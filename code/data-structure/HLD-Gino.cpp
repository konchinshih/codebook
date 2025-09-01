int n;
vector<vector<int>> G;
vector<int> sz;  // size of subtree
vector<int> mxkid;  // kid that has max sz
vector<int> dep, pa;

vector<int> id, top;  // id: node id in ds
// position in data structure (e.g. segment tree) for every vertex
int pos_in_ds;

void dfs(int u, int p, int h) {
    pa[u] = p, dep[u] = h;
    for (auto& v : G[u]) {
        if (v == p) continue;
        dfs(v, u, h + 1);
        sz[u] += sz[v];
        if (mxkid[u] == -1 || sz[v] > sz[mxkid[u]])
            mxkid[u] = v;
    }
}

// t stands for top vertex
void hld(int u, int t) {
    // 0-base or 1-base depends on your data structure
    id[u] = pos_in_ds++;
    top[u] = t;
    if (mxkid[u] == -1) return; // if this is a leaf

    // extend current chain with heavy kid
    hld(mxkid[u], t);
    // light kids: open a new chain
    for (auto& v : G[u]) {
        if (v == pa[u] || v == mxkid[u]) continue;
        hld(v, v);
    }
}

void HLD() {
    sz.assign(n + 1, 1);
    mxkid.assign(n + 1, -1);
    dep.assign(n + 1, 0);
    pa.assign(n + 1, 0);
    pos_in_ds = 0;

    dfs(1, 1, 0);
    hld(1, 1);

    /* [CODE] initialize data structure */
    // remember to use tree id
}

void query(int a, int b) {
    int ta = top[a], tb = top[b];
    while (ta != tb) {
        // W.L.O.G. a is deeper than b
        if (dep[ta] < dep[tb]) swap(a, b), swap(ta, tb);
        /* [CODE] some operations on interval [id[ta], id[a]] */
        // leverage "a" to above chain
        a = pa[ta]; ta = top[a];
    }
    if (dep[a] < dep[b]) swap(a, b);
    /* [CODE] some operations on interval [id[b], id[a]] */
}

