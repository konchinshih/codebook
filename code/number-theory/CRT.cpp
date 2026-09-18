// Solves x = a (mod m), x = b (mod n).
// m,n need not be coprime; asserts if no solution.
// Needs m*n < 2^62-ish; extgcd returns a*x+b*y=g.
ll extgcd(ll a, ll b, ll& x, ll& y) {
  if (!b) return x = 1, y = 0, a;
  ll g = extgcd(b, a % b, y, x);
  return y -= a / b * x, g;
}

ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = extgcd(m, n, x, y);
  assert((a - b) % g == 0);
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}
