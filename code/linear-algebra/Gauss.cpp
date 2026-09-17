// In-place RREF over Z_mod (mod prime); returns {rank, det}.
// det is valid only when A is square.
// Values must be normalized.
pair<int, ll> gauss(vector<vector<ll>>& A) {
  int n = sz(A), m = sz(A[0]), rank = 0;
  ll det = 1;
  for (int c = 0; c < m && rank < n; c++) {
    int piv = rank;
    while (piv < n && !A[piv][c]) piv++;
    if (piv == n) {
      det = 0;
      continue;
    }
    if (piv != rank) {
      swap(A[piv], A[rank]);
      det = sub(0, det);
    }
    ll inv = Pow(A[rank][c], mod - 2);
    det = mul(det, A[rank][c]);
    for (ll& x : A[rank]) x = mul(x, inv);
    for (int i = 0; i < n; i++) if (i != rank && A[i][c]) {
      ll f = A[i][c];
      for (int j = c; j < m; j++)
        A[i][j] = sub(A[i][j], mul(f, A[rank][j]));
    }
    rank++;
  }
  return {rank, det};
}
