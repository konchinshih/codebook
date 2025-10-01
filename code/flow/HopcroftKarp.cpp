// Author: Gino
// Function: Max Bipartite Matching in O(V sqrt(E))
// Usage:
// >>> init(nx, ny, m) -> add(x, y (+nx))
// >>> hk.max_matching() := the matching plan stores in mx, my
// >>> hk.min_vertex_cover() := the vertex cover plan stores in vcover
// (!) vertices are 0-based: X = [0, nx), Y = [nx, nx+ny)
struct HopcroftKarp {
  int n, nx, ny;
  vector<vector<int> > G;
  vector<int> mx, my;
  void init(int _nx, int _ny) {
    nx = _nx, ny = _ny;
    n = nx + ny;
    G.clear(); G.resize(n);
  }
  void add(int x, int y) {
    G[x].emplace_back(y);
    G[y].emplace_back(x);
  }
  int max_matching() {
    vector<int> dis, vis;
    mx.clear(); mx.resize(n, -1);
    my.clear(); my.resize(n, -1);

    function<bool(int)> dfs = [&](int x) {
      vis[x] = true;
      for (auto& y : G[x]) {
        int px = my[y];
        if (px == -1 ||
            (dis[px] == dis[x]+1 &&
             !vis[px] && dfs(px))) {
          mx[x] = y;
          my[y] = x;
          return true;
      } }
      return false;
    };
    
    while (true) {
      queue<int> q;
      dis.clear(); dis.resize(n, -1);
      for (int x = 0; x < nx; x++){
        if (mx[x] == -1) {
          dis[x] = 0;
          q.push(x);
      } }
      while (!q.empty()) {
        int x = q.front(); q.pop();
        for (auto& y : G[x]) {
          if (my[y] != -1 && dis[my[y]] == -1) {
            dis[my[y]] = dis[x] + 1;
            q.push(my[y]);
      } } }
      bool brk = true;
      vis.clear(); vis.resize(n, 0);
      for (int x = 0; x < nx; x++)
        if (mx[x] == -1 && dfs(x))
          brk = false;
      if (brk) break;
    }
    int ans = 0;
    for (int x = 0; x < nx; x++) if (mx[x] != -1) ans++;
    return ans;
  }
  vector<int> vcover;
  int min_vertex_cover() {
    int ans = max_matching();
    vcover.clear();

    vector<int> vis(n, 0);
    function<void(int)> dfs = [&](int x) {
      vis[x] = true;
      for (auto& y : G[x]) {
        if (y == mx[x] || my[y] == -1 || vis[y]) continue;
        vis[y] = true;
        dfs(my[y]);
      }
    };

    for (int x = 0; x < nx; x++) if (mx[x] == -1) dfs(x);
    for (int x = 0; x < nx; x++) if (!vis[x]) vcover.emplace_back(x);
    for (int y = nx; y < nx + ny; y++) if (vis[y]) vcover.emplace_back(y);
    return ans;
  }
} hk;
