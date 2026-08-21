// Author: Gino
// Usage: build ind, oud, G first, then eulerian()
int n, m;  // number of vertices, edges
vector<int> ind, oud;  // indegree, outdegree
vector<vector<pii>> G;  // G[u] := {(v, edge id)}

vector<int> path_u, path_e;
void dfs(int u) {
    while (!G[u].empty()) {
        auto [v, i] = G[u].back(); G[u].pop_back();
        dfs(v);
        path_u.emplace_back(v);
        path_e.emplace_back(i);
    }
}
void gogo(int s) {
    path_u.clear(); path_e.clear();
    dfs(s); path_u.emplace_back(s);
    reverse(path_u.begin(), path_u.end());
    reverse(path_e.begin(), path_e.end());
}
bool eulerian() {
    int s = -1;
    for (int u = 1; u <= n; u++) {
        if (abs(oud[u] - ind[u]) > 1) return false;
        if (oud[u] - ind[u] == 1) {
            if (s != -1) return false;
            s = u;
        }
    }
    if (s == -1) {
        s = 1; for (int u = 1; u <= n; u++) 
            if (ind[u] > 0)
                s = u;
    }
    gogo(s);
    for (int u = 1; u <= n; u++)
        if ((int)G[u].size() > 0)
            return false;

    return true;
}
