// Dependency: cycTsearch(); T = double for circle tangents
auto circlePointTangent(Cir c, Pt p) {
  vector<Line> res;
  double dSq = abs2(p - c.o);
  if (sgn(dSq - c.r * c.r) == 0) {
    res.push_back({p, p + rot90(p - c.o)});
  } else if (dSq > c.r * c.r) {
    double s = dSq - c.r * c.r;
    Pt v = p + (c.o - p) * s / dSq;
    Pt u = rot90(c.o - p) * sqrt(s) * c.r / dSq;
    res.push_back({p, v + u});
    res.push_back({p, v - u});
  }
  return res;
}
auto circlesTangent(Cir c1, Cir c2, int sign1) {
  // sign1 = 1 for outer tang, -1 for inter tang
  vector<Line> res;
  double dSq = abs2(c1.o - c2.o);
  if (sgn(dSq) == 0) return res;
  double d = sqrt(dSq);
  Pt v = (c2.o - c1.o) / d;
  double c = (c1.r - sign1 * c2.r) / d;
  if (c * c > 1) return res;
  double h = sqrt(max(0.0, 1.0 - c * c));
  for (int sign2 = 1; sign2 >= -1; sign2 -= 2) {
    Pt n = Pt(v.x * c - sign2 * h * v.y,
              v.y * c + sign2 * h * v.x);
    Pt p1 = c1.o + n * c1.r;
    Pt p2 = c2.o + n * (c2.r * sign1);
    if (sgn(p1.x - p2.x) == 0 &&
        sgn(p1.y - p2.y) == 0)
      p2 = p1 + rot90(c2.o - c1.o);
    res.push_back({p1, p2});
  }
  return res;
}
/* The point should be strictly out of hull
  return arbitrary point on the tangent line */
pii pointConvexTangent(vector<Pt>& C, Pt p) {
  auto gao = [&](int s) {
    return cycTsearch(sz(C), [&](int x, int y) {
      return ori(p, C[x], C[y]) == s;
    });
  };
  return pii(gao(1), gao(-1));
} // return (a, b), ori(p, C[a], C[b]) >= 0