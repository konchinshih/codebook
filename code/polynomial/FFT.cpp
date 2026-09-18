// Rounding is safe if
// (sum a[i]^2 + sum b[i]^2) log2(N) < 9e14.
// In practice, 1e16 or higher often works.
using C = complex<double>;
using vd = vector<double>;

void fft(vector<C>& a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n), rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    for (int i = k; i < 2 * k; i++)
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  vi rev(n);
  for (int i = 0; i < n; i++)
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        auto* x = (double*)&rt[j + k];
        auto* y = (double*)&a[i + j + k];
        C z(x[0] * y[0] - x[1] * y[1],
            x[0] * y[1] + x[1] * y[0]);
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}

vd convFFT(const vd& a, const vd& b) {
  if (a.empty() || b.empty()) return {};
  vd res(sz(a) + sz(b) - 1);
  int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
  vector<C> in(n), out(n);
  copy(all(a), begin(in));
  for (int i = 0; i < sz(b); i++) in[i].imag(b[i]);
  fft(in);
  for (C& x : in) x *= x;
  for (int i = 0; i < n; i++)
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  for (int i = 0; i < sz(res); i++)
    res[i] = imag(out[i]) / (4 * n);
  return res;
}
