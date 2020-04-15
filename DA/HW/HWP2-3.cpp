#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

const int maxn = 5e5 + 10;
vector<pair<int,long long> > adjvec[maxn];
bool seen[maxn];
int parent[maxn];
long long ans[2][maxn];
int n, k, q;
long long tmparr[maxn];

void calc(int v){
    int cnt = 0;
    long long sum = 0;
    for(int i = 0; i < adjvec[v].size(); i++){
        if(adjvec[v][i].first != parent[v]){
            calc(adjvec[v][i].first);
        }
    }
    for(int i = 0; i < adjvec[v].size(); i++){
        if(adjvec[v][i].first != parent[v]){
            sum += ans[0][adjvec[v][i].first];
            if(ans[1][adjvec[v][i].first] + adjvec[v][i].second > ans[0][adjvec[v][i].first]){
                tmparr[cnt] = -(ans[1][adjvec[v][i].first] + adjvec[v][i].second - ans[0][adjvec[v][i].first]);
                cnt += 1;
            }
        }
    }
    ans[0][v] = sum;
    ans[1][v] = sum;
    if(cnt > 0){
        sort(tmparr, tmparr+cnt);
        if(cnt < k){
            for(int i = 0; i < cnt; i++){
                ans[0][v] -= tmparr[i];
                ans[1][v] -= tmparr[i];
            }
        }else{
            for(int i = 0; i < k-1; i++){
                ans[0][v] -= tmparr[i];
                ans[1][v] -= tmparr[i];
            }
            ans[0][v] -= tmparr[k-1];
        }
    }
    
}

int dfs(int v){
    if(seen[v])
        return 1;
    seen[v] = true;
    for(int i = 0; i < adjvec[v].size(); i++){
        if(!seen[adjvec[v][i].first]){
            parent[adjvec[v][i].first] = v;
            dfs(adjvec[v][i].first);
        }
    }
}

void fastscan(int &x)
{
    bool neg=false;
    register int c;
    x = 0;
    c=getchar();
    if(c=='-')
    {
        neg = true;
        c=getchar();
    }
    for(;(c>47 && c<58);c=getchar())
        x = (x<<1) + (x<<3) +c -48;
    if(neg)
        x *=-1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // fastscan(q);
    scanf("%d", &q);
    while(q > 0){
        q -= 1;
        scanf("%d", &n);
        scanf("%d", &k);
        // fastscan(n);
        // fastscan(k);
        int s, t, w;
        for(int i = 0; i < n; i++){
            seen[i] = false;
            adjvec[i] = vector<pair<int, long long> >();
        }
        for(int i = 0; i < n-1; i++){
            scanf("%d", &s);
            scanf("%d", &t);
            scanf("%d", &w);
            // fastscan(s);
            // fastscan(t);
            // fastscan(w);
            // cout << s << " " << t << " " << w << endl;
            adjvec[s-1].push_back(pair<int, int>(t-1, w));
            adjvec[t-1].push_back(pair<int, int>(s-1, w));
        }
        dfs(0);
        calc(0);
        printf("%lld\n",ans[0][0]);
    }
    return 0;
}