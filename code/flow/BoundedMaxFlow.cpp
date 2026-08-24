// Author: CRyptoGRapheR
// Max flow with lower/upper bound on edges (source-sink version)
// <!> 1-based: original vertices are numbered 1 ~ n.
//     Super source, sink: n+1, n+2 respectively.
// <!> dependency: ISAP.cpp
// 1. n = #vertices (1 ~ n), m = #edges
//    s, t = original source, sink (both in [1, n])
// 2. l[i], r[i]  := edge i goes from l[i] -> r[i]   (l[i], r[i] in [1, n])
// 3. a[i], b[i]  := flow on edge i must lie in [a[i], b[i]]
// 4. int ans = solve(n, m, s, t);
// => ans == -1 : no feasible flow exists
// => ans       : feasible max flow value
// <!> N, M must be large enough for original graph + 2 super nodes
// Time: O(V^2 E), Space: O(V + E)
int in[N], out[N], l[M], r[M], a[M], b[M];
int solve(int n, int m, int s, int t){
  flow.init(n+2, n+1, n+2); // super source = n+1, super sink = n+2
  for(int i = 0; i < m; i++){
    in[r[i]] += a[i]; out[l[i]] += a[i];
    flow.addEdge(l[i], r[i], b[i] - a[i]);
    // flow from l[i] to r[i] must lie in [a[i], b[i]]
  }
  int nd = 0;
  for(int i = 1; i <= n; i++){
    if(in[i] < out[i]){
      flow.addEdge(i, flow.t, out[i] - in[i]);
      nd += out[i] - in[i];
    }
    if(out[i] < in[i])
      flow.addEdge(flow.s, i, in[i] - out[i]);
  }
  flow.addEdge(t, s, INF); // original sink -> source
  if(flow.flow() != nd) return -1; // infeasible
  int ans = flow.G[s].back().c; // t->s edge's current flow = feasible flow s->t
  flow.G[s].back().c = flow.G[t].back().c = 0;
  for(size_t i = 0; i < flow.G[flow.s].size(); i++){
    Maxflow::Edge &e = flow.G[flow.s][i];
    flow.G[flow.s][i].c = 0; flow.G[e.v][e.r].c = 0;
  }
  for(size_t i = 0; i < flow.G[flow.t].size(); i++){
    Maxflow::Edge &e = flow.G[flow.t][i];
    flow.G[flow.t][i].c = 0; flow.G[e.v][e.r].c = 0;
  }
  flow.addEdge(flow.s, s, INF); flow.addEdge(t, flow.t, INF);
  flow.reset(); // keeps G[] intact, only resets search state
  return ans + flow.flow();
}
