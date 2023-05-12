// from 1 to n
#define gg return cout << "IMPOSSIBLE\n", void();

int n, m;
vector<int> g[maxn];
bitset<maxn> inodd;
 
void init() {
cin >> n >> m;
inodd.reset();
for (int i = 0; i < m; i++) {
	int u, v; cin >> u >> v;
	inodd[u] = inodd[u] ^ true;
	inodd[v] = inodd[v] ^ true;
	g[u].emplace_back(v);
	g[v].emplace_back(u);
} }
stack<int> stk;
void dfs(int u) {
    while (!g[u].empty()) {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v);
    }
stk.push(u);}
