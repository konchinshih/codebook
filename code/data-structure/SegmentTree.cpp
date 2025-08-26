// Author: Gino
struct node {
    ll sum, add, mod; int ln;
    node(): sum(0), add(0), mod(0), ln(0) {}
};

struct segT {
    int n;
    vector<ll> ar;
    vector<node> st;

    void init(int _n) {
        n = _n;
        reset(ar, n, 0LL);
        reset(st, n*4);
    }
    void pull(int cl, int cr, int i) {
        st[i].sum = st[cl].sum + st[cr].sum;
    }
    void push(int cl, int cr, int i) {
        ll md = st[i].mod, ad = st[i].add;
        if (md) {
            st[cl].sum = md * st[cl].ln, st[cr].sum = md * st[cr].ln;
            st[cl].mod = md, st[cr].mod = md;
            st[i].mod = 0;
        }
        if (ad) {
            st[cl].sum += ad * st[cl].ln, st[cr].sum += ad * st[cr].ln;
            st[cl].add += ad, st[cr].add += ad;
            st[i].add = 0;
        }
    }
    void build(int l, int r, int i) {
        if (l == r) {
            st[i].sum = ar[l];
            st[i].ln = 1;
            return;
        }
        int mid = (l+r)>>1, cl = i<<1, cr = i<<1|1;
        build(l, mid, cl);
        build(mid + 1, r, cr);
        pull(cl, cr, i);
    }
    void addval(int ql, int qr, ll val, int l, int r, int i) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            st[i].sum += val * st[i].ln;
            st[i].add += val;
            return;
        }
        int mid = (l+r)>>1, cl = i<<1, cr = i<<1|1;
        push(cl, cr, i);
        addval(ql, qr, val, l, mid, cl);
        addval(ql, qr, val, mid + 1, r, cr);
        pull(cl, cr, i);
    }
    void modify(int ql, int qr, ll val, int l, int r, int i) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            st[i].sum = val * st[i].ln;
            st[i].add = 0;
            st[i].mod = val;
            return;
        }
        int mid = (l+r)>>1, cl = i<<1, cr = i<<1|1;
        push(cl, cr, i);
        modify(ql, qr, val, l, mid, cl);
        modify(ql, qr, val, mid+1, r, cr);
        pull(cl, cr, i);
    }
    ll query(int ql, int qr, int l, int r, int i) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[i].sum;
        int mid = (l+r)>>1, cl = i<<1, cr = i<<1|1;
        push(cl, cr, i);
        return (query(ql, qr, l, mid, cl) +
                query(ql, qr, mid+1, r, cr));
    }
};
