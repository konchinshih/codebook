using Poly = vector<ll>;

// op: 0 = AND, 1 = OR, 2 = XOR; inv = inverse transform
// conv: fwt(a,op), fwt(b,op), a[i] = mul(a[i], b[i]), fwt(a,op,1)
void fwt(Poly& a, int op, bool inv = false) {
  int n = sz(a);
  ll i2 = (mod + 1) / 2;
  for (int s = 1; s < n; s <<= 1)
    for (int i = 0; i < n; i += s << 1)
      for (int j = i; j < i + s; j++) {
        ll &x = a[j], &y = a[j + s];
        if (op == 0) x = inv ? sub(x, y) : add(x, y);
        else if (op == 1) y = inv ? sub(y, x) : add(y, x);
        else {
          tie(x, y) = pair(add(x, y), sub(x, y));
          if (inv) x = mul(x, i2), y = mul(y, i2);
        }
      }
}
