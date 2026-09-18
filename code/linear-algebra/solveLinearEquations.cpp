// Author: Gino
// solve(Augmented Matrix), nullity == -1 if no solution
struct Solution {
  int nullity; vector<ll> xp; vector<vector<ll>> basis;
};
Solution solve(vector<vector<ll>>& A) {  // augmented matrix
  int n = A.size(), m = A[0].size() - 1;
  auto [rank, det] = gauss(A);
  for (int i = 0; i < n; i++) if (A[i][m] != 0) {
    if (ranges::all_of(A[i] | views::take(m),
          [](ll x){ return x == 0; }))
      return {-1, {}, {}};
  }
  Solution sol;
  vector<int> pcol(rank);  // pivot columns
  vector<bool> isp(m, false);  // is the column a pivot?
  for (int i = 0; i < rank; i++) {
    auto it = ranges::find(A[i], 1);
    pcol[i] = ranges::distance(A[i].begin(), it);
    isp[pcol[i]] = true;
  }
  sol.nullity = m - rank;
  sol.xp.assign(m, 0);
  for (int i = 0; i < rank; i++) sol.xp[pcol[i]] = A[i][m];
  for (int j = 0; j < m; j++) if (!isp[j]) {
    vector<ll> d(m, 0); d[j] = 1;
    for (int i = 0; i < rank; i++) d[pcol[i]] = sub(0, A[i][j]);
    sol.basis.push_back(d);
  }
  return sol;
}
