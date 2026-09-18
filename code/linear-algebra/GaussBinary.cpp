// In-place RREF over GF(2); rows are bitsets, m = #columns,
// b = RHS (all-zero if unused); returns rank.
// For an XOR basis, use all-zero b and read the nonzero rows.
const int N = 1000;
using bs = bitset<N>;
int gaussBinary(vector<bs>& A, vector<int>& b, int m) {
  int n = A.size(), rank = 0;
  for (int c = 0; c < m && rank < n; c++) {
    int piv = rank;
    while (piv < n && !A[piv][c]) piv++;
    if (piv == n) continue;
    swap(A[piv], A[rank]); swap(b[piv], b[rank]);
    for (int i = 0; i < n; i++) if (i != rank && A[i][c])
      A[i] ^= A[rank], b[i] ^= b[rank];
    rank++;
  }
  return rank;
}
