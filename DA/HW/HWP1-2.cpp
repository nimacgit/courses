#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

const int maxn = 12, maxk = 1002;
pair<int, pair<int, int>> adjvec[int(maxk*maxk/2)];
pair<int, pair<int, int>> tmp[int(maxk*maxk/2)];
vector<int> adj[int(maxk*maxk/2)];
int grade[maxk][maxn][maxn];
int parent[maxk];
int parent_size[maxk];
int p[maxk];
int send_type[maxk];
int seen[maxk];
int n, m, k, w;

void merge(int s, int e){
    int t = (s+e)/2;
    int f = s;
    for(int i = s; i < e; i++){
        if(f == (s+e)/2){
            tmp[i] = adjvec[t];
            t+=1;
        }else if(t == e){
            tmp[i] = adjvec[f];
            f+=1;
        }else if(adjvec[f].first > adjvec[t].first){
            tmp[i] = adjvec[t];
            t+=1;
        }else{
            tmp[i] = adjvec[f];
            f+=1;
        }
    }
    for(int i = s; i < e; i++){
        adjvec[i] = tmp[i];
    }
}
void sort(int s, int e){
    if(e - s < 2)
        return;
    int mid = (s + e)/2;
    sort(s, mid);
    sort(mid, e);
    merge(s, e);
}

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

int calc_diff(int v, int u){
    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grade[v][i][j] == grade[u][i][j]){
                cnt++;
            }
        }
    }
    return m*n-cnt;
}

int dfs(int v){
    if(seen[v])
        return 1;
    seen[v] = true;
    for(int i = 0; i < adj[v].size(); i++){
        if(!seen[adj[v][i]]){
            cout << adj[v][i] + 1 << " " << v + 1 << endl;
            dfs(adj[v][i]);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> k >> w;
    for(int i = 0; i < k; i++){
        parent[i] = i;
        p[i] = i;
        parent_size[i] = 1;
        send_type[i] = false;
        for(int j = 0; j < n; j++){
            string s;
            cin >> s;
            for(int k = 0; k < m; k++){
                grade[i][j][k] = s[k];
            }
        }
    }
    int cnt = 0;
    for(int i = 0; i < k; i++){
        for(int j = i + 1; j < k; j++){
            adjvec[cnt] = pair<int, pair<int, int>>(calc_diff(i, j), pair<int, int>(i, j));
            cnt += 1;
        }
    }
    sort(0, cnt);
    int good = 0;
    int cost = 0;
    for(int i = 0; i < cnt; i++){
        if(adjvec[i].first * w < m*n && get_par(adjvec[i].second.first) != get_par(adjvec[i].second.second)){
            cost += adjvec[i].first * w;
            good += 1;
            merge_par(adjvec[i].second.first, adjvec[i].second.second);
            adj[adjvec[i].second.first].push_back(adjvec[i].second.second);
            adj[adjvec[i].second.second].push_back(adjvec[i].second.first);
        }
    }
    cout << (k-good)*n*m + cost << endl;
    for(int i = 0; i < k; i++){
        if(!seen[i]){
            cout << i+1 << " " << 0 << endl;
            dfs(i);
        }
    }
    return 0;
}