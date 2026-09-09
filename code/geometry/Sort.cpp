// Dependency: cmp(), btwAngle()
// cmp in Basic: polar angle sort
// all points are on line ab. closer to a: front
bool cmpLine(Pt s, Pt t, Pt a, Pt b) {
  Pt v = a - b;
  if (sgn(v.x)) return sgn(s.x - t.x) == sgn(v.x);
  return sgn(s.y - t.y) == sgn(v.y);
}
// intersect points polar angle sort, deno: positive
bool cmpFractionPolar(pair<Pt, ll> o,
    pair<Pt, ll> s, pair<Pt, ll> t) {
  Pt u = s.first * o.second - o.first * s.second;
  Pt v = t.first * o.second - o.first * t.second;
  return cmp(u, v);
}
struct Seg {
  Pt a, b; // a.x < b.x
  bool operator<(const Seg& o) const {
    if (a == o.a) return ori(o.b, a, b) == 1;
    if (a.x <= o.a.x) return ori(o.a, a, b) == 1;
    return ori(a, o.a, o.b) == -1;
} };
struct PolarSeg {
  Pt a, b; // ori(Pt(0, 0), a, b) > 0
  bool operator<(const PolarSeg& o) const {
    if (a == o.a) return ori(o.b, a, b) == -1;
    if (btwAngle(Pt(0, 0), a, b, o.a, 0))
      return ori(o.a, a, b) == -1;
    return ori(a, o.a, o.b) == 1;
} };
struct Arc {
  // contain(a, b): circle a inside circle b
  Cir c; int id, s; // 0 -> up, 1 -> down
  bool operator<(const Arc& b) const {
    if (id == b.id) return s < b.s;
    if (contain(c, b.c)) return b.s == 1;
    if (contain(b.c, c)) return s == 0;
    if (c.o.y == b.c.o.y) return id < b.id;
    return c.o.y > b.c.o.y;
} };