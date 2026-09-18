// isPrime(n): deterministic for n < 2^63; 1e6 calls ~0.25s
// Pow(b, e, p) here is the same as ModSqrt's but with
// __int128 mul, so it is safe for p up to 2^63.
ll mul(ll a, ll b, ll p) { return (__int128)a * b % p; }
ll Pow(ll b, ll e, ll p) { ll r = 1;
  for (; e; e >>= 1, b = mul(b, b, p)) if (e & 1) r = mul(r, b, p);
  return r; }
bool isPrime(ll n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  ll s = __builtin_ctzll(n - 1), d = n >> s;
  for (ll a : A) {
    ll p = Pow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = mul(p, p, n);
    if (p != n - 1 && i != s) return 0;
  }
  return 1;
}
