static inline ll gcd_ll(ll a, ll b) {
  return __gcd(a, b); // non-negative
}

static inline ll lcm_ll(ll a, ll b) {
  if (a == 0 || b == 0) return 0;
  ll g = __gcd(a, b);
  __int128 t = (__int128)(a / g) * (__int128)b; // avoid overflow
  if (t < 0) t = -t;
  return (ll)t; // may overflow if result > LLONG_MAX
}

static inline __int128 lcm_i128(ll a, ll b) {
  if (a == 0 || b == 0) return 0;
  ll g = __gcd(a, b);
  __int128 t = (__int128)(a / g) * (__int128)b;
  return t < 0 ? -t : t;
}

