// Author: Ian, CRyptoGRapheR
struct TwoSAT: SCC {
  TwoSAT(int n): SCC(2*n) {}
  // (var a == na) ∨ (var b == nb)
  void add_disjunction(int a,int na,int b,int nb) {
    a = 2*a^na, b = 2*b^nb;
    G[a^1].push_back(b);
    G[b^1].push_back(a);
  }
  vector<int> solve() {
    build();
    vector<int> assignment(n/2,0);
    for(int i=0; i<n/2; i++) {
      if (sccn[2*i] == sccn[2*i^1]) return {};
      assignment[i] = sccn[2*i] > sccn[2*i^1];
    }
    return assignment;
  }
};
