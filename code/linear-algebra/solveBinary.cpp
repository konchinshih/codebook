// solveBinary(A, b, m): Ax=b over GF(2), m = #variables,
// nullity == -1 if no solution
struct BinSolution { int nullity; bs xp; vector<bs> basis; };
BinSolution solveBinary(vector<bs>& A, vector<int>& b, int m) {
  int n = A.size(), rank = gaussBinary(A, b, m);
  for (int i = rank; i < n; i++) if (b[i]) return {-1, {}, {}};
  BinSolution sol{m - rank, {}, {}};
  vector<int> pcol(rank);  // pivot columns
  bs isp;  // is the column a pivot?
  for (int i = 0; i < rank; i++) {
    pcol[i] = A[i]._Find_first();
    isp[pcol[i]] = 1; sol.xp[pcol[i]] = b[i];
  }
  for (int j = 0; j < m; j++) if (!isp[j]) {
    bs d; d[j] = 1;
    for (int i = 0; i < rank; i++) d[pcol[i]] = A[i][j];
    sol.basis.push_back(d);
  }
  return sol;
}
