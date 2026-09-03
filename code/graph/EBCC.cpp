// Author: Ian, https://judge.yosupo.jp/submission/399295
// Edge BCC, 0-based; Edge ID 0-based
// 1. EBCC ebcc(n);  // n = #(vertices)
// 2. ebcc.add_edge(u, v);
// 3. ebcc.build();
// => bcc[i]: each edge bcc
// => bccn[x]: in which bcc is x
// => isbr[e]: whether edge e is a bridge
struct EBCC {
  int n, m, t, ncnt;
  vector<vector<pii>> G;
  vector<vector<int>> bcc;
  vector<bool> isbr;
  vector<int> dep, low, bccn, s;
  EBCC(int n): n(n), m(0), t(0), ncnt(0), G(n),
    dep(n, -1), low(n), bccn(n) {}
  void add_edge(int u, int v) {
    G[u].eb(v, m), G[v].eb(u, m++); }
  void dfs(int x, int f) {
    if (~dep[x]) return;
    dep[x] = low[x] = t++;
    s.push_back(x);
    for (auto [y, e]: G[x]) if (e != f) {
      if (dep[y] == -1)
        dfs(y, e), low[x] = min(low[x], low[y]);
      else
        low[x] = min(low[x], dep[y]);
    }
    if (dep[x] == low[x]) {
      if (~f) isbr[f] = true;
      bcc.resize(bcc.size()+1);
      int p; do {
        bccn[p = s.back()] = ncnt;
        s.pop_back();
        bcc.back().push_back(p);
      } while (p != x); ncnt++;
    }
  }
  void build() {
    isbr.assign(m, false);
    for (int i=0; i<n; i++) dfs(i, -1); }
};
