// Author: Ian, https://judge.yosupo.jp/submission/399308
// Vertex BCC (Round Square Tree) 0-based; Edge ID 0-based
// 1. BCC bcc(n);  // n = #(vertices)
// 2. bcc.add_edge(u, v);
// 3. bcc.build();
// => bcc[id]: vertices in bcc `id` (square node n+id in T)
// => T[id]: tree adjacency; square nodes are n..n+ncnt-1
// => is_cut(x): whether x is a cut vertex
// => bcc_id(u, v): square node containing tree-edge (u, v)
struct BCC {
  int n, m, t, ncnt;
  vector<vector<pii>> G;
  vector<vector<int>> T, bcc;
  vector<int> dep, low, pa2, dep2, s;
  void add_edge(int u, int v) {
    G[u].eb(v, m), G[v].eb(u, m++); }
  void dfs(int x, int f) {
    if (~dep[x]) return;
    dep[x] = low[x] = t++;
    s.push_back(x);
    for (auto [y, e]: G[x]) if (e != f) {
      if (dep[y] == -1) {
        dfs(y, e), low[x] = min(low[x], low[y]);
        if (low[y] >= dep[x]) {
          int id = n + ncnt++, p;
          bcc.resize(bcc.size()+1);
          do {
            p = s.back(), s.pop_back();
            T[id].push_back(p), T[p].push_back(id);
            bcc.back().push_back(p);
          } while (p != y);
          T[id].push_back(x), T[x].push_back(id);
          bcc.back().push_back(x);
        }
      } else low[x] = min(low[x], dep[y]); } }
  void dfs2(int x, int p) {
    dep2[x] = ~p ? dep2[p] + 1 : 0, pa2[x] = p;
    for (auto y: T[x]) if (y != p) dfs2(y, x); }
  bool is_cut(int x) { return (int)T[x].size() != 1; }
  int bcc_id(int u, int v) {
    return pa2[dep2[u] < dep2[v] ? v : u] - n; }
  void build() {
    for (int i = 0; i < n; i++) if (dep[i] == -1) {
      if (G[i].empty()) { // isolated vertex: singleton bcc
        dep[i] = low[i] = t++;
        int id = n + ncnt++;
        bcc.push_back({i});
        T[id].push_back(i), T[i].push_back(id);
      } else dfs(i, -1);
      dfs2(i, -1);
    } }
  BCC(int n): n(n), m(0), t(0), ncnt(0), G(n), T(2*n),
    dep(n, -1), low(n), pa2(2*n), dep2(2*n) {}
};
