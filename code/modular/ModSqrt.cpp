// sqrtMod(a, p) finds x with x^2 = a (mod p), p prime
// 2 Roots: (x, p - x), returns the smaller one
// (Tonelli-Shanks) O(log^2 p), usually O(log p).
ll Pow(ll b, ll e, ll p) { ll r = 1;
  for (; e; e >>= 1, b = b * b % p) if (e & 1) r = r * b % p;
  return r; }
ll sqrtMod(ll a, ll p) { a = (a % p + p) % p;
  if (p == 2) return a;
  if (a == 0) return 0;
  if (Pow(a, (p - 1) / 2, p) != 1) return -1;
  if (p % 4 == 3) return Pow(a, (p + 1) / 4, p);
  ll s = p - 1, n = 2;
  int r = 0, m;
  while (s % 2 == 0) r++, s /= 2;
  while (Pow(n, (p - 1) / 2, p) != p - 1) n++;
  ll x = Pow(a, (s + 1) / 2, p);
  ll b = Pow(a, s, p), g = Pow(n, s, p);
  for (;; r = m) {
    ll t = b;
    for (m = 0; m < r && t != 1; m++) t = t * t % p;
    if (m == 0) return min(x, p - x);
    ll gs = Pow(g, 1LL << (r - m - 1), p);
    g = gs * gs % p;
    x = x * gs % p;
    b = b * g % p;
} }
