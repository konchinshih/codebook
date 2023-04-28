const int lgmx = 19;
 
int n, q;
int spt[lgmx][maxn];

void build() {
    FOR(k, 1, lgmx, 1) {
        for (int i = 0; i+(1<<k)-1 < n; i++) {
            spt[k][i] = min(spt[k-1][i], spt[k-1][i+(1<<(k-1))]);
        }
    }
}
 
int query(int l, int r) {
    int ln = len(l, r);
    int lg = __lg(ln);
    return min(spt[lg][l], spt[lg][r-(1<<lg)+1]);
}
