// Author: ckiseki
// n = #(left vertices) = #(right vertices)
// left, right vertices labeled 1 ~ n separately
// 1. build 1-based matrix G of size (n + 1) * (n + 1)
//    G[u][v] := weight between (left u, right v)
//  <!> if not need perfect matching => set weights of all negative edges to 0
// 2. constrcut (solve at same time): KM km(n, G);
// => km.ans (max perfect weight sum)
// => km.fl[u] (left u -> right v)
// => km.fr[v] (right v -> left u)
// Time: O(V^3), Space: O(V^2)
// Test: V <= 500, 243ms
struct KM { // maximize, test @ UOJ 80
  int n, l, r; ll ans; // fl and fr are the match
  vector<ll> hl, hr; vector<int> fl, fr, pre, q;
  void bfs(const auto &w, int s) {
    vector<int> vl(n + 1), vr(n + 1); vector<ll> slk(n + 1, LINF);
    l = r = 0; vr[q[r++] = s] = true;
    auto check = [&](int x) -> bool {
      if (vl[x] || slk[x] > 0) return true;
      vl[x] = true; slk[x] = LINF;
      if (fl[x] != -1) return (vr[q[r++] = fl[x]] = true);
      while (x != -1) swap(x, fr[fl[x] = pre[x]]);
      return false;
    };
    while (true) {
      while (l < r)
        for (int x = 1, y = q[l++]; x <= n; ++x) if (!vl[x])
          if (ll val = hl[x] + hr[y] - w[x][y]; val < slk[x]) {
            slk[x] = val;
            if (pre[x] = y, !check(x)) return;
          }
      ll d = LINF;
      for (int x = 1; x <= n; ++x) d = min(d, slk[x]);
      for (int x = 1; x <= n; ++x)
        vl[x] ? hl[x] += d : slk[x] -= d;
      for (int x = 1; x <= n; ++x) if (vr[x]) hr[x] -= d;
      for (int x = 1; x <= n; ++x) if (!check(x)) return;
    }
  }
  KM(int n_, const auto &w) : n(n_), ans(0),
    hl(n + 1), hr(n + 1), fl(n + 1, -1), fr(fl), pre(n + 1), q(n + 1) {
    for (int i = 1; i <= n; ++i) {
      hl[i] = -LINF;
      for (int j = 1; j <= n; ++j) hl[i] = max(hl[i], (ll)w[i][j]);
    }
    for (int i = 1; i <= n; ++i) bfs(w, i);
    for (int i = 1; i <= n; ++i) ans += w[i][fl[i]];
  }
};
