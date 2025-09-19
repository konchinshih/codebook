// requires: using ll = long long; assumes m > 0 and e >= 0

static inline ll norm_mod(ll a, ll m) {
  a %= m; if (a < 0) a += m; return a;
}

static inline ll pow_mod_ll(ll a, long long e, ll m) {
  if (m == 1) return 0;                 // a^e mod 1 = 0
  __int128 base = norm_mod(a, m);
  __int128 res  = 1 % m;                // ensures e==0 -> 1 mod m
  while (e > 0) {
    if (e & 1) res = (res * base) % m;
    base = (base * base) % m;
    e >>= 1;
  }
  return (ll)res;                       // already reduced
}

// inverse modulo prime p (Fermat). Requires p prime and a % p != 0.
static inline ll inv_mod_prime(ll a, ll p) {
  return pow_mod_ll(a, p - 2, p);
}

// inverse modulo any m > 0. Returns true iff gcd(a, m) == 1,
// and sets inv in [0, m-1].  (requires extgcd(a,m,x,y) available)
static inline bool inv_mod_any(ll a, ll m, ll &inv) {
  ll x, y;
  ll g = extgcd(a, m, x, y);
  if (g != 1) return false;
  inv = norm_mod(x, m);
  return true;
}

