// Author: Ian, https://judge.yosupo.jp/submission/400861
const int maxn=2e5+5;
const ll MX = 1e18+5;
const ll MN = -MX;
#define m ((l+r)>>1)
struct node {
  ll sum, inc;
  ll mn, smn; int mnc;
  ll mx, smx; int mxc;
  node(ll x=0): sum(x), inc(0),
    mn(x), smn(MX), mnc(1),
    mx(x), smx(MN), mxc(1) {}
  void pull(int i);
  void push(int i, int l, int r);
} a[(maxn+1)<<2];
void node::pull(int i) {
  sum = a[i<<1].sum+a[i<<1|1].sum;
  if (a[i<<1].mn == a[i<<1|1].mn) {
    mn = a[i<<1].mn;
    smn = min(a[i<<1].smn, a[i<<1|1].smn);
    mnc = a[i<<1].mnc+a[i<<1|1].mnc;
  } else {
    if (a[i<<1].mn < a[i<<1|1].mn) {
      mn = a[i<<1].mn;
      smn = min(a[i<<1].smn, a[i<<1|1].mn);
      mnc = a[i<<1].mnc;
    } else {
      mn = a[i<<1|1].mn;
      smn = min(a[i<<1|1].smn, a[i<<1].mn);
      mnc = a[i<<1|1].mnc;
    } }
  if (a[i<<1].mx == a[i<<1|1].mx) {
    mx = a[i<<1].mx;
    smx = max(a[i<<1].smx, a[i<<1|1].smx);
    mxc = a[i<<1].mxc+a[i<<1|1].mxc;
  } else {
    if (a[i<<1].mx > a[i<<1|1].mx) {
      mx = a[i<<1].mx;
      smx = max(a[i<<1].smx, a[i<<1|1].mx);
      mxc = a[i<<1].mxc;
    } else {
      mx = a[i<<1|1].mx;
      smx = max(a[i<<1|1].smx, a[i<<1].mx);
      mxc = a[i<<1|1].mxc;
    } }
}
void updmn(int i, int len, ll v) {
  a[i].sum += (v-a[i].mn)*a[i].mnc; a[i].mn = v;
  if (len==1||v>=a[i].mx)
    a[i].mx = v, a[i].smx = MN;
  else if (v>a[i].smx)
    a[i].smx = v;
}
void updmx(int i, int len, ll v) {
  a[i].sum -= (a[i].mx-v)*a[i].mxc; a[i].mx = v;
  if (len==1||v<=a[i].mn)
    a[i].mn = v, a[i].smn = MX;
  else if (v<a[i].smn)
    a[i].smn = v;
}
void node::push(int i, int l, int r) {
  if (r-l==1) return;
  pair<int, int> ch[] = {{i<<1, m-l}, {i<<1|1, r-m}};
  if (inc!=0) for (auto [j, len]: ch) {
    a[j].sum += inc*len, a[j].inc += inc;
    a[j].mx += inc, a[j].smx += inc;
    a[j].mn += inc, a[j].smn += inc;
  } inc = 0;
  for (auto [j, len]: ch) {
    if (a[j].mn < mn) updmn(j, len, mn);
    if (a[j].mx > mx) updmx(j, len, mx); }
}
void build(vector<ll>& v, int i=1,int l=0,int r=maxn) {
  if ((int)v.size()<=l) return;
  if (r-l==1) { a[i] = node(v[l]); return; }
  build(v, i<<1, l, m);
  build(v, i<<1|1, m, r);
  a[i].pull(i);
}
void chmin(int ql,int qr,ll v,int i=1,int l=0,int r=maxn){
  if (qr<=l||r<=ql||a[i].mx<=v) return;
  if (ql<=l&&r<=qr&&a[i].smx<v) {updmx(i, r-l, v);return;}
  a[i].push(i, l, r);
  chmin(ql, qr, v, i<<1, l, m);
  chmin(ql, qr, v, i<<1|1, m, r);
  a[i].pull(i);
}
void chmax(int ql,int qr,ll v,int i=1,int l=0,int r=maxn){
  if (qr<=l||r<=ql||a[i].mn>=v) return;
  if (ql<=l&&r<=qr&&a[i].smn>v) {updmn(i, r-l, v);return;}
  a[i].push(i, l, r);
  chmax(ql, qr, v, i<<1, l, m);
  chmax(ql, qr, v, i<<1|1, m, r);
  a[i].pull(i);
}
void inc(int ql,int qr,ll v,int i=1,int l=0,int r=maxn){
  if (qr<=l || r<=ql) return;
  if (ql<=l && r<=qr) {
    a[i].sum += v*(r-l);
    a[i].mx += v, a[i].smx += v;
    a[i].mn += v, a[i].smn += v;
    a[i].inc += v;
    return;
  }
  a[i].push(i, l, r);
  inc(ql, qr, v, i<<1, l, m);
  inc(ql, qr, v, i<<1|1, m, r);
  a[i].pull(i);
}
ll qsum(int ql, int qr, int i=1, int l=0, int r=maxn) {
  if (qr<=l || r<=ql) return 0;
  if (ql<=l && r<=qr) return a[i].sum;
  a[i].push(i, l, r);
  return qsum(ql, qr, i<<1, l, m)+qsum(ql,qr, i<<1|1, m, r);
}
#undef m
