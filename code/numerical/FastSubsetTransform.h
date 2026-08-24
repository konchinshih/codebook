/* Author: Lucian Bicsi (License: GNU Free Documentation License 1.2)
* Description: Transform to a basis with fast convolutions of the form
 *   c[z] = \sum_{z = x \oplus y} a[x] * b[y]
 * where \oplus is one of AND, OR, XOR.
 * The size of $a$ must be a power of 2.
* Time: O(N \log N), Status: stress-tested */
void FST(vi& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
      int &u = a[j], &v = a[j + step]; tie(u, v) =
        inv ? pii(v - u, u) : pii(v, u + v); // AND
        // inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
        // pii(u + v, u - v);                   // XOR /// include-line
    }
  }
  // if (inv) for (int& x : a) x /= sz(a); // XOR only /// include-line
}
vi conv(vi a, vi b) {
  FST(a, 0); FST(b, 0);
  rep(i,0,sz(a)) a[i] *= b[i];
  FST(a, 1); return a;
}