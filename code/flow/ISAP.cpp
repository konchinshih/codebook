// Author: CRyptoGRapheR
// 1-based: vertices are numbered 1 ~ n
// 1. flow.init(n, s, t);
//    n = #vertices, s, t = source, sink
// 2. flow.addEdge(u, v, c);  // u, v in [1, n]
// 3. call: int ans = flow.flow();
// => ans = max flow value from s to t
// Time: O(V^2 * E) worst case, usually much faster in practice
static const int MAXV=50010;
static const int INF =1000000;
struct Maxflow{
  struct Edge{
    int v,c,r;
    Edge(int _v,int _c,int _r):v(_v),c(_c),r(_r){}
  };
  int s,t; vector<Edge> G[MAXV];
  int iter[MAXV],d[MAXV],gap[MAXV],tot;
  void init(int n,int _s,int _t){
    tot=n,s=_s,t=_t;
    for(int i=1;i<=tot;i++){
      G[i].clear(); iter[i]=d[i]=gap[i]=0;
    }
  }
  void addEdge(int u,int v,int c){
    G[u].push_back(Edge(v,c,SZ(G[v])));
    G[v].push_back(Edge(u,0,SZ(G[u])-1));
  }
  int DFS(int p,int flow){
    if(p==t) return flow;
    for(int &i=iter[p];i<SZ(G[p]);i++){
      Edge &e=G[p][i];
      if(e.c>0&&d[p]==d[e.v]+1){
        int f=DFS(e.v,min(flow,e.c));
        if(f){ e.c-=f; G[e.v][e.r].c+=f; return f; }
      } 
    }
    if((--gap[d[p]])==0) d[s]=tot;
    else{ d[p]++; iter[p]=0; ++gap[d[p]]; }
    return 0;
  }
  int flow(){
    int res=0;
    for(res=0,gap[0]=tot;d[s]<tot;res+=DFS(s,INF));
    return res;
  }
  void reset(){
    for(int i=1;i<=tot;i++) iter[i]=d[i]=gap[i]=0;
  }
} flow;
