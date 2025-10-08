// Author: ckiseki
// find x^? = y (mod M)
// O(sqrt(M))
template<typename Int>
Int BSGS(Int x, Int y, Int M) {
  // x^? \equiv y (mod M)
  Int t = 1, c = 0, g = 1;
  for (Int M_ = M; M_ > 0; M_ >>= 1) g = g * x % M;
  for (g = gcd(g, M); t % g != 0; ++c) {
    if (t == y) return c;
    t = t * x % M;
  }
  if (y % g != 0) return -1;
  t /= g, y /= g, M /= g;
  Int h = 0, gs = 1;
  for (; h * h < M; ++h) gs = gs * x % M;
  unordered_map<Int, Int> bs;
  for (Int s = 0; s < h; bs[y] = ++s) y = y * x % M;
  for (Int s = 0; s < M; s += h) {
    t = t * gs % M;
    if (bs.count(t)) return c + s + h - bs[t];
  }
  return -1;
}
