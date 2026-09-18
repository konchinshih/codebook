// mod 998244353, Requirement: ModBasic.cpp
const int N = 1 << 20, G = 3;
using Poly = vector<ll>;

struct NTT {
  ll w[N];
  NTT() {
    ll dw = Pow(G, (mod - 1) / N);
    w[0] = 1;
    for (int i = 1; i < N; i++)
      w[i] = mul(w[i - 1], dw);
  }
  void operator()(Poly& a, bool inv = false) {
    int n = sz(a);
    for (int j = 1, x = 0; j < n - 1; j++) {
      for (int k = n >> 1; (x ^= k) < k; k >>= 1);
      if (j < x) swap(a[x], a[j]);
    }
    for (int L = 2; L <= n; L <<= 1) {
      int dx = N / L, dl = L >> 1;
      for (int i = 0; i < n; i += L)
        for (int j = i, x = 0; j < i + dl; j++, x += dx) {
          ll tmp = mul(a[j + dl], w[x]);
          a[j + dl] = sub(a[j], tmp);
          a[j] = add(a[j], tmp);
        }
    }
    if (inv) {
      reverse(1 + all(a));
      ll invn = Pow(n, mod - 2);
      for (ll& x : a) x = mul(x, invn);
  } }
} ntt;
// polyMul: a*b truncated to bound terms, O(n log n).
// Result length must be <= N.
Poly polyMul(Poly a, Poly b, int bound = N) {
  int m = sz(a) + sz(b) - 1, n = 1;
  while (n < m) n <<= 1;
  a.resize(n), b.resize(n);
  ntt(a), ntt(b);
  for (int i = 0; i < n; i++) a[i] = mul(a[i], b[i]);
  ntt(a, true);
  a.resize(min(m, bound));
  return a;
}
// NTT primes & primitive roots (p = c * 2^k + 1)
// max convolution length (|a|+|b|-1) = 2^k
// Prime = c * 2^k + 1               Root  Max len (2^k)
// 7681 = 15 * 2^9  + 1              17    512
// 12289 = 3  * 2^12 + 1             11    4096
// 40961 = 5  * 2^13 + 1             3     8192
// 65537 = 1  * 2^16 + 1             3     65536
// 786433 = 3  * 2^18 + 1            10    262144
// 5767169 = 11 * 2^19 + 1           3     524288
// 7340033 = 7  * 2^20 + 1           3     1048576
// 23068673 = 11 * 2^21 + 1          3     2097152
// 104857601 = 25 * 2^22 + 1         3     4194304
// 985661441 = 235* 2^22 + 1         3     4194304
// 998244353 = 119* 2^23 + 1         3     8388608
// 2810183681 = 335* 2^23 + 1        11    8388608
// 167772161 = 5  * 2^25 + 1         3     33554432
// 1107296257 = 33 * 2^25 + 1        10    33554432
// 469762049 = 7  * 2^26 + 1         3     67108864
// 2885681153 = 43 * 2^26 + 1        3     67108864
// 2013265921 = 15 * 2^27 + 1        31    134217728
// 605028353 = 577* 2^20 + 1         3     1048576
// 2061584302081 = 15 * 2^37 + 1     7     137438953472
// 2748779069441 = 5  * 2^39 + 1     3     549755813888
// 9223372036737335297 = (2^39-7)*2^24+1   3   16777216
// 1945555039024054273 = 27*2^56+1         5   72057594037927936
