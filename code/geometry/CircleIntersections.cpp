// Dependency: cycTsearch(); T = double for circles
vector<Pt> circleLineIntersect(Cir c, Line l) {
  Pt p = l.a + (l.b - l.a) *
    ((c.o - l.a) * (l.b - l.a)) / abs2(l.b - l.a);
  double s = (l.b - l.a) ^ (c.o - l.a);
  double h2 = c.r * c.r - s * s / abs2(l.b - l.a);
  if (sgn(h2) == -1) return {};
  if (sgn(h2) == 0) return {p};
  Pt h = (l.b - l.a) / abs(l.b - l.a) * sqrt(h2);
  return {p - h, p + h};
}
// covered area of c1: arc from res[0] to res[1], CCW
vector<Pt> circlesIntersect(Cir c1, Cir c2) {
  double d2 = abs2(c1.o - c2.o), d = sqrt(d2);
  if (d < max(c1.r, c2.r) - min(c1.r, c2.r) ||
      d > c1.r + c2.r) return {};
  Pt u = (c1.o + c2.o) / 2 +
    (c1.o - c2.o) *
    ((c2.r * c2.r - c1.r * c1.r) / (2 * d2));
  double A = sqrt((c1.r + c2.r + d) *
    (c1.r - c2.r + d) * (c1.r + c2.r - d) *
    (-c1.r + c2.r + d));
  Pt v = rot90(c2.o - c1.o) * A / (2 * d2);
  if (sgn(v.x) == 0 && sgn(v.y) == 0) return {u};
  return {u - v, u + v};
}
vector<pii> convexLineIntersect(vector<Pt>& C, Line la) {
  auto dis = [&](int p) {
    return (la.b - la.a) ^ (C[p] - la.a);
  };
  auto gao = [&](int s) {
    return cycTsearch(sz(C), [&](int i, int j) {
      return sgn(dis(i) - dis(j)) == s;
    });
  };
  int x = gao(1), y = gao(-1), n = sz(C);
  if (sgn(dis(x)) < 0 || sgn(dis(y)) > 0) return {};
  if (sgn(dis(x)) == 0 || sgn(dis(y)) == 0) {
    int v = ((sgn(dis(x)) == 0 ? x : y) + n - 1) % n;
    vector<pii> vec;
    for (int i = 0; i < 3; i++, v = (v + 1) % n)
      if (sgn(dis(v)) == 0) vec.emplace_back(v, v);
    return vec;
  }
  auto get = [&](int l, int r, int s) {
    while ((l + 1) % n != r) {
      int m = ((l + r + (l < r ? 0 : n)) / 2) % n;
      (sgn(dis(m)) == s ? l : r) = m;
    }
    if (sgn(dis(r)) == 0) return pii(r, r);
    return pii(l, r);
  };
  return {get(x, y, 1), get(y, x, -1)};
}
