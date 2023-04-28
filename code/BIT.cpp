inline int lb(int& x) {
    return x & (-x);
}

struct BIT {
    int sz = 0;
    vector<ll> bit;
    void build(int _sz) {
        sz = _sz;
        bit.resize(sz+1, 0);
        FOR(i, 1, n+1, 1) {
	        bit[i] = arr[i];
	        int lim = i - lb(i);
	        for (int j = i-1; j > lim; j -= lb(j)) {
	            bit[i] += bit[j];
	        }
	    }
    }
    void modify(int x, ll val) {
        for (; x <= sz; x += lb(x)) {
            bit[x] += val;
        }
    }
    ll query(int x) {
        ll ret = 0;
        for (; x > 0; x -= lb(x)) {
            ret += bit[x];
        }
        return ret;
    }
};

struct SUMBIT {
    int sz = 0;
    BIT bit1, bit2;
    void build(int _sz) {
        sz = _sz;
        bit1.build(sz);
        bit2.build(sz);
    }
    void modify(int l, int r, ll val) {
        bit1.modify(l, val);
        bit1.modify(r+1, -val);
        bit2.modify(l, val*l);
        bit2.modify(r+1, -val*(r+1));
    }
    ll query(int x) {
        return (x+1) * bit1.query(x) - bit2.query(x);
    }
    ll query(int l, int r) {
        return query(r) - (l>1 ? query(l-1) : 0);
    }
};
