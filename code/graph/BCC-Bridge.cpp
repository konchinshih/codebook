int n, m;
vector<int> g[maxn], E;
int low[maxn], dfn[maxn], instp;
int bccnt, bccid[maxn];
stack<int> stk;
bitset<maxm> vis, isbrg;
void init() {
	cin >> n >> m;
	REP(i, m) {
		int u, v;
		cin >> u >> v;
		E.emplace_back(u^v);
		g[u].emplace_back(i);
		g[v].emplace_back(i);
	}
	fill(low, low+maxn, INF);
}
void popout(int u) {
	bccnt++;
	while (!stk.empty()) {
		int v = stk.top();
		if (v == u) break;
		stk.pop();
		bccid[v] = bccnt;
	}
}
void dfs(int u) {
	stk.push(u);
	low[u] = dfn[u] = ++instp;
	
	Each(e, g[u]) {
		if (vis[e]) continue;
		vis[e] = true;
		
		int v = E[e]^u;
		if (dfn[v]) {
			// back edge
			low[u] = min(low[u], dfn[v]);
		} else {
			// tree edge
			dfs(v);
			low[u] = min(low[u], low[v]);
			if (low[v] == dfn[v]) {
				isbrg[e] = true;
				popout(u);
			}
		}
	}
}
void solve() {
	FOR(i, 1, n+1, 1) {
		if (!dfn[i]) dfs(i);
	}
	vector<pii> ans;
	vis.reset();
	FOR(u, 1, n+1, 1) {
		Each(e, g[u]) {
			if (!isbrg[e] || vis[e]) continue;
			vis[e] = true;
			int v = E[e]^u;
			ans.emplace_back(mp(u, v));
		}
	}
	cout << (int)ans.size() << endl;
	Each(e, ans) cout << e.F << ' ' << e.S << endl;
}