// mod 998244353; 1e9+7 is NOT ntt-friendly
const int N = 1 << 20, G = 3;
using Poly = vector<ll>;

struct NTT {
  ll w[N];
  NTT() {
    ll dw = Pow(G, (mod - 1) / N);
    w[0] = 1;
    for (int i = 1; i < N; i++)
      w[i] = mul(w[i - 1], dw);
  }
  void operator()(Poly& a, bool inv = false) {
    int n = sz(a);
    for (int j = 1, x = 0; j < n - 1; j++) {
      for (int k = n >> 1; (x ^= k) < k; k >>= 1);
      if (j < x) swap(a[x], a[j]);
    }
    for (int L = 2; L <= n; L <<= 1) {
      int dx = N / L, dl = L >> 1;
      for (int i = 0; i < n; i += L)
        for (int j = i, x = 0; j < i + dl; j++, x += dx) {
          ll tmp = mul(a[j + dl], w[x]);
          a[j + dl] = sub(a[j], tmp);
          a[j] = add(a[j], tmp);
        }
    }
    if (inv) {
      reverse(1 + all(a));
      ll invn = Pow(n, mod - 2);
      for (ll& x : a) x = mul(x, invn);
    }
  }
} ntt;

// polyMul: a*b truncated to bound terms, O(n log n).
// Result length must be <= N.
Poly polyMul(Poly a, Poly b, int bound = N) {
  int m = sz(a) + sz(b) - 1, n = 1;
  while (n < m) n <<= 1;
  a.resize(n), b.resize(n);
  ntt(a), ntt(b);
  for (int i = 0; i < n; i++) a[i] = mul(a[i], b[i]);
  ntt(a, true);
  a.resize(min(m, bound));
  return a;
}
