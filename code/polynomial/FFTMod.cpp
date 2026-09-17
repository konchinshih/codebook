// Higher precision FFT convolution modulo M.
// Safe when N log2(N) M < 8.6e14.
// Inputs are in [0,M), with M < 2^31-ish.
// needs: FFT
vector<ll> convMod(const vector<ll>& a, const vector<ll>& b, ll M) {
  if (a.empty() || b.empty()) return {};
  vector<ll> res(sz(a) + sz(b) - 1);
  int B = 32 - __builtin_clz(sz(res)), n = 1 << B;
  int cut = int(sqrt(M));
  vector<C> L(n), R(n), outs(n), outl(n);
  for (int i = 0; i < sz(a); i++)
    L[i] = C((int)(a[i] / cut), (int)(a[i] % cut));
  for (int i = 0; i < sz(b); i++)
    R[i] = C((int)(b[i] / cut), (int)(b[i] % cut));
  fft(L), fft(R);
  for (int i = 0; i < n; i++) {
    int j = -i & (n - 1);
    outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
    outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n * C(0, 1));
  }
  fft(outl), fft(outs);
  for (int i = 0; i < sz(res); i++) {
    ll av = ll(real(outl[i]) + .5);
    ll cv = ll(imag(outs[i]) + .5);
    ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
    res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
  }
  return res;
}
