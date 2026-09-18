// O(1) gcd(x, y) for 1 <= x, y <= n after O(n) init.
// Use when ~1e7+ gcd queries on values <= n (e.g. sum of
// gcd(a[i], a[j]), gcd-convolution); else std::gcd is fine.
// Usage: GCD<N, SQRT> G; (global) G.init(n); G.fastGCD(x, y)
//   N > n, SQRT > sqrt(n). Memory 20 bytes * N.
// -O2: n=1e6 init 17ms, 20MB; n=1e7 init 0.2s, 200MB.
// 1e7 random queries: 0.2s (std::gcd 0.6-0.7s, ~3x).
template <size_t N, size_t SQRT>
struct GCD {
  int sq, minp[N], gcd_table[SQRT][SQRT];
  vector<int> primes;
  array<int, 3> fac[N];
  void init(const int n) {
    sq = int(sqrt(n));
    for (int i = 0; i <= sq; ++i)
      gcd_table[0][i] = gcd_table[i][0] = i;
    for (int i = 1; i <= sq; ++i)
      for (int j = 1; j <= i; ++j)
        gcd_table[i][j] = gcd_table[j][i] = gcd_table[j][i % j];
    for (int i = 1; i <= n; ++i)
      minp[i] = i;
    fac[1] = {1, 1, 1};
    for (int i = 2; i <= n; ++i) {
      if (minp[i] == i) {
        primes.push_back(i);
        fac[i] = {1, 1, i};
      }
      for (const int &p : primes) {
        if (i * p > n) break;
        const int j = i * p;
        minp[j] = p;
        fac[j] = fac[i];
        fac[j][0] *= p;
        ranges::sort(fac[j]);
        if (i % p == 0) break;
  } } }
  int fastGCD(int x, int y) {
    int g = 1;
    for (const int &f : fac[x]) {
      int c = 1;
      if (f <= sq) c = gcd_table[f][y % f];
      else if (y % f == 0) c = f;
      y /= c; g *= c;
    }
    return g;
} };
