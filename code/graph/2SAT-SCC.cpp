// Author: Ian
// 2-sat + tarjan SCC
void solve() {
  int n, r, l; cin >> n >> r >> l;
  V<P<int>> v(l);
  for (auto& [a, b] : v)
    cin >> a >> b;
  V<V<int>> e(2 * l);
  for (int i = 0; i < l; i++)
    for (int j = i + 1; j < l; j++) {
      if (v[i].first == v[j].first && abs(v[i].second - v[j].second) <= 2 * r) {
        e[i << 1].emplace_back(j << 1 | 1);
        e[j << 1].emplace_back(i << 1 | 1);
      }
      if (v[i].second == v[j].second && abs(v[i].first - v[j].first) <= 2 * r) {
        e[i << 1 | 1].emplace_back(j << 1);
        e[j << 1 | 1].emplace_back(i << 1);
      }
    }
  V<bool> ins(2 * l, false);
  V<int> scc(2 * l), dfn(2 * l, -1), low(2 * l, inf);
  stack<int> s;
  function<void(int)> dfs = [&](int x) {
    if (~dfn[x]) return;
    static int t = 0;
    dfn[x] = low[x] = t++;
    s.push(x), ins[x] = true;
    for (auto i : e[x])
      if (dfs(i), ins[i])
        low[x] = min(low[x], low[i]);
    if (dfn[x] == low[x]) {
      static int ncnt = 0;
      int p; do {
        ins[p = s.top()] = false;
        s.pop(), scc[p] = ncnt;
      } while (p != x); ncnt++;
    }
  };
  for (int i = 0; i < 2 * l; i++)
    dfs(i);
  for (int i = 0; i < l; i++)
    if (scc[i << 1] == scc[i << 1 | 1]) {
      cout << "NO" << endl;
      return;
    }
  cout << "YES" << endl;
}
