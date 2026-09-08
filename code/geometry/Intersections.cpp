// m=0: segment, m=1: ray from l.a to l.b, m=2: line
bool banana(Line ls, int ms, Line lt, int mt, int strict) {
  auto on = [&](Line l, int m, Pt p) {
    if (ori(l.a, l.b, p) != 0) return false;
    if (m && abs2(l.a - p) > abs2(l.b - p)) return true;
    return m == 2 || sgn((p - l.a) * (p - l.b)) <= -strict;
  };
  if (sameVec(ls, lt, 0)) {
    return on(ls, ms, lt.a) || on(ls, ms, lt.b) ||
           on(lt, mt, ls.a) || on(lt, mt, ls.b);
  }
  auto good = [&](Line l, int m, Line o) {
    if (m && abs((l.a - o.a) ^ (l.a - o.b)) >
        abs((l.b - o.a) ^ (l.b - o.b))) return true;
    return m == 2 ||
      ori(l.a, o.a, o.b) * ori(l.b, o.a, o.b) == -1;
  };
  if (good(ls, ms, lt) && good(lt, mt, ls)) return 1;
  if (!strict) {
    if (mt != 2 && on(ls, ms, lt.a)) return 1;
    if (mt == 0 && on(ls, ms, lt.b)) return 1;
    if (ms != 2 && on(lt, mt, ls.a)) return 1;
    if (ms == 0 && on(lt, mt, ls.b)) return 1;
  }
  return 0;
}
// becareful when two lines are parallel
auto bananaPoint(Line a, Line b) {
  auto abc = (a.b - a.a) ^ (b.a - a.a);
  auto abd = (a.b - a.a) ^ (b.b - a.a);
  return make_pair(b.b * abc - b.a * abd, abc - abd);
}