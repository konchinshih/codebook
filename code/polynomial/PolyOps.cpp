// needs: NTT
// needs: ModSqrt
// polyInv(a): inverse modulo x^n, a[0] != 0.
Poly polyInv(Poly a) {
  int n = sz(a);
  Poly res(1, Pow(a[0], mod - 2));
  for (int m = 1; m < n; m <<= 1) {
    if (n < m * 2) a.resize(m * 2);
    Poly v1(a.begin(), a.begin() + m * 2), v2 = res;
    v1.resize(m * 4), v2.resize(m * 4);
    ntt(v1), ntt(v2);
    for (int i = 0; i < m * 4; i++)
      v1[i] = mul(mul(v1[i], v2[i]), v2[i]);
    ntt(v1, true);
    res.resize(m * 2);
    for (int i = 0; i < m; i++) res[i] = add(res[i], res[i]);
    for (int i = 0; i < m * 2; i++)
      res[i] = sub(res[i], v1[i]);
  }
  res.resize(n);
  return res;
}

// polyDiv(a,b): a = bQ + R, b.back() != 0.
pair<Poly, Poly> polyDiv(Poly a, Poly b) {
  int n = sz(a), m = sz(b), k = n - m + 1;
  if (n < m) return {{0}, a};
  Poly ra = a, rb = b;
  reverse(all(ra)), ra.resize(k);
  reverse(all(rb)), rb.resize(k);
  Poly q = polyMul(ra, polyInv(rb), k);
  reverse(all(q));
  Poly res = polyMul(b, q), r(m - 1);
  for (int i = 0; i < m - 1; i++) r[i] = sub(a[i], res[i]);
  return {q, r};
}

// polySqrt(a): square root modulo x^n; asserts if a[0]
// not a residue.
Poly polySqrt(Poly a) {
  if (a.empty()) return {0};
  int n = sz(a), m = 0;
  while (m < n && a[m] == 0) m++;
  if (m == n) return Poly(n);
  if (m & 1) return {-1};
  a.erase(a.begin(), a.begin() + m);
  ll z = sqrtMod(a[0], mod);
  Poly q(1, z);
  ll inv2 = (mod + 1) / 2;
  for (int k = 1; k < n - m + 1; k <<= 1) {
    if (n - m < k * 2) a.resize(k * 2);
    q.resize(k * 2);
    Poly f2 = polyMul(q, q, k * 2);
    for (int i = 0; i < k * 2; i++) f2[i] = sub(f2[i], a[i]);
    f2 = polyMul(f2, polyInv(q), k * 2);
    for (int i = 0; i < k * 2; i++)
      q[i] = sub(q[i], mul(f2[i], inv2));
  }
  q.resize(n - m);
  Poly res(n);
  for (int i = 0; i < sz(q); i++) res[i + m / 2] = q[i];
  return res;
}

Poly deriv(Poly a) {
  int n = sz(a);
  Poly res(max(0, n - 1));
  for (int i = 0; i < n - 1; i++)
    res[i] = mul(a[i + 1], i + 1);
  return res;
}

Poly integ(Poly a) {
  int n = sz(a);
  Poly res(n + 1);
  for (int i = 0; i < n; i++)
    res[i + 1] = mul(a[i], Pow(i + 1, mod - 2));
  return res;
}

// polyLn(a): formal logarithm, a[0] = 1.
Poly polyLn(Poly a) {
  int n = sz(a);
  if (n == 1) return {0};
  Poly d = deriv(a);
  a.pop_back();
  return integ(polyMul(d, polyInv(a), n - 1));
}

// polyExp(a): formal exponential, a[0] = 0.
Poly polyExp(Poly a) {
  int n = sz(a);
  Poly q(1, 1);
  a[0] = add(a[0], 1);
  for (int m = 1; m < n; m <<= 1) {
    if (n < m * 2) a.resize(m * 2);
    Poly g(a.begin(), a.begin() + m * 2), h = q;
    h.resize(m * 2), h = polyLn(h);
    for (int i = 0; i < m * 2; i++) g[i] = sub(g[i], h[i]);
    q = polyMul(g, q, m * 2);
  }
  q.resize(n);
  return q;
}

Poly polyPow(Poly a, ll k) {
  int n = sz(a), m = 0;
  Poly ans(n);
  if (!k) return ans[0] = 1, ans;
  while (m < n && a[m] == 0) m++;
  if (k && m && (k >= n || k * m >= n)) return ans;
  if (m == n) return ans[0] = 1, ans;
  int lead = m * k;
  Poly b(a.begin() + m, a.end());
  ll base = Pow(b[0], k), inv = Pow(b[0], mod - 2);
  for (int i = 0; i < n - m; i++) b[i] = mul(b[i], inv);
  b = polyLn(b);
  for (ll& x : b) x = mul(x, k % mod);
  b = polyExp(b);
  for (int i = lead; i < n; i++)
    ans[i] = mul(b[i - lead], base);
  return ans;
}

vector<ll> evaluate(Poly a, vector<ll> x) {
  if (x.empty()) return {};
  int n = sz(x);
  vector<Poly> up(n * 2);
  for (int i = 0; i < n; i++) up[i + n] = {sub(0, x[i]), 1};
  for (int i = n - 1; i > 0; i--)
    up[i] = polyMul(up[i * 2], up[i * 2 + 1]);
  vector<Poly> down(n * 2);
  down[1] = polyDiv(a, up[1]).second;
  for (int i = 2; i < n * 2; i++)
    down[i] = polyDiv(down[i >> 1], up[i]).second;
  vector<ll> y(n);
  for (int i = 0; i < n; i++) y[i] = down[i + n][0];
  return y;
}

Poly interpolate(vector<ll> x, vector<ll> y) {
  int n = sz(x);
  vector<Poly> up(n * 2);
  for (int i = 0; i < n; i++) up[i + n] = {sub(0, x[i]), 1};
  for (int i = n - 1; i > 0; i--)
    up[i] = polyMul(up[i * 2], up[i * 2 + 1]);
  Poly a = evaluate(deriv(up[1]), x);
  for (int i = 0; i < n; i++)
    a[i] = mul(y[i], Pow(a[i], mod - 2));
  vector<Poly> down(n * 2);
  for (int i = 0; i < n; i++) down[i + n] = {a[i]};
  for (int i = n - 1; i > 0; i--) {
    Poly lhs = polyMul(down[i * 2], up[i * 2 + 1]);
    Poly rhs = polyMul(down[i * 2 + 1], up[i * 2]);
    down[i].resize(sz(lhs));
    for (int j = 0; j < sz(lhs); j++)
      down[i][j] = add(lhs[j], rhs[j]);
  }
  return down[1];
}
