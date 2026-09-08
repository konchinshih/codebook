struct P3 {
  double x, y, z;
  P3(double _x = 0, double _y = 0, double _z = 0) :
      x(_x), y(_y), z(_z) {}
  P3 operator+(const P3& o) const {
    return P3(x + o.x, y + o.y, z + o.z); }
  P3 operator-(const P3& o) const {
    return P3(x - o.x, y - o.y, z - o.z); }
  P3 operator*(double k) const {
    return P3(x * k, y * k, z * k); }
  P3 operator/(double k) const {
    return P3(x / k, y / k, z / k); }
  double operator*(const P3& o) const {
    return x * o.x + y * o.y + z * o.z; }
  P3 operator^(const P3& o) const {
    return P3(y * o.z - z * o.y,
      z * o.x - x * o.z, x * o.y - y * o.x); }
};
double abs2(P3 o) { return o * o; }
double abs(P3 o) { return sqrt(abs2(o)); }
P3 cross3(P3 a, P3 b, P3 c) { return (b - a) ^ (c - a); }
double area(P3 a, P3 b, P3 c) { 
  return abs(cross3(a, b, c)); }
double volume(P3 a, P3 b, P3 c, P3 d) {
  return cross3(a, b, c) * (d - a); }
bool coplanar(P3 a, P3 b, P3 c, P3 d) {
  return fabs(volume(a, b, c, d)) < eps; }
P3 proj(P3 o, P3 a, P3 b, P3 c) {
  P3 n = cross3(a, b, c);
  return o - n * ((o - a) * (n / abs2(n))); }
P3 linePlaneIntersect(P3 u, P3 v, P3 a, P3 b, P3 c) {
  // intersection of line uv and plane abc
  P3 n = cross3(a, b, c);
  double s = n * (u - v);
  if (fabs(s) < eps) return {-1, -1, -1};
  return v + (u - v) * ((n * (a - v)) / s); }