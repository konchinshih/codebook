int ud(Pt a) // 0: upper half (incl. +x axis), 1: lower
{ return !sgn(a.y) ? sgn(a.x) < 0 : a.y < 0; }
bool cmp(Pt a, Pt b) // polar angle in [0, 2PI)
{ return ud(a) == ud(b) ? sgn(a ^ b) > 0 : ud(a) < ud(b); }
bool sameVec(Pt a, Pt b, int d)//d=0: parallel,d=1: same dir
{ return !sgn(a ^ b) && sgn(a * b) > d * 2 - 2; }
bool sameVec(Line a, Line b, int d)
{ return sameVec(a.b - a.a, b.b - b.a, d); }
Pt rot90(Pt a) { return {-a.y, a.x}; } // CCW
Pt ref(Pt a) { return ud(a) ? Pt(-a.x, -a.y) : a; }
T dbarea(vector<Pt>& p) { // doubled signed area, CCW > 0
  T res = 0; for (int i = 0; i < sz(p); i++)
    res += p[i] ^ p[(i+1) % sz(p)];
  return res; }
// ---- T = double ----
const double PI = acos(-1);
double normalize(double x) { // to [0, 2pi)
  while (x < -eps) x += PI * 2;
  while (x > PI * 2 + eps) x -= PI * 2;
  return x; }
double theta(Pt a) { return normalize(atan2(a.y, a.x)); }
Pt unit(Pt a) { return a / abs(a); }
Pt rot(Pt a, double o) { // CCW
  double c = cos(o), s = sin(o);
  return Pt(c * a.x - s * a.y, s * a.x + c * a.y);
}
Pt projVec(Pt a, Pt b, Pt c) // vector ac proj to ab
{ return (b - a) * ((c - a) * (b - a)) / abs2(b - a); }
Pt projPt(Pt a, Pt b, Pt c) // point c proj to ab
{ return projVec(a, b, c) + a; }