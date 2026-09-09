// Author: Ian
// insert(L): add line L(ax+b) in [0, maxn)
// insertseg(L, ql, qr): add segment L in [ql, qr)
// query(x): find maximum L at x
using T=long long;
const int maxn = 1e5+5;
const T MN = -1e15;
struct line {
	T a, b;
  line(T a=0, T b=MN): a(a), b(b) {}
	T operator()(T x) {return a * x + b;}
} arr[(maxn+1)<<3];
bool operator<(line a, line b) {
  return a.a < b.a || (a.a == b.a && a.b < b.b); }
#define m ((l+r)>>1)
void insert(line x, int i=1, int l=0, int r=maxn) {
	if (r-l == 1) {
		if (x(l) > arr[i](l)) arr[i] = x;
		return; }
	line a = max(arr[i], x), b = min(arr[i], x);
	if (a(m) > b(m))
		arr[i] = a, insert(b, i<<1, l, m);
	else
		arr[i] = b, insert(a, i<<1|1, m, r);
}
void insertseg(line x, int ql, int qr,
               int i=1, int l=0, int r=maxn) {
	if (qr<=l || r<=ql || ql>=qr) return;
	if (ql<=l && r<=qr) { insert(x, i, l, r); return; }
	insertseg(x, ql, qr, i<<1, l, m);
	insertseg(x, ql, qr, i<<1|1, m, r);
}
T query(T x, int i=1, int l=0, int r=maxn) {
	if (x<l || r<=x) return MN;
	if (r-l == 1) return arr[i](x);
	return max({arr[i](x),
    query(x, i<<1, l, m), query(x, i<<1|1, m, r)});
}
#undef m
