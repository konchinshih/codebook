typedef pair<ll, int> edge;
 
int n, m;
vector<edge> g[maxn];
ll dis[maxn];
 
void init() {
    cin >> n >> m;
    fill(g, g+maxn, vector<edge>());
    memset(dis, 0, sizeof(dis));
}
 
void dijk(int sr) {
    fill(dis, dis+maxn, LLINF);
    dis[sr] = 0;
    priority_queue<edge, vector<edge>, greater<edge> > pq;
    pq.push(mp(0, sr));
 
    while (!pq.empty()) {
        int u = pq.top().S;
        ll ds = pq.top().F;
        pq.pop();
 
        if (ds > dis[u]) continue;
 
        Each(e, g[u]) {
            int v = e.S;
            ll w = e.F;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push(mp(dis[v], v));
            }
        }
    }
}
