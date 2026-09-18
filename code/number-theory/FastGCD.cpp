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
