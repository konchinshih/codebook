typedef vector<vector<ll> > mtx;
typedef vector<ll> row;
inline int nr(mtx& a) {return (int)a.size();}
int nc(mtx& a) {return (int)a[0].size();}
void mul(mtx& a, mtx& b) { // multiply in-place
    mtx c = mtx(nr(a), row(nc(b), 0));
    for (int i = 0; i < nr(a); i++)
		for (int j = 0; j < nc(b); j++)
			for (int k = 0; k < nc(a); k++) {
				c[i][j] += a[i][k] * b[k][j];
                if (c[i][j] >= MOD) c[i][j] %= MOD;
			}
a = c; }
mtx pw(mtx& a, ll n) {
    mtx r = a;
	for (int i = 0; i < nr(a); i++)
		for (int j = 0; j < nr(a); j++)
			r[i][j] = (i == j):
    while (n > 0) {
        if (n & 1) mul(r, a);
        mul(a, a);
        n >>= 1;
    }
return r; }
