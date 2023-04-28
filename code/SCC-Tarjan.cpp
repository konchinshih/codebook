// 2-SAT
vector<int> E, g[maxn];  // 1~n, n+1~2n
int low[maxn], in[maxn], instp;
int sccnt, sccid[maxn];
 
stack<int> stk;
bitset<maxn> ins, vis;
 
int n, m;
 
void init() {
    cin >> m >> n;
    E.clear();
    fill(g, g+maxn, vector<int>());
    fill(low, low+maxn, INF);
    memset(in, 0, sizeof(in));
    instp = 1;
    sccnt = 0;
    memset(sccid, 0, sizeof(sccid));
    ins.reset();
    vis.reset();
}
 
inline int no(int u) {
    return (u > n ? u-n : u+n);
}
 
int ecnt = 0;
inline void clause(int u, int v) {
    E.eb(no(u)^v);
    g[no(u)].eb(ecnt++);
    E.eb(no(v)^u);
    g[no(v)].eb(ecnt++);
}
 
void dfs(int u) {
    in[u] = instp++;
    low[u] = in[u];
    stk.push(u);
    ins[u] = true;
 
    Each(e, g[u]) {
        if (vis[e]) continue;
        vis[e] = true;
 
        int v = E[e]^u;
        if (ins[v]) low[u] = min(low[u], in[v]);
        else if (!in[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
 
    if (low[u] == in[u]) {
        sccnt++;
        while (!stk.empty()) {
            int v = stk.top();
            stk.pop();
            ins[v] = false;
            sccid[v] = sccnt;
            if (u == v) break;
        }
    }
}
 
 
int main() {
    WiwiHorz
    init();
 
    REP(i, m) {
        char su, sv;
        int u, v;
        cin >> su >> u >> sv >> v;
        if (su == '-') u = no(u);
        if (sv == '-') v = no(v);
        clause(u, v);
    }
 
    FOR(i, 1, 2*n+1, 1) {
        if (!in[i]) dfs(i);
    }
 
    FOR(u, 1, n+1, 1) {
        int du = no(u);
        if (sccid[u] == sccid[du]) {
            return cout << "IMPOSSIBLE\n", 0;
        }
    }
 
    FOR(u, 1, n+1, 1) {
        int du = no(u);
        cout << (sccid[u] < sccid[du] ? '+' : '-') << ' ';
    }
    cout << endl;
 
    return 0;
}
