// Author: Ian, https://judge.yosupo.jp/submission/399291
// Tarjan SCC, 0-based
// 1. SCC scc(n);  // n = #(vertices)
// 2. Fill in adj list G
// 3. scc.build()
// => scc[i]: each scc
// => sccn[x]: in which scc is x
struct SCC {
  const int inf = 1e9+5;
  int n, t, ncnt;
  vector<vector<int>> G, scc;
  vector<bool> ins;
  vector<int> sccn, dfn, low, s;
  SCC(int n): n(n), t(0), ncnt(0), G(n),
    ins(n, false), sccn(n), dfn(n, -1), low(n, inf) {}
  void dfs(int x) {
    if (~dfn[x]) return;
    dfn[x] = low[x] = t++;
    s.push_back(x), ins[x] = true;
    for (auto i: G[x])
      if (dfs(i), ins[i])
        low[x] = min(low[x], low[i]);
    if (dfn[x] == low[x]) {
      scc.resize(scc.size()+1);
      int p; do {
        ins[p = s.back()] = false;
        s.pop_back(); sccn[p] = ncnt;
        scc.back().push_back(p);
      } while (p != x); ncnt++;
    }
  }
  void build() { for (int i=0; i<n; i++) dfs(i); }
};
