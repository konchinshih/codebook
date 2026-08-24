// Author: Ian
// tarjan SCC
void solve() {
  V<bool> ins(n, false);
  V<int> scc(n), dfn(n, -1), low(n, inf);
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
  for (int i = 0; i < n; i++)
    dfs(i);
}
