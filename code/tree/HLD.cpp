// Author: Ian, https://judge.yosupo.jp/submission/399317
void segbuild(vector<int>&v);
void segmodify(int p, int k);
int segquery(int ql, int qr);
// Insert [ql, qr) segment tree here
template<class T=int> struct HLD {
  int n, cnt;
  vector<int> d, f, sz, son, top, dfn;
  HLD(int n): n(n), cnt(0), d(n, 0), f(n, 0), sz(n, 1),
    son(n, -1), top(n, 0), dfn(n, -1) {}
  void dfs1(int x, int p) {
    for (auto i: e[x]) if (i != p) {
      d[i] = d[x]+1, f[i] = x;
      dfs1(i, x), sz[x] += sz[i];
      if (son[x] == -1 || sz[son[x]] < sz[i])
        son[x] = i;
    } }
  void dfs2(int x, int t) {
    dfn[x] = cnt++, top[x] = t;
    if (son[x] == -1) return;
    dfs2(son[x], t);
    for (auto i: e[x])
      if (!~dfn[i]) dfs2(i, i);
  }
  void build(const vector<T> &v) {
    dfs1(0, 0); dfs2(0, 0);
    vector<T> dfnv(v.size());
    for (int i=0; i<n; i++)
      dfnv[dfn[i]] = v[i];
    segbuild(dfnv); }
  void modify(int p, T v) { segmodify(dfn[p], v); }
  T query(int a, int b) {
    auto aggr = [](int x, int y) { return max(x, y); };
    T ret = 0;
    while (top[a] != top[b]) {
      if (d[top[a]] > d[top[b]]) swap(a, b);
      ret = aggr(ret, segquery(dfn[top[b]], dfn[b]+1));
      b = f[top[b]];
    }
    if (dfn[a] > dfn[b]) swap(a, b);
    return aggr(ret, segquery(dfn[a], dfn[b]+1));
  }
};
