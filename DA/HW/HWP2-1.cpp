#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

const int maxn = 18;
int n, m, k;
long a[maxn];
long c[maxn][maxn];
long two[maxn];
int tmparr[maxn];
long ans[maxn][2LL<<maxn];

int main(){
    cin >> n >> m >> k;
    two[0] = 1;
    for(int i = 0; i < n; i++){
        if(i > 0){
            two[i] = two[i - 1] * 2;
        }
        cin >> a[i];
        for(int j = 0; j < n; j++){
            c[i][j] = 0;
        }
    }
    for(int i = 0; i < k; i++){
        int x, y;
        cin >> x >> y;
        cin >> c[x-1][y-1];
    }

    long max_ans = 0;
    if(m == 0){
        cout << 0 << endl;
        return 0;
    }
    for(int i = 0; i < n; i++){
        ans[i][two[i]] = a[i];
        max_ans = max(a[i], max_ans);
    }
    for(int i = 2; i <= m; i++){
        for(int j = 0; j < n; j++){
            if(j < i){
                tmparr[n-j-1] = 1;
            }
            else{
                tmparr[n-j-1] = 0;
            }
        }
        do{
            long num = 0;
            for(int j = 0; j < n; j++){
                if(tmparr[j] == 1){
                    num += two[n-1-j];
                }
            }
            for(int j = 0; j < n; j++){
                for(int k = 0; k < n; k++){
                    if(k != j){
                        if(tmparr[n-1-j] == 1 && tmparr[n-1-k] == 1){
                            // cout << a[j] << " " << c[j][k] << " " << ans[k][num - two[j]] << " " << j << " " << k << " " << num << endl;
                            ans[j][num] = max(ans[j][num], a[j] + c[j][k] + ans[k][num - two[j]]);
                            if(i == m){
                                max_ans = max(ans[j][num], max_ans);
                            }
                        }
                    }
                }
            }
            // for(int j = 0; j < n; j++){
            //     cout << tmparr[j] << " ";
            // }
            // cout << endl << "    ";
            // for(int j = 0; j < n; j++){
            //     cout << ans[j][num] << " ";
            // }
            // cout << endl;
        }while(next_permutation(tmparr, tmparr+n));
    }
    cout << max_ans << endl;
    
    
    return 0;
}