// Author: ckiseki (Modified by Gino)
// Usage: RH<Sigma, Mod> Hs(s);
// If no modifications needed, replace BIT with prefix sum
template <ll P = 127, ll Q = 1051762951>
class RH {
  int n; vector<ll> p, inv, d, bit;
  ll add(ll a, ll b) { return a+b >= Q ? a+b-Q : a+b; }
  ll sub(ll a, ll b) { return a-b < 0  ? a-b+Q : a-b; }
  ll mul(ll a, ll b) { return (__int128)a * b % Q; }
  ll pw(ll a, ll x) {
    ll r = 1; for (; x; a = mul(a, a), x >>= 1)
      if (x & 1) r = mul(r, a);
    return r;
  }
  void bit_add(int i, ll x)
    { for (; i <= n; i += i&-i) bit[i] = add(bit[i], x); }
  ll bit_qry(int i)
    { ll s = 0; for (; i; i -= i&-i) s = add(s, bit[i]); return s; }
public:
  RH(const auto &s) : n(s.size()),
      p(n+1, 1), inv(n+1, 1), d(n+1), bit(n+1) {
    ll iv = pw(P, Q - 2);
    for (int i = 1; i <= n; i++) {
      p[i] = mul(p[i - 1], P); inv[i] = mul(inv[i - 1], iv);
      d[i] = mul(s[i - 1], p[i]); bit_add(i, d[i]);
  } }
  void update(int i, char c)
    { ll x=mul(c, p[i]); bit_add(i, sub(x, d[i])); d[i]=x; }
  ll query(int l, int r)
    { return mul(sub(bit_qry(r), bit_qry(l - 1)), inv[l]); }
};