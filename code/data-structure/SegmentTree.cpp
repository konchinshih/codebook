struct node {
    ll sum, add, mod;
    int ln;
    node(): sum(0), add(0), mod(0), ln(0) {}
};
typedef struct node node;
node st[maxn*4];
 
inline void pull(int cl, int cr, int idx) {
    st[idx].sum = st[cl].sum + st[cr].sum;
}
 
inline void push(int idx) {
    if (st[idx].ln == 1) {
        st[idx].mod = 0;
        st[idx].add = 0;
        return;
    }
    int cl = idx<<1, cr = (idx<<1) + 1;
    ll md = st[idx].mod, ad = st[idx].add;
    if (md) {
        st[cl].sum = md * st[cl].ln;
        st[cr].sum = md * st[cr].ln;
        st[cl].mod = st[cr].mod = md;
        st[cl].add = st[cr].add = 0;
        st[idx].mod = 0;
    }
    if (ad) {
        st[cl].sum += ad * st[cl].ln;
        st[cr].sum += ad * st[cr].ln;
        st[cl].add += ad;
        st[cr].add += ad;
        st[idx].add = 0;
    }
}
 
void build(int l, int r, int idx) {
    if (l == r) {
        st[idx].sum = arr[l];
        st[idx].ln = 1;
        return;
    }
    int mid = (l+r) >> 1, cl = (idx<<1), cr = (idx<<1) + 1;
    build(l, mid, cl);
    build(mid+1, r, cr);
    st[idx].ln = len(l, r);
    pull(cl, cr, idx);
}
 
void addval(int ql, int qr, ll val, int l, int r, int idx) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        st[idx].sum += val * st[idx].ln;
        st[idx].add += val;
        return;
    }
    push(idx);
    int mid = (l+r)>>1, cl = (idx<<1), cr = (idx<<1) + 1;
    addval(ql, qr, val, l, mid, cl);
    addval(ql, qr, val, mid+1, r, cr);
    pull(cl, cr, idx);
}
 
void modify(int ql, int qr, ll val, int l, int r, int idx) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        st[idx].sum = val * st[idx].ln;
        st[idx].add = 0;
        st[idx].mod = val;
        return;
    }
    push(idx);
    int mid = (l+r)>>1, cl = (idx<<1), cr = (idx<<1) + 1;
    modify(ql, qr, val, l, mid, cl);
    modify(ql, qr, val, mid+1, r, cr);
    pull(cl, cr, idx);
}
 
ll query(int ql, int qr, int l, int r, int idx) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return st[idx].sum;
    push(idx);
    int mid = (l+r)>>1, cl = (idx<<1), cr = (idx<<1) + 1;
    return (query(ql, qr, l, mid, cl) +
            query(ql, qr, mid+1, r, cr));
}
