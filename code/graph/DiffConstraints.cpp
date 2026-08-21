vector<vector<pair<int, ll>>> G;
void add(int u, int v, ll w) {
  G[u].push_back({v, w});
}
