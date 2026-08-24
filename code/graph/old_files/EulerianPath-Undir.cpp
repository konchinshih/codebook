// Author: Gino
// Usage: build deg, G first, then eulerian()
int n, m;  // number of vertices and edges
vector<int> deg;  // degree 
vector<set<pii>> G;  // G[u] := {(v, edge id)}

vector<int> path_u, path_e;
void dfs(int u) {
    while (!G[u].empty()) {
        auto it = G[u].begin();
        auto [v, i] = *it; G[u].erase(it);
        G[v].erase(make_pair(u, i)); dfs(v);
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
    int oddcnt = 0, s = -1;
    for (int u = 1; u <= n; u++)
        if (deg[u] & 1)
            oddcnt++, s = u;

    if (oddcnt != 0 && oddcnt != 2) return false;
    if (s == -1) {
        s = 1; for (int u = 1; u <= n; u++) 
            if (deg[u] > 0)
                s = u;
    }
    gogo(s);

    for (int u = 1; u <= n; u++)
        if ((int)G[u].size() > 0)
            return false;
    return true;
}
