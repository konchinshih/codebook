// (forward, inverse):
// and : x += y * (1, -1)
// or  : y += x * (1, -1)
// xor : x = (x + y) * (1, 1/2)
//       y = (x - y) * (1, 1/2)
// conv: fwt(a), fwt(b), a[i] = mul(a[i], b[i]), fwt(a, 1)
void fwt(vector<ll>& a, bool inv = false) {
  int n = a.size();
  for (int s = 1; s < n; s <<= 1)
    for (int i = 0; i < n; i += s << 1)
      for (int j = i; j < i + s; j++) {
        ll &x = a[j], &y = a[j + s];
        // do something
      }
}
