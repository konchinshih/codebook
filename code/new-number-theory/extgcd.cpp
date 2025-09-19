// extgcd: returns g = gcd(a, b) >= 0 and finds x, y s.t. a*x + b*y = g
static inline ll extgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) { x = (a >= 0 ? 1 : -1); y = 0; return a >= 0 ? a : -a; }
  ll x1, y1;
  ll g = extgcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return g;
}

// Solve all solutions of a*x ≡ b (mod m), with m > 0.
// If solvable, returns true and sets:
//   x0  = the smallest non-negative solution
//   mod = m / gcd(a, m)   (general solution: x ≡ x0 (mod mod))
static inline bool solve_linear_congruence_all(ll a, ll b, ll m, ll &x0, ll &mod) {
  if (m < 0) m = -m;
  ll x, y;
  ll g = extgcd(a, m, x, y);
  if (b % g) return false;              // no solution
  ll m_red = m / g;
  __int128 t = (__int128)x * (b / g);   // one solution before normalization
  ll r = (ll)(t % m_red);
  if (r < 0) r += m_red;
  x0 = r;
  mod = m_red;
  return true;
}

