// from node 1 to node n
#define gg return cout << "IMPOSSIBLE\n", 0

int n, m;
vector<int> g[maxn];
stack<int> stk;
int in[maxn], out[maxn];
 
void init() {
cin >> n >> m;
for (int i = 0; i < m; i++) {
	int u, v; cin >> u >> v;
	g[u].emplace_back(v);
	out[u]++, in[v]++;
}
for (int i = 1; i <= n; i++) {
	if (i == 1 && out[i]-in[i] != 1) gg;
	if (i == n && in[i]-out[i] != 1) gg;
	if (i != 1 && i != n && in[i] != out[i]) gg;
} }
void dfs(int u) {
    while (!g[u].empty()) {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v);
    }
    stk.push(u);
}
void solve() {
	dfs(1)
    for (int i = 1; i <= n; i++)
        if ((int)g[i].size()) gg;
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        cout << u << ' ';
} }
