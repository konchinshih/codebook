// factorization(x): sorted (p, e) with x = prod p^e, x < 2^62
// 1e18 semiprime ~0.5ms; needs: MillerRabin
ll pollard(ll n) {
  ll x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  auto f = [&](ll x) { return mul(x, x, n) + i; };
  while (t++ % 40 || gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = mul(prd, abs(x - y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}
vector<pair<ll, int>> factorization(ll x) {
  map<ll, int> cnt;
  auto rec = [&](auto&& self, ll x) -> void {
    if (x == 1) return;
    if (isPrime(x)) { cnt[x]++; return; }
    ll d = pollard(x);
    self(self, d), self(self, x / d);
  };
  rec(rec, x);
  return {all(cnt)};
}
