// get edge index: check (0, a), (0, b) first
// then after binary search, check (a, b)
bool inConvex(vector<Pt>& C, Pt p, bool strict = true) {
  // only works when no three points are collinear
  int a = 1, b = sz(C) - 1, r = !strict;
  if (sz(C) == 0) return false;
  if (sz(C) < 3) return r && onseg(p, C[0], C.back());
  if (ori(C[0], C[a], C[b]) > 0) swap(a, b);
  if (ori(C[0], C[a], p) >= r ||
      ori(C[0], C[b], p) <= -r) return false;
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (ori(C[0], C[c], p) > 0 ? b : a) = c;
  }
  return ori(C[a], C[b], p) < r;
}
// -1: out, 0: edge, 1: in
int inPoly(vector<Pt> poly, Pt o, int strict) {
  int cnt = 0;
  for (int i = 0; i < sz(poly); i++) {
    Pt a = poly[i], b = poly[(i + 1) % sz(poly)];
    if (onseg(o, a, b)) return !strict;
    cnt ^= ((o.y < a.y) - (o.y < b.y)) * ori(o, a, b) > 0;
  }
  return cnt ? 1 : -1;
}
// relation of q with circumcircle; T = long long
bool inCC(array<Pt, 3> p, Pt q) {
  __int128 det = 0;
  for (int i = 0; i < 3; i++)
    det += __int128(abs2(p[i]) - abs2(q)) *
      ((p[(i + 1) % 3] - q) ^ (p[(i + 2) % 3] - q));
  return det > 0; // in: >0, on: =0, out: <0
}