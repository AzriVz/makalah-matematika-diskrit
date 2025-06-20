#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];    
int f[MAXN][2];              
int pos[MAXN];               
bool is_evil[MAXN];          
int n, m, d, ans = 0;

void dfs(int u, int parent) {
    if (is_evil[u]) f[u][0] = 0; 

    for (int v : adj[u]) {
        if (v == parent) continue;

        dfs(v, u);

        int depth = f[v][0] + 1;
        if (depth > f[u][0]) {
            f[u][1] = f[u][0];
            f[u][0] = depth;
            pos[u] = v;
        } else if (depth > f[u][1]) {
            f[u][1] = depth;
        }
    }
}

void redfs(int u, int parent, int up) {
    int max_dist = max(f[u][0], up);
    if (max_dist <= d) ans++;

    for (int v : adj[u]) {
        if (v == parent) continue;

        int use_up = (v == pos[u]) ? f[u][1] + 1 : f[u][0] + 1;
        use_up = max(use_up, up + 1);
        redfs(v, u, use_up);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> d;

    for (int i = 0; i < m; ++i) {
        int id;
        cin >> id;
        is_evil[id] = true;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        f[i][0] = f[i][1] = -1e9;
    }

    dfs(1, -1);  
    redfs(1, -1, -1e9);         

    cout << ans << "\n";
    return 0;
}
