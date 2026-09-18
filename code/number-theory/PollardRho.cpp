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
vector<ll> factor(ll x) {
  if (x == 1) return {};
  if (isPrime(x)) return {x};
  ll d = pollard(x);
  auto l = factor(d), r = factor(x / d);
  l.insert(l.end(), all(r));
  return l;
}
vector<pair<ll, int>> factorization(ll x) {
  auto f = factor(x); sort(all(f));
  vector<pair<ll, int>> res;
  for (ll p : f)
    if (!res.empty() && res.back().first == p) res.back().second++;
    else res.emplace_back(p, 1);
  return res;
}
