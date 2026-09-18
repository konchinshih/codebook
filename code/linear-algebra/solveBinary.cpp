// solveBinary(A, m): A is augmented (column m is b),
// m = #variables. nullity == -1 if no solution.
struct BinSolution { int nullity; bs xp; vector<bs> basis; };
BinSolution solveBinary(vector<bs>& A, int m) {
  int n = A.size();
  auto [rank, det] = gaussBinary(A, m + 1);
  for (int i = 0; i < n; i++)  // row: 0 ... 0 | 1
    if (A[i]._Find_first() == m) return {-1, {}, {}};
  BinSolution sol{m - rank, {}, {}};
  vector<int> pcol(rank);  // pivot columns
  bs isp;  // is the column a pivot?
  for (int i = 0; i < rank; i++) {
    pcol[i] = A[i]._Find_first();
    isp[pcol[i]] = 1; sol.xp[pcol[i]] = A[i][m];
  }
  for (int j = 0; j < m; j++) if (!isp[j]) {
    bs d; d[j] = 1;
    for (int i = 0; i < rank; i++) d[pcol[i]] = A[i][j];
    sol.basis.push_back(d);
  }
  return sol;
}
