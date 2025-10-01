// Author: Benson
// Function: Max Flow, O(V^2 E)
// Usage: Call init(n) first, then add(u, v, w) based on your model
// (!) vertices 0-based
// >>> flow() := return max flow
// >>> find_cut() := return min cut + store cut set in dinic.cut
// >>> find_matching() := return |M| + store matching plan in dinic.matching
// >>> flow_decomposition := return max flow + store decomposition in dinic.D
#define int long long
#define eb emplace_back
#define ALL(a) a.begin(), a.end()
struct Dinic {
  struct Edge {
    // t: to | C: original capacity | c: current capacity | r: residual edge | f: current flow
    int t, C, c, r, f;
    bool fw;  // is in forward-edge graph
    Edge() {}
    Edge(int _t, int _C, int _r, bool _fw, int _f=0):
      t(_t), C(_C), c(_C), r(_r), fw(_fw), f(_f) {}
  };
  vector<vector<Edge>> G;
  vector<int> dis, iter;
  int n, s, t;
  void init(int _n) {
    n = _n;
    G.resize(n), dis.resize(n), iter.resize(n);
    for(int i = 0; i < n; ++i)
      G[i].clear();
  }
  void add(int a, int b, int c) {
    G[a].eb(b, c, G[b].size(), true);
    G[b].eb(a, 0, G[a].size() - 1, false);
  }
  bool bfs() {
    fill(ALL(dis), -1);
    dis[s] = 0;
    queue<int> que;
    que.push(s);
    while(!que.empty()) {
      int u = que.front(); que.pop();
      for(auto& e : G[u]) {
        if(e.c > 0 && dis[e.t] == -1) {
          dis[e.t] = dis[u] + 1;
          que.push(e.t);
    } } }
    return dis[t] != -1;
  }
  int dfs(int u, int cur) {
    if(u == t) return cur;
    for(int &i = iter[u]; i < (int)G[u].size(); ++i) {
      auto& e = G[u][i];
      if(e.c > 0 && dis[u] + 1 == dis[e.t]) {
        int ans = dfs(e.t, min(cur, e.c));
        if(ans > 0) {
          G[e.t][e.r].c += ans;
          e.c -= ans;
          return ans;
    } } }
    return 0;
  }
// find max flow
  int flow(int a, int b) {
    s = a, t = b;
    int ans = 0;
    while(bfs()) {
      fill(ALL(iter), 0);
      int tmp;
      while((tmp = dfs(s, INF)) > 0)
        ans += tmp;
    }
    return ans;
  }
// min cut plan
  vector<pair<pair<int, int>, int>> cut;
  int find_cut(int a, int b) {
    int cut_sz = flow(a, b);
    vector<int> vis(n, 0);
    cut.clear();
    function<void(int)> dfs = [&](int u) {
      vis[u] = 1;
      for (auto& e : G[u])
        if (e.c > 0 && !vis[e.t])
          dfs(e.t);
    };
    dfs(a);
    for (int u = 0; u < n; u++)
      if (vis[u])
        for (auto& e : G[u])
          if (!vis[e.t])
            cut.eb(make_pair(make_pair(u, e.t), G[e.t][e.r].c));
    return cut_sz;
  }
// bipartite matching plan
  vector<pair<int, int>> matching;
  int find_matching(int Xstart, int Xend, int Ystart, int Yend, int a, int b) {
    int msz = flow(a, b);
    matching.clear();
    for (int x = Xstart; x <= Xend; x++)
      for (auto& e : G[x])
        if (e.c == 0 && Ystart <= e.t && e.t <= Yend)
          matching.emplace_back(make_pair(x, e.t));
    return msz;
  }
// flow decomposition
  vector<pair<int, vector<int>>> D; // (flow amount, [path p1 ... pk])
  int flow_decomposition(int a, int b) {
    int mxflow = flow(a, b);

    vector<vector<Edge>> fG(n); // graph consists of forward edges
    for (int u = 0; u < n; u++) {
      for (auto& e : G[u]) {
        if (e.fw) {
          e.f = e.C - e.c;
          if (e.f > 0) fG[u].eb(e);
    } } }

    vector<int> vis;
    function<int(int, int)> dfs = [&](int u, int cur) {
      if (u == b) {
        D.back().second.eb(u);
        return cur;
      }
      vis[u] = 1;
      for (auto& e : fG[u]) {
        if (e.f > 0 && !vis[e.t]) {
          int ans = dfs(e.t, min(cur, e.f));
          if (ans > 0) {
            e.f -= ans;
            D.back().second.eb(u);
            return ans;
      } } }
      return 0LL;
    };
    D.clear();
    int quota = mxflow;
    while (quota > 0) {
      D.emplace_back(make_pair(0, vector<int>()));
      vis.assign(n, 0);
      int f = dfs(a, INF);
      if (f == 0) break;
      reverse(D.back().second.begin(), D.back().second.end());
      D.back().first = f, quota -= f;
    }
    return mxflow;
  }
};
