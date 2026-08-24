// Author: Gino
// Function: Max Bipartite Matching in O(V sqrt(E))
// Usage:
// >>> init(nx, ny) -> add(x, y (+nx))
// >>> hk.max_matching() := the matching plan stores in mx, my
// >>> hk.min_vertex_cover() := the vertex cover plan stores in vcover
// (!) vertices are 0-based: X = [0, nx), Y = [nx, nx+ny)
#define pb emplace_back
struct HopcroftKarp {
  int n, nx, ny;
  vector<vector<int> > G;
  vector<int> mx, my;
  void init(int _nx, int _ny) {
    nx = _nx, ny = _ny;
    n = nx + ny;
    G.assign(n, vector<int>());
  }
  void add(int x, int y) { G[x].pb(y); G[y].pb(x); }
  int max_matching() {
    vector<int> dis, vis;
    mx.assign(n, -1); my.assign(n, -1);
    function<bool(int)> dfs = [&](int x) {
      vis[x] = 1;
      for (int y : G[x]) {
        int p = my[y];
        if (p == -1 || (dis[p] == dis[x] + 1 && !vis[p] && dfs(p)))
          return mx[x] = y, my[y] = x, true;
      }
      return false;
    };
    while (true) {
      dis.assign(n, -1);
      queue<int> q;
      for (int x = 0; x < nx; x++)
        if (mx[x] == -1) dis[x] = 0, q.push(x);
      while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : G[x])
          if (my[y] != -1 && dis[my[y]] == -1)
            dis[my[y]] = dis[x] + 1, q.push(my[y]);
      }
      vis.assign(n, 0);
      bool found = false;
      for (int x = 0; x < nx; x++)
        if (mx[x] == -1 && dfs(x)) found = true;
      if (!found) break;
    }
    int ans = 0;
    for (int x = 0; x < nx; x++) if (mx[x] != -1) ans++;
    return ans;
  }
  vector<int> vcover;
  int min_vertex_cover() {
    int ans = max_matching();
    vector<int> vis(n, 0);
    function<void(int)> dfs = [&](int x) {
      vis[x] = true;
      for (int y : G[x]) {
        if (y == mx[x] || my[y] == -1 || vis[y]) continue;
        vis[y] = true;
        dfs(my[y]);
      }
    };
    for (int x = 0; x < nx; x++) if (mx[x] == -1) dfs(x);
    vcover.clear();
    for (int x = 0; x < nx; x++) if (!vis[x]) vcover.pb(x);
    for (int y = nx; y < nx + ny; y++) if (vis[y]) vcover.pb(y);
    return ans;
  }
} hk;
