// Function: Max Flow + Flow Decomposition, O(V^2 E)
// init -> addEdge; vertices 0-based
// >>> flow() := return max flow
// >>> flow_decomposition() := return max flow + store decomposition in flow.D
struct Dinic{
  static const int MXN=10000;
  struct Edge{ int v,c,r,C; bool fw; };
  int n,s,t,level[MXN]; vector<Edge> G[MXN];
  void init(int _n,int _s,int _t){
    n=_n; s=_s; t=_t;
    for (int i=0; i<n; i++) G[i].clear(); }
  void addEdge(int u,int v,int c){
    G[u].push_back({v,c,(int)G[v].size(),c,true});
    G[v].push_back({u,0,(int)G[u].size()-1,0,false}); }
  bool BFS(){
    for (int i=0;i<n;i++) level[i]=-1;
    queue<int> que; que.push(s); level[s]=0;
    while(!que.empty()){
      int u=que.front(); que.pop();
      for (auto &it:G[u]){
        if(it.c>0&&level[it.v]==-1){
          level[it.v]=level[u]+1; que.push(it.v);
    } } }
    return level[t]!=-1; }
  int DFS(int u,int nf){
    if(u==t) return nf;
    int res=0;
    for (auto &it:G[u]){
      if(it.c>0&&level[it.v]==level[u]+1){
        int tf=DFS(it.v,min(nf,it.c));
        res+=tf; nf-=tf; it.c-=tf;
        G[it.v][it.r].c+=tf;
        if(nf==0) return res;
      } }
    if(!res) level[u]=-1;
    return res; }
  int flow(int res=0){
    while(BFS()) res+=DFS(s,2147483647);
    return res;
  } // reset: do nothing
  vector<pair<int, vector<int>>> D; // (flow amount, [path p1 ... pk])
  int flow_decomposition(){
    int mxflow = flow();
    vector<vector<Edge>> fG(n); // graph with forward edges
    for (int u = 0; u < n; u++) {
      for (auto &e : G[u]) {
        if (e.fw && e.C - e.c > 0)
          fG[u].push_back({e.v, e.C - e.c, e.r, e.C, e.fw});
    } }
    vector<int> vis(n, 0);
    function<int(int, int)> dfs = [&](int u, int cur) {
      if (u == t) {
        D.back().second.push_back(u);
        return cur; }
      vis[u] = 1;
      for (auto &e : fG[u]) {
        if (e.c > 0 && !vis[e.v]) {
          int ans = dfs(e.v, min(cur, e.c));
          if (ans > 0) {
            e.c -= ans;
            D.back().second.push_back(u);
            return ans;
      } } }
      return 0; };
    D.clear();
    int quota = mxflow;
    while (quota > 0) {
      D.emplace_back(0, vector<int>());
      fill(vis.begin(), vis.end(), 0);
      int f = dfs(s, 2147483647);
      if (f == 0) break;
      reverse(D.back().second.begin(),
        D.back().second.end());
      D.back().first = f, quota -= f;
    }
    return mxflow; }
}flow;
