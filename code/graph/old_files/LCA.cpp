int n, q;
vector<int> g[maxn];
int h[maxn], anc[21][maxn];
 
void init() {
    cin >> n >> q;
    fill(g, g+maxn, vector<int>());
    memset(h, 0, sizeof(h));
    memset(anc, 0, sizeof(anc));
}
 
void buildH(int u, int p, int cur) {
    anc[0][u] = p;
    h[u] = cur;
 
    Each(v, g[u]) {
        if (v == p) continue;
        buildH(v, u, cur+1);
    }
}
 
void buildP() {
    FOR(i, 1, 21, 1) {
        FOR(u, 1, n+1, 1) {
            anc[i][u] = anc[i-1][anc[i-1][u]];
        }
    }
}
 
int findLCA(int u, int v) {
    if (h[u] > h[v]) swap(u, v);
    int dif = h[v] - h[u];
 
    for (int i = 20; i >= 0; i--) {
        if (dif & (1<<i)) v = anc[i][v];
    }
 	
 	// important !!!!
    if (u == v) return u;
 
    for (int i = 20; i >= 0; i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }
 
    return anc[0][u];
}
