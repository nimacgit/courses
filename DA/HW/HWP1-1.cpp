#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

const int maxn = 1e5 + 10, maxm = 2e5 + 100;
vector<int> adjvec[maxn];
int paries[maxn];
int paries_b[maxn];
int snode, tnode;
int seen[maxn];
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



bool bfs(int s, int max_q, int t){
    queue<int> q = queue<int>();
    for(int j = 0; j < n; j++){
        seen[j] = -1;
        parent[j] = j;
    }
    for(int i = 0; i < k; i++){
        q.push(paries[i]);
        seen[paries[i]] = 0;
    }
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if(seen[v] < max_q){
            for(int i = 0; i < adjvec[v].size(); i++){
                if(seen[adjvec[v][i]] == -1){
                    merge_par(v, adjvec[v][i]);
                    q.push(adjvec[v][i]);
                    seen[adjvec[v][i]] = seen[v] + 1;
                }else if(seen[adjvec[v][i]]+seen[v] < max_q){
                    merge_par(v, adjvec[v][i]);
                }
            }
        }
    }

    q = queue<int>();
    for(int j = 0; j < n; j++){
        seen[j] = -1;
    }
    for(int i = 0; i < k; i++){
        if(get_par(s) == get_par(paries[i])){
            q.push(paries[i]);
            seen[paries[i]] = 0;
        }
    }
    for(int j = 0; j < n; j++){
        parent[j] = j;
    }
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if(seen[v] < max_q){
            for(int i = 0; i < adjvec[v].size(); i++){
                if(seen[adjvec[v][i]] == -1){
                    merge_par(v, adjvec[v][i]);
                    q.push(adjvec[v][i]);
                    seen[adjvec[v][i]] = seen[v] + 1;
                }else if(seen[adjvec[v][i]]+seen[v] < max_q){
                    merge_par(v, adjvec[v][i]);
                }
            }
        }
    }
    return seen[t] != -1;
}

int main(){
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++){
        paries[i] = false;
        adjvec[i] = vector<int>();
    }
    for(int i = 0; i < k; i++){
        int tmp;
        cin >> tmp;
        tmp--;
        paries_b[tmp] = true;
        paries[i] = tmp;
    }
    for(int i = 0; i < m; i++){
        int s,t;
        cin >> s >> t;
        adjvec[s-1].push_back(t-1);
        adjvec[t-1].push_back(s-1);
    }
    cin >> snode >> tnode;
    snode--;
    tnode--;

    if(bfs(snode, 0, tnode)){
        cout << 0 << endl;
        return 0;
    }
    if(!bfs(snode, n-1, tnode)){
        cout << -1 << endl;
        return 0;
    }
    int s = 0, e = n-1;
    while(s < e - 1){
        int mid = (s+e)/2;
        if(bfs(snode, mid, tnode)){
            e = mid;
        }else{
            s = mid;
        }
    }
    cout << e << endl;
    return 0;
}