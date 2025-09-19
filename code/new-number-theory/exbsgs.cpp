// exbsgs — discrete log without coprimality (extended BSGS)
// Solve smallest x ≥ 0 s.t. a^x ≡ b (mod m) for m>1 (gcd(a,m) may ≠1).
// Returns true and sets x if a solution exists; otherwise false.
// Requires: norm_mod(a,m), pow_mod_ll(a,e,m), inv_mod_any(a,m,inv)

using ll = long long;

static inline bool exbsgs(ll a, ll b, ll m, ll &x){
  if (m == 1){ x = 0; return (b % 1) == 0; }

  a = norm_mod(a, m);
  b = norm_mod(b, m);

  // a ≡ 0 (mod m): a^0 ≡ 1, a^k ≡ 0 for k≥1
  if (a == 0){
    if (b == 1 % m){ x = 0; return true; }
    if (b == 0){ x = 1; return true; }
    return false;
  }
  if (b == 1 % m){ x = 0; return true; }

  ll cnt = 0;
  ll mult = 1 % m;
  while (true){
    ll g = std::gcd(a, m);
    if (g == 1) break;
    if (b % g != 0) return false;
    m /= g;
    b /= g;
    mult = (ll)((__int128)mult * (a / g) % m); // mult *= a/g
    ++cnt;
    if (mult == b){ x = cnt; return true; }
  }

  // Now gcd(a,m)==1: solve a^y ≡ b * inv(mult) (mod m) via BSGS, then x = y + cnt.
  ll inv_mult;
  if (!inv_mod_any(mult, m, inv_mult)) return false;
  ll target = (ll)((__int128)b * inv_mult % m);

  ll n = (ll)std::sqrt((long double)m) + 1;

  std::unordered_map<ll, int> baby;
  baby.reserve((size_t)(n * 1.3)); baby.max_load_factor(0.7f);

  ll aj = 1 % m;
  for (int j = 0; j < n; ++j){
    if (!baby.count(aj)) baby.emplace(aj, j);
    aj = (ll)((__int128)aj * a % m);
  }

  ll an = pow_mod_ll(a, n, m);
  ll inv_an;
  if (!inv_mod_any(an, m, inv_an)) return false;

  ll cur = target;
  for (ll i = 0; i <= n; ++i){
    auto it = baby.find(cur);
    if (it != baby.end()){
      x = cnt + i * n + it->second;
      return true;
    }
    cur = (ll)((__int128)cur * inv_an % m);
  }
  return false;
}

