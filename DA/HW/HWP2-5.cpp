#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

const int maxn = 2005;
int n, m;
long dd[maxn][maxn], dds[maxn][maxn], dr[maxn][maxn], drs[maxn][maxn];
bool isrock[maxn][maxn];
long mod = 1e9 + 7;
int rowsum[maxn][maxn], colsum[maxn][maxn];
// long getdr(int i, int j);

long getdd(int i, int j){
    // cout << " dd " << i << " " << j << endl;
    if(dd[i][j] != -1){
        return dd[i][j];
    }
    if(i == n - 1 && j == m - 1){
        return dd[i][j] = 1;
    }
    if(i == n - 1){
        if(rowsum[i][j] == 0)
            return dd[i][j] = 1;
        return dd[i][j] = 0;
    }
    if(j == m - 1){
        return dd[i][j] = 0;
    }
    dd[i][j] = 0;
    // cout << " sum " << rowsum[i][j+1] << endl;
    for(int k = j + 1; k < m - rowsum[i][j+1]; k++){
        if(colsum[i+1][k] < n - i - 1){
            if(k == m - 1){
                if(colsum[i][k] == 0){
                    dd[i][j] = (dd[i][j] + 1LL)%mod;
                }
            }else{
                dd[i][j] = (dd[i][j] + getdd(i+1, k))%mod;
            }
        }
    }
    // cout << " ans dd " << i << " " << j << " " << dd[i][j] << endl;
    return dd[i][j];
}
// long getdr(int i, int j){
//     // cout << " dr " << i << " " << j << endl;
//     if(i == n - 1 && j == m - 1){
//         return dr[i][j] = 1;
//     }
//     if(dr[i][j] != -1){
//         return dr[i][j];
//     }
//     dr[i][j] = 0;
//     // cout << " sum " << colsum[i+1][j] << endl;
//     for(int k = i + 1; k < n - colsum[i+1][j]; k++){
//         dr[i][j] = (dr[i][j] + getdd(k, j))%mod;
//     }
//     // cout << " ans dr " << i << " " << j << " " << dr[i][j] << endl;
//     return dr[i][j];
// }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int sum = 0;
        for(int j = 0; j < m; j++){
            if(s[j] == '.'){
                isrock[i][j] = false;
            }else{
                sum += 1;
                isrock[i][j] = true;
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(isrock[i][m-1]){
            rowsum[i][m-1] = 1;
        }
        for(int j = m-2; j >= 0; j--){
            rowsum[i][j] = rowsum[i][j+1];
            if(isrock[i][j]){
                rowsum[i][j] += 1;
            }
        }
    }
    for(int i = 0; i < m; i++){
        if(isrock[n-1][i]){
            colsum[n-1][i] = 1;
        }
        for(int j = n-2; j >= 0; j--){
            colsum[j][i] = colsum[j+1][i];
            if(isrock[j][i]){
                colsum[j][i] += 1;
            }
        }
    }
    for(int i = 0; i < m-1; i++){
        if(rowsum[n-1][i] == 0){
            dd[n-1][i] = 1;
            dds[n-1][i] = 1;
        }else
            dd[n-1][i] = 0;
    }
    for(int i = 0; i < n-1; i++){
        if(colsum[i][m-1] == 0){
            dr[i][m-1] = 1;
            drs[i][m-1] = 1;
        }else
            dr[i][m-1] = 0;
    }
    if(m == 1){
        if(colsum[0][0] == 0){
            cout << 1 << endl;
            return 0;
        }
        cout << 0 << endl;
        return 0;
    }
    for(int i = n-2; i >= 0; i--){
        for(int j = m-2; j >= 0; j--){
            dd[i][j] = (drs[i][j+1] - drs[i][m-rowsum[i][j+1]] + mod)%mod;
            dds[i][j] = (dds[i+1][j] + dd[i][j])%mod;
            dr[i][j] = (dds[i+1][j] - dds[n-colsum[i+1][j]][j] + mod)%mod;
            drs[i][j] = (drs[i][j+1] + dr[i][j])%mod;
        }
    }
    
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < m; j++){
    //         cout << dd[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < m; j++){
    //         cout << dr[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << (dd[0][0] + dr[0][0])%mod << endl;
    return 0;
}