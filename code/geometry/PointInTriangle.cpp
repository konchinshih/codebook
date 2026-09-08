// number of p with a < p < b and ori(p, a, b) < 0
int under(Pt a, Pt b) {}
// number of points with a < p < b and ori(p, a, b) = 0
int edge(Pt a, Pt b) {}
// check if this number is calculated
bool check(Pt p) {}
// number of points that strictly inside the triangle
int inTri(array<Pt, 3> arr) {
  sort(all(arr));
  auto [a, b, c] = arr;
  int x = ori(b, a, c);
  if (x == 0) return 0;
  if (x == 1)
    return under(a, b) + under(b, c) -
      under(a, c) - edge(a, c);
  return under(a, c) - under(a, b) -
    under(b, c) - edge(a, b) - edge(b, c) - check(b);
}