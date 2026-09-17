const ll mod = 998244353;
ll add(ll a, ll b) { return (a += b) >= mod ? a - mod : a; }
ll sub(ll a, ll b) { return (a -= b) < 0 ? a + mod : a; }
ll mul(ll a, ll b) { return a * b % mod; }
ll Pow(ll b, ll e) {
  ll r = 1;
  for (; e; e >>= 1, b = mul(b, b)) if (e & 1) r = mul(r, b);
  return r;
}
