//Author:Gino, simple polygons any orientation, O((sum n)^2)
// T = ll: exact (|coord| <= 1e9); T = double: also works
double polysUnionArea(vector<vector<Pt>> poly) {
  struct Fr { T p, q; }; // p / q, q > 0
  auto lt = [](Fr a, Fr b) {
//return (__int128)a.p * b.q < (__int128)b.p * a.q;  // if T == long long
    return a.p * b.q < b.p * a.q;
  };
  auto val = [&](Fr a) { // clamp to [0, 1], to double
    if (lt(a, {0, 1})) return 0.;
    if (lt({1, 1}, a)) return 1.;
    return (double)a.p / a.q;
  };
  auto get = [&](int i, int e) {
    return poly[i][(e + 1) % sz(poly[i])];
  };
  for (auto& p : poly)
    if (dbarea(p) < 0) reverse(all(p));
  double sum = 0;
  for (int i = 0; i < sz(poly); i++)
    for (int e = 0; e < sz(poly[i]); e++) {
      Pt s = poly[i][e], t = get(i, e);
      vector<pair<Fr, int>> c = {{{0, 1}, 0}, {{1, 1}, 0}};
      for (int j = 0; j < sz(poly); j++) {
        if (i == j) continue;
        for (int f = 0; f < sz(poly[j]); f++) {
          Pt a = poly[j][f], b = get(j, f);
          int ta = ori(s, t, a), tb = ori(s, t, b);
          if (!ta && !tb) {
            if (j < i && sgn((b-a) * (t-s)) > 0) {
              T d = abs2(t-s);
              c.pb({Fr{(a-s) * (t-s), d}, 1});
              c.pb({Fr{(b-s) * (t-s), d}, -1});
            }
          } else if ((ta >= 0) != (tb >= 0)) {
            T x = (b-a) ^ (s-a), y = (b-a) ^ (t-a);
            if (x < y) x = -x, y = -y;
            c.pb({Fr{x, x-y}, ta >= 0 ? 1 : -1});
          }
        }
      }
      sort(all(c), [&](auto& u, auto& v)
        { return lt(u.first, v.first); });
      double z = val(c[0].first), r = 0;
      for (int k = 1, d = c[0].second; k < sz(c); k++) {
        double w = val(c[k].first);
        if (!d) r += w - z;
        d += c[k].second, z = w;
      }
      sum += (s^t) * r;
    }
  return sum / 2;
}