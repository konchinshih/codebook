// Author: std_abs
// Vertices 1-based
// Edge ID 0-based, BCCID 0-based
// 1. EBCC ebcc(n);  // n = #(vertices)
// 2. ebcc.add_edge(u, v);
// 3. ebcc.build();
// => nbcc: number of EBCC
// => bccs: stores all edge bccs
// => bcc_id[u], is_bridge[Edge ID]
struct EBCC { // 1-based, remember to build
  int n, m, nbcc;
  vector<vector<pair<int, int>>> G;
  vector<vector<int>> bccs;
  vector<int> pa, low, dep, bcc_id, stk, is_bridge;
  void dfs(int v, int p, int f) {
    low[v] = dep[v] = ~p ? dep[p] + 1 : 0;
    stk.push_back(v), pa[v] = p;
    for (auto [u, e] : G[v]) {
      if (low[u] == -1)
        dfs(u, v, e), low[v] = min(low[v], low[u]);
      else if (e != f)
        low[v] = min(low[v], dep[u]);
    }
    if (low[v] == dep[v]) {
      if (~f) is_bridge[f] = true;
      bccs.push_back({});
      int id = nbcc++, x;
      do {
        x = stk.back(), stk.pop_back();
        bcc_id[x] = id;
        bccs[id].emplace_back(x);
      } while (x != v);
    }
  }
  void build() {
    is_bridge.assign(m, 0);
    for (int i = 1; i <= n; ++i) if (low[i] == -1)
      dfs(i, -1, -1);
  }
  void add_edge(int u, int v) {
    G[u].emplace_back(v, m), G[v].emplace_back(u, m++);
  }
  EBCC (int _n) : n(_n), m(0), nbcc(0), G(n + 1), pa(n + 1),
    low(n + 1, -1), dep(n + 1), bcc_id(n + 1), stk() {}
};
