#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

const int maxn = 1e5 + 1000;
int t, k;
long ans[maxn];
long mod = 1e9 + 7;

int main(){
    cin >> t >> k;
    int a, b;
    ans[0] = 1;
    for(int i = 1; i < 1e5+100; i++){
        ans[i] = ans[i-1];
        if(k <= i){
            ans[i] = (ans[i] + ans[i-k])%mod;
        }
    }
    for(int i = 1; i < 1e5+100; i++){
        ans[i] = (ans[i] + ans[i-1])%mod;
    }
    for(int i = 0; i < t; i++){
        cin >> a >> b;
        cout << (mod + ans[b] - ans[a-1])%mod << endl;
    }
    
    
    return 0;
}