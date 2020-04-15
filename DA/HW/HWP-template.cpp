#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

const int maxn = 1e5 + 10, maxm = 2e5 + 100;
vector<int> adjvec[maxn];
int paries[maxn];
int snode, tnode;
bool seen[maxn];
int parent[maxn];
int parent_size[maxn];
int n, m, k;

int get_par(int v){
    if(parent[v] != parent[parent[v]])
        return parent[v] = get_par(parent[v]);
    else
        return parent[v];
}

void merge_par(int v, int u){
    v = get_par(v);
    u = get_par(u);
    if(parent_size[v] < parent_size[u])
        swap(v, u);
    parent[u] = v;
    parent_size[v] += parent_size[u];
}

int bfs(int s){
    queue<int> q = queue<int>();
    seen[s] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int i = 0; i < adjvec[v].size(); i++){
            if(!seen[adjvec[v][i]]){
                q.push(adjvec[v][i]);
                seen[adjvec[v][i]] = true;
            }
        }
    }
}

int dfs(int v){
    if(seen[v])
        return 1;
    seen[v] = true;
    for(int i = 0; i < adjvec[v].size(); i++){
        if(!seen[adjvec[v][i]]){
            dfs(adjvec[v][i]);
        }
    }
}

void fastscan(int &x)
{
    bool neg=false;
    register int c;
    x =0;
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
    int n, m, k;
    // scanf("%d",&x);
    // fastscan(n);
    // cin >> n >> m >> k;
    // for(int i = 0; i < n; i++){
    //     seen[i] = false;
    //     adjvec[i] = vector<int>();
    // }
    // for(int i = 0; i < k; i++){
    //     int tmp;
    //     cin >> tmp;
    //     paries[i] = tmp - 1;
    // }
    // for(int i = 0; i < m; i++){
    //     int s,t;
    //     cin >> s >> t;
    //     adjvec[s-1].push_back(t-1);
    //     adjvec[t-1].push_back(s-1);
    // }
    // cin >> snode >> tnode;
    // // bfs(snode);
    // dfs(snode);
    return 0;
}
