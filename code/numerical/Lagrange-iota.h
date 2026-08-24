
/**
 * Author: koukanni
 * Date: 2025
 * License: CC0
 * Source: 
 * Description: Lagrange interpolation for polynomial evaluation at integer points.
 * Given polynomial values f[0], f[1], ..., f[n-1], computes f(c).
 * Time: O(n)
 * Status: tested
 */
Mint lagrange_iota(const vector<Mint> &f, const int c) {
  const int n = int(size(f));
  if (c < n) {
    return f[c];
  }
  vector<Mint> fac(n), ifac(n);
  fac[0] = 1;
  for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * i;
  ifac[n - 1] = fac[n - 1].inv();
  for (int i = n - 1; i >= 1; i--) ifac[i - 1] = ifac[i] * i;
  vector<Mint> g(n);
  for (int i = 0; i < n; i++) {
    g[i] = f[i] * ifac[i] * ifac[n - 1 - i];
    if ((n - 1 - i) & 1) g[i] *= -1;
  }
  vector<Mint> lp(n + 1), rp(n + 1);
  lp[0] = rp[n] = 1;
  for (int i = 0; i < n; i++) lp[i + 1] = lp[i] * Mint(c - i);
  for (int i = n - 1; i >= 0; i--) rp[i] = rp[i + 1] * Mint(c - i);
  Mint ans = 0;
  for (int i = 0; i < n; i++) ans += g[i] * lp[i] * rp[i + 1];
  return ans;
}