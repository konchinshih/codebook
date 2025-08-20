int n;
vector<vector<int>> G;

pii centroid;
vector<int> sz, mxcc;  // mxcc[u]: max component size after removing u

void dfs(int u, int p) {
    sz[u] = 1;
    for (auto& v : G[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        mxcc[u] = max(mxcc[u], sz[v]);
    }
    mxcc[u] = max(mxcc[u], n - sz[u]);
}

void find_centroid() {
    centroid = pii{-1, -1};
    reset(sz, n + 1, 0);
    reset(mxcc, n + 1, 0);
    dfs(1, 1);
    for (int u = 1; u <= n; u++) {
        if (mxcc[u] <= n / 2) {
            if (centroid.first != -1) centroid.second = u;
            else centroid.first = u;
        }
    }
}
