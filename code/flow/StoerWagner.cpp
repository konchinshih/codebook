// Author: ckiseki
// 1-based: vertices are numbered 1 ~ n
// 1. vector<vector<ll>> G(n + 1, vector<ll>(n + 1, 0));
// 2. add_edge(G, u, v, c);  // add undirected edge u-v with weight c, u,v in [1,n]
// 3. ll ans = mincut(G, n); // n = #vertices
// => ans = global min cut value
// Time: O(V^3)
void add_edge(auto &w, int u, int v, int c) {
  w[u][v] += c; w[v][u] += c; }
auto phase(const auto &w, int n, vector<int> id) {
  vector<ll> g(n + 1); int s = -1, t = -1;
  while (!id.empty()) {
    int c = -1;
    for (int i : id) if (c == -1 || g[i] > g[c]) c = i;
    s = t; t = c;
    id.erase(ranges::find(id, c));
    for (int i : id) g[i] += w[c][i];
  }
  return tuple{s, t, g[t]};
}
ll mincut(auto w, int n) {
  ll cut = numeric_limits<ll>::max();
  vector<int> id(n); iota(all(id), 1);
  for (int i = 0; i < n - 1; ++i) {
    auto [s, t, gt] = phase(w, n, id);
    id.erase(ranges::find(id, t));
    cut = min(cut, gt);
    for (int j = 1; j <= n; ++j)
      w[s][j] += w[t][j], w[j][s] += w[j][t];
  }
  return cut;
}
