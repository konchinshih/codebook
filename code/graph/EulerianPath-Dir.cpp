// from node 1 to node n
#define gg return cout << "IMPOSSIBLE\n", 0
 
int n, m;
vector<int> g[maxn];
stack<int> stk;
int in[maxn], out[maxn];
 
void init() {
    cin >> n >> m;
}
 
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
        g[u].emplace_back(v);
        out[u]++, in[v]++;
    }
 
    FOR(i, 1, n+1, 1) {
        if (i == 1 && out[i]-in[i] != 1) gg;
        if (i == n && in[i]-out[i] != 1) gg;
        if (i != 1 && i != n && in[i] != out[i]) gg;
    }
 
    dfs(1);
 
    FOR(i, 1, n+1, 1) {
        if ((int)g[i].size()) gg;
    }
 
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        cout << u << ' ';
    }
 
    return 0;
}
