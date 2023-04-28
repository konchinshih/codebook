typedef pair<ll, int> edge;

int n, m;
vector<edge> g[maxn];
ll dis[maxn];
bitset<maxn> inq;

void init() {
    cin >> n >> m;
    fill(g, g+maxn, vector<edge>());
    memset(dis, 0, sizeof(dis));
    inq.reset();
}

void spfa(int sr) {
    fill(dis, dis+maxn, LLINF);
    inq.reset();
 
    queue<int> q;
    dis[sr] = 0;
    q.push(sr);
    inq[sr] = true;
 
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
 
        Each(e, g[u]) {
            int v = e.S;
            ll w = e.F;
 
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}
