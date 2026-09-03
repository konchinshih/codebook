void init() {
    cin >> n >> m >> q;
    Each(i, dis) Each(j, i) j = LLINF;
}
while (m--) {
    int u, v; ll w;
    cin >> u >> v >> w;
    dis[u][v] = min(dis[u][v], w);
    dis[v][u] = min(dis[v][u], w);
}
void floydwarshall() {
	FOR(k, 1, n+1, 1) {
	    FOR(i, 1, n+1, 1) {
		FOR(j, 1, n+1, 1) {
		    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
} } } }
