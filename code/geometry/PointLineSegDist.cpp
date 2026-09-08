// T = double
double pointLineDist(Pt p, Line L)
{ return fabs(((L.b - L.a) ^ (p - L.a)) / abs(L.b - L.a)); }
double pointSegDist(Pt p, Pt a, Pt b) {
  if (a == b) return abs(p - a);
  if (sgn((b - a) * (p - a)) >= 0 &&
      sgn((a - b) * (p - b)) >= 0)
    return pointLineDist(p, {a, b});
  return min(abs(p - a), abs(p - b));
}