const int lgmx = 19;
int n, q;
int spt[lgmx][maxn];
void build() {
    for (int k = 1; k < lgmx; k++)
        for (int i = 0; i+(1<<k)-1 < n; i++)
            spt[k][i] = min(spt[k-1][i], spt[k-1][i + (1<<(k-1))]);
}
int query(int l, int r) {
    int lg = __lg(r - l + 1);
    return min(spt[lg][l], spt[lg][r-(1<<lg)+1]);
}
