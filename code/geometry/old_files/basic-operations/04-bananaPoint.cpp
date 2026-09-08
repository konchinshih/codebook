// Dependency: 02, T should be double
Pt intersect_point(Pt a, Pt b, Pt c, Pt d) {
  if (onseg(c, a, b)) return c;
  if (onseg(d, a, b)) return d;
  if (onseg(a, c, d)) return a;
  if (onseg(b, c, d)) return b;
  T s = abs(mv(a, b) ^ mv(a, c));
  T t = abs(mv(a, b) ^ mv(a, d));
  return d * (s/(s+t)) + c * (t/(s+t));
}

