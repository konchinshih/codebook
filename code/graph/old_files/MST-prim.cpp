typedef pair<ll, int> edge;

int n, m;
vector<edge> g[maxn];
bitset<maxn> vis;

void init() {
    cin >> n >> m;
    fill(g, g+maxn, vector<edge>());
    vis.reset();
}

int viscnt = 0;
ll ans = 0;
void prim() {
    priority_queue<edge, vector<edge>, greater<edge> > pq;
    pq.push(mp(0, 1));
 
    while (!pq.empty()) {
        int u = pq.top().S;
        ll wu = pq.top().F;
        pq.pop();
 
        if (vis[u]) continue;
 
        ans += wu;
        vis[u] = true;
        viscnt++;
 
        Each(e, g[u]) {
            int v = e.S;
            ll wv = e.F;
            if (vis[v]) continue;
            pq.push(mp(wv, v));
        }
    }
}
