typedef vector<vector<ll> > mtx;
typedef vector<ll> row;
 
int nr(mtx& a) {
    return (int)a.size();
}
int nc(mtx& a) {
    return (int)a[0].size();
}
 
void mulip(mtx& a, mtx& b) { // multiply in-place
    mtx c = mtx(nr(a), row(nc(b), 0));
    REP(i, nr(a)) {
        REP(j, nc(b)) {
            REP(k, nc(a)) {
                c[i][j] += a[i][k] * b[k][j];
                if (c[i][j] >= MOD) c[i][j] %= MOD;
            }
        }
    }
    a = c;
}

mtx pw(mtx& a, ll n) {
    mtx r = a;
    REP(i, nr(a)) {
        REP(j, nr(a)) {
            r[i][j] = (i == j);
        }
    }
 
    while (n > 0) {
        if (n & 1) mulip(r, a);
        mulip(a, a);
        n >>= 1;
    }
    return r;
}
