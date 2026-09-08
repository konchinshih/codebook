// T = double
double areaSector(Pt pa, Pt pb, double r) {
  if (abs(pa) < abs(pb)) swap(pa, pb);
  if (abs(pb) < eps) return 0;
  double S, h, t;
  double a = abs(pb), b = abs(pa), c = abs(pb - pa);
  double cosB = pb * (pb - pa) / a / c;
  double B = acos(cosB);
  double cosC = pa * pb / a / b, C = acos(cosC);
  if (a > r) {
    S = C / 2 * r * r;
    h = a * b * sin(C) / c;
    if (h < r && B < PI / 2)
      S -= acos(h / r) * r * r - h * sqrt(r * r - h * h);
  } else if (b > r) {
    t = PI - B - asin(sin(B) / r * a);
    S = 0.5 * a * r * sin(t) + (C - t) / 2 * r * r;
  } else {
    S = 0.5 * sin(C) * a * b;
  }
  return S;
}
double areaPolyCircle(vector<Pt> poly, Pt O, double r) {
  double S = 0;
  int n = sz(poly);
  for (int i = 0; i < n; i++)
    S += areaSector(poly[i] - O,
      poly[(i + 1) % n] - O, r) *
      ori(O, poly[i], poly[(i + 1) % n]);
  return fabs(S);
}
