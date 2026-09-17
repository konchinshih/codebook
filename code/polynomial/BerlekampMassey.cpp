// Returns c with s[i] = sum c[j]*s[i-1-j].
// O(n^2); provide at least 2k samples for order k.
using Poly = vector<ll>;

Poly berlekampMassey(Poly s) {
  int n = sz(s), L = 0, m = 0;
  Poly C(n), B(n), T;
  C[0] = B[0] = 1;
  ll b = 1;
  for (int i = 0; i < n; i++) {
    m++;
    ll d = s[i] % mod;
    for (int j = 1; j <= L; j++)
      d = add(d, mul(C[j], s[i - j]));
    if (!d) continue;
    T = C;
    ll coef = mul(d, Pow(b, mod - 2));
    for (int j = m; j < n; j++)
      C[j] = sub(C[j], mul(coef, B[j - m]));
    if (2 * L > i) continue;
    L = i + 1 - L;
    B = T, b = d, m = 0;
  }
  C.resize(L + 1);
  C.erase(C.begin());
  for (ll& x : C) x = x ? mod - x : 0;
  return C;
}
