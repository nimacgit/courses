#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

const int maxn = 503;
vector<pair<int, int> > adjvec[maxn];
pair<pair<int, int>, int> edges[maxn*maxn];
int paries[maxn];
int snode, tnode;
bool seen[maxn];
int parent[maxn];
int parent_size[maxn];
int n, m, k;
int d[maxn][maxn];

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


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i <= n; i++){
        d[0][i] = 1e9;
        seen[i] = false;
        adjvec[i] = vector<pair<int, int> >();
    }
    d[0][0] = 0;
    for(int i = 0; i < m; i++){
        int s,t,w;
        cin >> s >> t >> w;
        adjvec[s].push_back(pair<int, int>(t, w));
        edges[i] = pair<pair<int, int>,int>(pair<int, int>(s,t), w);
    }
    int s, t, w;
    for(int i = 0; i < n; i++){
        adjvec[0].push_back(pair<int, int>(i+1, 0));
        edges[m+i] = pair<pair<int, int>,int>(pair<int, int>(0,i+1), 0);
    }
    m += n;
    n += 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < n; j++){
            d[i][j] = d[i-1][j];
        }
        for(int j = 0; j < m; j++){
            s = edges[j].first.first;
            t = edges[j].first.second;
            w = edges[j].second;
            if(d[i-1][s] + w < d[i][t])
                d[i][t] = d[i-1][s] + w;
        }
    }
    for(int j = 0; j < m; j++){
        s = edges[j].first.first;
        t = edges[j].first.second;
        w = edges[j].second;
        if(d[n-1][s] + w < d[n-1][t]){
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    int mind = d[n-1][1];
    for(int i = 2; i < n; i++){
        mind = min(d[n-1][i], mind);
    }
    for(int i = 1; i < n; i++){
        cout << d[n-1][i] - mind << " ";
    }
    cout << endl;
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         d[i][j] = 1e9;
    //     }
    //     d[i][i] = 0;
    //     for(int j = 0; j < m; j++){
    //         s = edges[j].first.first;
    //         t = edges[j].first.second;
    //         w = edges[j].second;
    //         d[s][t] = w;
    //     }
    // }
    // for(int k = 0; k < n; k++){
    //     for(int i = 0; i < n; i++){
    //         for(int j = 0; j < n; j++){        
    //             if(d[i][k] + d[k][j] < d[i][j])
    //                 d[i][j] = d[i][k] + d[k][j];
    //         }
    //     }
    // }
    return 0;
}