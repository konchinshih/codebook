// In-place RREF over GF(2) on the first m columns of A
// (rows are bitsets; extra columns, e.g. an augmented b,
// are carried along). Returns {rank, det}; det is valid
// only when A is n x m square.
// For an XOR basis, run it and read the nonzero rows.
const int N = 1000;
using bs = bitset<N>;
pair<int, int> gaussBinary(vector<bs>& A, int m) {
  int n = A.size(), rank = 0;
  for (int c = 0; c < m && rank < n; c++) {
    int piv = rank;
    while (piv < n && !A[piv][c]) piv++;
    if (piv == n) continue;
    swap(A[piv], A[rank]);
    for (int i = 0; i < n; i++)
      if (i != rank && A[i][c]) A[i] ^= A[rank];
    rank++;
  }
  return {rank, n == m && rank == n};
}
