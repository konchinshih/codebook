// Author: CRyptoGRapheR
// Usage:
// 1. MCMF.init(n, s, t)
// 2. MCMF.add(u, v, cap, cost)
// 3. auto [max_flow, min_cost] = MCMF.flow()
typedef int Tcost;
const int MAXV = 20010;
const int INFf = 1000000;
const Tcost INFc  = 1e9;
struct MCMF {
  struct Edge{
    int v, cap;
    Tcost w;
    int rev;
    bool fw;
    Edge(){}
    Edge(int t2, int t3, Tcost t4, int t5, bool t6)
    : v(t2), cap(t3), w(t4), rev(t5), fw(t6) {}
  };
  int V, s, t;
  vector<Edge> G[MAXV];
  void init(int n){
    V = n;
    for(int i = 0; i <= V; i++) G[i].clear();
  }
  void add(int a, int b, int cap, Tcost w){
    G[a].push_back(Edge(b, cap, w, (int)G[b].size(), true));
    G[b].push_back(Edge(a, 0, -w, (int)G[a].size()-1, false));
  }
  Tcost d[MAXV];
  int id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  queue<int> q;
  pair<int, Tcost> flow(int _s, int _t){
    s = _s, t = _t;
    int mxf = 0; Tcost mnc = 0;
    while(1){
      fill(d, d+1+V, INFc); // need to use type cast
      fill(inqu, inqu+1+V, 0);
      fill(mom, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      q.push(s); inqu[s] = 1;
      while(q.size()){
        int u = q.front(); q.pop();
        inqu[u] = 0;
        for(int i = 0; i < (int) G[u].size(); i++){
          Edge &e = G[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]) q.push(v), inqu[v] = 1;
          }
        }
      }
      if(mom[t] == -1) break ;
      int df = INFf;
      for(int u = t; u != s; u = mom[u])
        df = min(df, G[mom[u]][id[u]].cap);
      for(int u = t; u != s; u = mom[u]){
        Edge &e = G[mom[u]][id[u]];
        e.cap             -= df;
        G[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df*d[t];
    }
    return make_pair(mxf, mnc);
  }
};
