#define mid ((l + r) >> 1)
#define cl (i<<1)
#define cr (i<<1|1)
class SegT {
  int n; vector<S> a, t; vector<T> lz;
  inline void pull(int i) { t[i] = op(t[cl], t[cr]); }
  inline void apply(int i, T tag) {
    t[i] = mapping(tag, t[i]);
    lz[i] = composition(tag, lz[i]);
  }
  inline void push(int i) {
    apply(cl, lz[i]); apply(cr, lz[i]);
    lz[i] = id();
  }
  void build(int l, int r, int i) {
    if (l == r) { t[i] = a[l]; return; }//!! a[l], not a[i]
    build(l, mid, cl); build(mid+1, r, cr); pull(i);
  }
  int ql, qr; T tag;
  void upd(int l, int r, int i) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) { apply(i, tag); return; }
    push(i); upd(l, mid, cl); upd(mid+1, r, cr); pull(i);
  }
  S qry(int l, int r, int i) {
    if (qr < l || r < ql) return e();
    if (ql <= l && r <= qr) return t[i];
    push(i); return op(qry(l, mid, cl), qry(mid+1, r, cr));
  }
public:
  SegT(vector<S>& a):
    n(a.size()), a(a), t(n<<2), lz(n<<2, id()) {
    build(0, n - 1, 1);
  }
  void update(int l, int r, T tag) {  // [l, r)
    ql = l, qr = r - 1, this->tag = tag;
    upd(0, n - 1, 1);
  }
  S query(int l, int r) {  // [l, r)
    ql = l, qr = r - 1;
    return qry(0, n - 1, 1);
} };
#undef mid
#undef cl
#undef cr
