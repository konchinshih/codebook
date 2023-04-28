constexpr int maxn = 5e4 + 5;
struct line {
	ld a, b;
	ld operator()(ld x) {return a * x + b;}
} arr[(maxn + 1) << 2];
bool operator<(line a, line b) {return a.a < b.a;}
#define m ((l+r)>>1)
void insert(line x, int i = 1, int l = 0, int r = maxn) {
	if (r - l == 1) {
		if (x(l) > arr[i](l))
			arr[i] = x;
		return;
	}
	line a = max(arr[i], x), b = min(arr[i], x);
	if (a(m) > b(m))
		arr[i] = a, insert(b, i << 1, l, m);
	else
		arr[i] = b, insert(a, i << 1 | 1, m, r);
}
ld query(int x, int i = 1, int l = 0, int r = maxn) {
	if (x < l || r <= x) return -numeric_limits<ld>::max();
	if (r - l == 1) return arr[i](x);
	return max({arr[i](x), query(x, i << 1, l, m), query(x, i << 1 | 1, m, r)});
}
#undef m