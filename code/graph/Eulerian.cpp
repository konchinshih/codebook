// Author: kactl (Simon Lindholm), wrapped by Gino
// Vertices are 1-based, Edge ID are 0-based
// 1. EulerWalk euler(n, true(directed) / false(undirected));
// 2. euler.addEdge(u, v);
// 3. int result = euler.solve();
// => -1: nothing ( euler.path, euler.path_edges = {} )
// =>  1: Euler trail,
// =>  2: Euler circuit
//        euler.path = {u_1, ..., u_{m+1}}
//        euler.path_edges = {e_1, ..., e_m}
// Time: O(V + E), Space: O(V + E)
// Test: V, E <= 2e5, 99ms
struct EulerWalk {
  int n, m = 0; bool dir;
  vector<vector<pii>> G; vi deg;
  EulerWalk(int n, bool dir) : n(n), dir(dir), G(n + 1), deg(n + 1) {}
  void addEdge(int u, int v) {
    G[u].push_back({v, m});
    if (!dir) G[v].push_back({u, m});
    deg[u]++, deg[v] += dir ? -1 : 1;
    m++;
  }
  vi path, path_edges;
  void walk(int src) {
    path.clear(); path_edges.clear();
    vi its(n + 1), visE(m);
    function<void(int, int)> dfs = [&](int u, int e_in) {
      while (its[u] < sz(G[u])) {
        auto [v, e] = G[u][its[u]++];
        if (visE[e]) continue;
        visE[e] = 1;
        dfs(v, e);
      }
      path.push_back(u);
      if (e_in != -1) path_edges.push_back(e_in);
    };
    dfs(src, -1);
    if (sz(path) != m + 1) {
      path.clear(); path_edges.clear(); return;
    }
    ranges::reverse(path); ranges::reverse(path_edges);
  }
  int solve() {
    int s = -1, odd = 0, src = 0, dst = 0;
    for (int u = 1; u <= n; u++) {
      if (!dir && (deg[u] & 1)) odd++, s = u;
      if (dir && deg[u] == 1) s = u, src++;
      if (dir && deg[u] == -1) dst++;
      if (dir && abs(deg[u]) > 1) return -1;
    }
    if (!dir && odd != 0 && odd != 2) return -1;
    if (dir && !((src == 0 && dst == 0) || (src == 1 && dst == 1))) return -1;
    if (s == -1) for (int u = 1; u <= n; u++) if (!G[u].empty()) { s = u; break; }
    if (s == -1) s = 1;
    walk(s);  return path.empty() ? -1 : path.front() == path.back() ? 2 : 1;
  }
};
