// T = double
Pt circenter(Pt a, Pt b, Pt c) { // r = abs(o - a)
  b = b-a, c = c-a; double m = 2 * (b^c);
  Pt o = {(abs2(b) * c.y - abs2(c) * b.y) / m,
          (abs2(c) * b.x - abs2(b) * c.x) / m};
  return o + a;
}
Pt incenter(Pt a, Pt b, Pt c) { // r = 2 * area / s
  double x = abs(b - c), y = abs(c - a);
  double z = abs(a - b), s = x + y + z;
  return (a*x + b*y + c*z) / s;
}
Pt centroid(Pt a, Pt b, Pt c) { return (a + b + c) / 3; }
Pt orthocenter(Pt a, Pt b, Pt c) {
  return centroid(a, b, c) * 3 - circenter(a, b, c) * 2;
}