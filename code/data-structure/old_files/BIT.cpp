// Author: Gino
inline int lb(int& x) {
    return x & (-x);
}

struct BIT {
    int n;
    vector<ll> bit;
    inline int lb(int x) { return x & (-x); }
    void init(int _n) {
        n = _n;
        bit.assign(n + 1, 0LL);
    }
    void upd(int p, ll x) {
        for (; p <= sz; p += lb(p)) {
            bit[p] += x;
        }
    }
    ll qry(int p) {
        ll ret = 0;
        for (; p > 0; p -= lb(p)) {
            ret += bit[p];
        }
        return ret;
    }
    ll query(int l, int r) {
        return qry(r) - (l > 1 ? qry(l - 1) : 0);
    }
};

struct RANGE_ADD_BIT {
    int n;
    BIT bit1, bit2;
    void init(int _n) {
        n = _n;
        bit1.init(n);
        bit2.init(n);
    }
    void modify(int l, int r, ll val) {
        bit1.modify(l, val);
        bit1.modify(r+1, -val);
        bit2.modify(l, val*l);
        bit2.modify(r+1, -val*(r+1));
    }
    ll qry(int x) {
        return (x+1) * bit1.qry(x) - bit2.qry(x);
    }
    ll query(int l, int r) {
        return qry(r) - (l>1 ? qry(l-1) : 0);
    }
};
