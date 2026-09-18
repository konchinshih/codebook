// Author: Gino, Range Affine Segment Tree
// Maintain b*a[i]+c, support range modifications of b, c
// ================== RANGE MAX/MIN ==================
struct S { ll mx; };
struct T { ll b, c; };  // bx + c, b >= 0
inline S op(S a, S b) { return {max(a.mx, b.mx)}; }
inline S e() { return {LLONG_MIN}; }   // min: LLONG_MAX
inline S mapping(T f, S x) {
  if (x.mx == LLONG_MIN) return x;     // keep -inf
  return {f.b * x.mx + f.c}; }
inline T composition(T f, T g) {
  return {f.b * g.b, f.b * g.c + f.c};
}
inline T id() { return {1, 0}; }
// ==================== RANGE SUM ====================
struct S { ll x, len; };
struct T { ll b, c; };  // bx + c
inline S op(S a, S b) { return {
  (a.x + b.x) % mod,
  a.len + b.len,
}; }
inline S e() { return {0, 0}; }
inline S mapping(T f, S x) { return {
  (f.b * x.x + f.c * x.len) % mod,
  x.len,
}; }
inline T composition(T f, T g) { return {
// fb(gb*x + gc) + fc = (fb*gb)x + (fb*gc + fc)
  (f.b * g.b) % mod,
  (f.b * g.c + f.c) % mod,
}; }
inline T id() { return {1, 0}; }
