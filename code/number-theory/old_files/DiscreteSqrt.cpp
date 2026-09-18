// Author: ckiseki
// find solution for x^2 = n (mod P)
// O(log^2 P)
int get_root(int n, int P) { // ensure 0 <= n < p
  if (P == 2 or n == 0) return n;
  auto check = [&](lld x) {
    return modpow(int(x), (P - 1) / 2, P); };
  if (check(n) != 1) return -1;
  mt19937 rnd(7122); lld z = 1, w;
  while (check(w = (z * z - n + P) % P) != P - 1)
    z = rnd() % P;
  const auto M = [P, w](auto &u, auto &v) {
    auto [a, b] = u; auto [c, d] = v;
    return make_pair((a * c + b * d % P * w) % P,
        (a * d + b * c) % P);
  };
  pair<lld, lld> r(1, 0), e(z, 1);
  for (int q = (P + 1) / 2; q; q >>= 1, e = M(e, e))
    if (q & 1) r = M(r, e);
  return int(r.first); // sqrt(n) mod P where P is prime
}
