// Author: ckiseki
// Usage: RH<Sigma, Mod> Hs(s);
template <ll C = 127, ll Q = 1051762951>
class RH {
  vector<ll> h, p;
  static ll add(ll a, ll b) { return a + b >= Q ? a + b - Q : a + b; }
  static ll sub(ll a, ll b) { return a - b < 0  ? a - b + Q : a - b; }
  static ll mul(ll a, ll b) { return (__int128)a * b % Q; }
public:
  RH(const auto &s) : h(s.size()+1), p(s.size()+1) {
    for (size_t i = 0; i < s.size(); ++i)
      h[i + 1] = add(mul(h[i], C), s[i]);
    generate(all(p), [x = 1LL, y = 1LL, this]() mutable {
      return y = x, x = mul(x, C), y; });
  }
  ll query(int l, int r) const { // 0-base [l, r)
    return sub(h[r], mul(h[l], p[r - l]));
  }
};