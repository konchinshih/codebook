// solveBinary(A, b, m): Ax=b over GF(2), m = #variables.
// nullity == -1 if no solution. Self-contained RREF (no
// column swaps) so pivot columns are known for the basis.
struct BinSolution { int nullity; bs xp; vector<bs> basis; };
BinSolution solveBinary(vector<bs> A, vector<int> b, int m) {
  int n = A.size(), rank = 0;
  vector<int> pcol;  // pivot columns
  for (int c = 0; c < m && rank < n; c++) {
    int piv = rank;
    while (piv < n && !A[piv][c]) piv++;
    if (piv == n) continue;
    swap(A[piv], A[rank]); swap(b[piv], b[rank]);
    for (int i = 0; i < n; i++) if (i != rank && A[i][c])
      A[i] ^= A[rank], b[i] ^= b[rank];
    pcol.push_back(c); rank++;
  }
  for (int i = rank; i < n; i++) if (b[i]) return {-1, {}, {}};
  BinSolution sol{m - rank, {}, {}};
  bs isp;  // is the column a pivot?
  for (int i = 0; i < rank; i++)
    sol.xp[pcol[i]] = b[i], isp[pcol[i]] = 1;
  for (int j = 0; j < m; j++) if (!isp[j]) {
    bs d; d[j] = 1;
    for (int i = 0; i < rank; i++) d[pcol[i]] = A[i][j];
    sol.basis.push_back(d);
  }
  return sol;
}
