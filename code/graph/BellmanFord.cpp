// Author: Gino
// n, m = #(vertices), #(edges), and vertices are 1-based
// 1. BellmanFord bf(G, n, m); 
// 2-1: bf.calcDis(s);
// => bf.dis[u] := shortest dis from s to u
// => bf.dis[u] := LINF  (s can't reach u)
// => bf.dis[u] := -LINF (dis[u] can be arbitrary small)
// 2-2: bf.findNegCycle();
// => return false (if no neg cycle)
// => return true  (has neg cycle, and gives an example: bf.neg_cycle)
// Time: O(VE), Space: O(V + E)
const ll LINF = 4e18;
struct BellmanFord {
  const vector<vector<pair<int, ll>>>& G;
  int n, m;  // #(vertices), #(edges)
  BellmanFord(const auto& G, int n, int m): G(G), n(n), m(m) {}
  vector<ll> dis; vector<int> nth_relax, pa;
  void run_bf(const auto& src) {
dis.assign(n+1,LINF);nth_relax.assign(n+1,0);pa.assign(n+1,-1);
    for (auto& s : src) dis[s] = 0;
    for (int rlx = 1; rlx <= n; rlx++) {
      for (int u = 1; u <= n; u++) {
        if (dis[u] == LINF) continue; // !important
        for (auto& [v, w] : G[u]) {
          if (dis[v] > dis[u] + w) {
            dis[v] = dis[u] + w; pa[v] = u;
            if (rlx == n) nth_relax[v] = 1;
  } } } } }  // 5 brackets
  void calcDis(int s) {
    run_bf(vector<int>{s}); queue<int> q;
    for (int u=1;u<=n;u++) if (nth_relax[u]) q.push(u);
    while (!q.empty()) { int u = q.front(); q.pop();
      for (auto& [v, w] : G[u]) {
        if (!nth_relax[v]) {
          nth_relax[v] = 1; q.push(v);
    } } }
    for (int u=1;u<=n;u++) if (nth_relax[u]) dis[u]= -LINF;
  }
  vector<int> neg_cycle;
  bool findNegCycle() {
    auto src = views::iota(1, n + 1); run_bf(src);
    auto it = ranges::find_if(src, [&](int s){ return nth_relax[s]; });
    if (it == src.end()) return false;
    int ptr = *it; for (int i=0; i<n; i++) ptr = pa[ptr];
    neg_cycle.clear(); int cur = ptr;
    while (true) {
      neg_cycle.emplace_back(cur);
      if (cur == ptr && neg_cycle.size() > 1) break;
      cur = pa[cur];
    }
    ranges::reverse(neg_cycle);
    return true;
  } };
