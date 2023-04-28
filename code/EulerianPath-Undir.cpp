int n, m;
vector<int> g[maxn];
bitset<maxn> inodd;
 
void init() {
    cin >> n >> m;
    inodd.reset();
}
 
stack<int> stk;
void dfs(int u) {
    while (!g[u].empty()) {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v);
    }
    stk.push(u);
}
 
 
int main() {
    WiwiHorz
    init();
 
    REP(i, m) {
        int u, v;
        cin >> u >> v;
        inodd[u] = inodd[u] ^ true;
        inodd[v] = inodd[v] ^ true;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
 
    FOR(i, 1, n+1, 1) {
        if (inodd[i]) return cout << "IMPOSSIBLE\n", 0;
    }
 
    dfs(1);
 
    FOR(i, 1, n+1, 1) {
        if ((int)g[i].size()) return cout << "IMPOSSIBLE\n", 0;
    }
 
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        cout << u << ' ';
    }
    cout << endl;
 
    return 0;
}
