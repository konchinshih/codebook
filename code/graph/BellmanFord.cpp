typedef pair<pii, ll> edge;

int n, m, cycle;
bool ans;
vector<edge> E;
ll dis[maxn]; int p[maxn];

void init() {
    cin >> n >> m;
    cycle = -1;
    ans = false;
    REP(i, m) {
        int u, v; ll w;
        cin >> u >> v >> w;
        E.eb(mp(mp(u, v), w));
    }
}
void bellmanford() {
    fill(dis, dis+maxn, LLINF);
    dis[1] = 0;
    FOR(upd, 1, n+1, 1) {
        Each(e, E) {
            int u = e.F.F, v = e.F.S; ll w = e.S;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                p[v] = u;
                if (upd == n) cycle = v;
            }
        }
    }
}
void solve() {
    stack<int> output;
    bellmanford();
    if (cycle == -1) return cout << "NO\n", void();
    cout << "YES\n";
    for (int i = 0; i < n; i++) cycle = p[cycle];  // VIP!!
    for (int cur = cycle; ; cur = p[cur]) {
        output.push(cur);
        if (cur == cycle && (int)output.size() > 1) break;
    }
    while (!output.empty()) {
        cout << output.top() << ' ';
        output.pop();
    }
    cout << endl;
}