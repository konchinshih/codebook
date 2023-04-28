int n, m;
int low[maxn], dfn[maxn], instp;
vector<int> E, g[maxn];
bitset<maxn> isap;
bitset<maxm> vis;
stack<int> stk;
int bccnt;
vector<int> bcc[maxn];
inline void popout(int u) {
	bccnt++;
	bcc[bccnt].emplace_back(u);
	while (!stk.empty()) {
		int v = stk.top();
		if (u == v) break;
		stk.pop();
		bcc[bccnt].emplace_back(v);
	}
}
void dfs(int u, bool rt = 0) {
	stk.push(u);
	low[u] = dfn[u] = ++instp;
	int kid = 0;
	Each(e, g[u]) {
		if (vis[e]) continue;
		vis[e] = true;
		int v = E[e]^u;
		if (!dfn[v]) {
			// tree edge
			kid++; dfs(v);
			low[u] = min(low[u], low[v]);
			if (!rt && low[v] >= dfn[u]) {
				// bcc found: u is ap
				isap[u] = true;
				popout(u);
			}
		} else {
			// back edge
			low[u] = min(low[u], dfn[v]);
		}
	}
	// special case: root
	if (rt) {
		if (kid > 1) isap[u] = true;
		popout(u);
	}
}
void init() {
	cin >> n >> m;
	fill(low, low+maxn, INF);
	REP(i, m) {
		int u, v;
		cin >> u >> v;
		g[u].emplace_back(i);
		g[v].emplace_back(i);
		E.emplace_back(u^v);
	}
}
void solve() {
	FOR(i, 1, n+1, 1) {
		if (!dfn[i]) dfs(i, true);
	}
	vector<int> ans;
	int cnt = 0;
	FOR(i, 1, n+1, 1) {
		if (isap[i]) cnt++, ans.emplace_back(i);
	}
	cout << cnt << endl;
	Each(i, ans) cout << i << ' ';
	cout << endl;
}