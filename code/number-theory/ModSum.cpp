// modSum(to, c, k, m) sums (k*i+c) mod m for i < to.
// divSum computes the corresponding sum of floor((k*i+c)/m).
// Both run in O(log m).
using ull = unsigned long long;

ull sumsq(ull to) { return to / 2 * ((to - 1) | 1); }

ull divSum(ull to, ull c, ull k, ull m) {
  ull res = k / m * sumsq(to) + c / m * to;
  k %= m;
  c %= m;
  if (!k) return res;
  ull to2 = (to * k + c) / m;
  return res + (to - 1) * to2
    - divSum(to2, m - 1 - c, m, k);
}

ll modSum(ull to, ll c, ll k, ll m) {
  c = ((c % m) + m) % m;
  k = ((k % m) + m) % m;
  return to * c + k * sumsq(to) - m * divSum(to, c, k, m);
}
