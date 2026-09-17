// sqrtMod(a, p) finds x with x^2 = a (mod p).
// Tonelli-Shanks runs in O(log^2 p), usually O(log p).

// Pow(b,e,p): 3-arg overload
ll Pow(ll b, ll e, ll p) {
  ll r = 1;
  for (; e; e >>= 1, b = b * b % p)
    if (e & 1) r = r * b % p;
  return r;
}

ll sqrtMod(ll a, ll p) {
  a %= p;
  if (a < 0) a += p;
  if (a == 0) return 0;
  assert(Pow(a, (p - 1) / 2, p) == 1);
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
    if (m == 0) return x;
    ll gs = Pow(g, 1LL << (r - m - 1), p);
    g = gs * gs % p;
    x = x * gs % p;
    b = b * g % p;
  }
}
