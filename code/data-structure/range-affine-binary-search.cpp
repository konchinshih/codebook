// Add-on for the lazy SegT (S/op/e, T/mapping/composition/id).
// g: bool(S), monotone along the range, g(e()) must be true.
// e.g. first r with sum[l, r) >= k:
//   max_right(l, [&](S s) { return s.x < k; })  (n if none)
// private:
  template <class G> int mr(int l, int r, int i, S& acc, G g) {
    if (r < ql) return -1;
    if (ql <= l) { S s = op(acc, t[i]);
      if (g(s)) { acc = s; return -1; }
      if (l == r) return l; }
    push(i);
    int res = mr(l, mid, cl, acc, g);
    return res != -1 ? res : mr(mid+1, r, cr, acc, g);
  }
  template <class G> int ml(int l, int r, int i, S& acc, G g) {
    if (qr < l) return -1;
    if (r <= qr) { S s = op(t[i], acc);
      if (g(s)) { acc = s; return -1; }
      if (l == r) return l + 1; }
    push(i);
    int res = ml(mid+1, r, cr, acc, g);
    return res != -1 ? res : ml(l, mid, cl, acc, g);
  }
// public:
  // max r in [l, n] s.t. g(op(a[l..r))) true
  template <class G> int max_right(int l, G g) {
    ql = l; S acc = e(); int r = mr(0, n - 1, 1, acc, g);
    return r == -1 ? n : r;
  }
  // min l in [0, r] s.t. g(op(a[l..r))) true
  template <class G> int min_left(int r, G g) {
    qr = r - 1; S acc = e(); int l = ml(0, n - 1, 1, acc, g);
    return l == -1 ? 0 : l;
  }
