// sorted by x; type 0 = update (weight w), 1 = query
// query: ans[id] = sum of w over updates with x' <= x,
// y' <= y, z' <= z (< if strict[dim]). 值域 [1, mxc]
// Dependency: 值域 BIT
struct Info { int x, y, z, type; ll w; int id; };
struct CDQ {
  static bool cy(const Info& p, const Info& q)
  { return p.y < q.y; }
  vector<Info> a; int n; array<bool, 3> strict;
  vector<ll> ans; BIT bit;
  void dfs(int l, int r) { if (r - l <= 1) return;
    int m = (l + r) / 2, i = l;
    dfs(l, m);
    vector<Info> t(a.begin() + m, a.begin() + r);
    ranges::sort(t, cy);
    for (auto& q : t) {
      for (; i < m && a[i].y < q.y + !strict[1]; i++)
        if (!a[i].type) bit.upd(a[i].z, a[i].w);
      if (q.type)
        ans[q.id] += bit.qry(q.z - strict[2]);
    }
    for (int k = l; k < i; k++)
      if (!a[k].type) bit.upd(a[k].z, -a[k].w);
    dfs(m, r);
    inplace_merge(a.begin() + l, a.begin() + m,
                  a.begin() + r, cy);
  }
  CDQ(vector<Info> _a, int mxc, array<bool, 3> _s = {}):
      a(_a), n(a.size()), strict(_s) {
    ans.assign(n, 0); bit.init(mxc);
    auto key = [&](Info& p) { return
      make_tuple(p.x, p.type != strict[0], p.y, p.z); };
    ranges::sort(a, {}, key); dfs(0, n);
  }
};

