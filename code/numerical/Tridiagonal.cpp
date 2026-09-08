/** Author: Ulf Lundstrom, Simon Lindholm (License: CC0)
 * Description: Solves the tridiagonal matrix equation system:
 *   [ b_0 ]   [ d_0  p_0   0    0   ...   0   ] [ x_0 ]
 *   [ b_1 ]   [ q_0  d_1  p_1   0   ...   0   ] [ x_1 ]
 *   [ b_2 ] = [  0   q_1  d_2  p_2  ...   0   ] [ x_2 ]
 *   [ ... ]   [ ...  ...  ...  ...  ...  ...  ] [ ... ]
 *   [b_n-1]   [  0    0   ...   0  q_n-2 d_n-1] [x_n-1]
 * Application:
 *   Solves linear recurrence systems of the form:
 *     a_i = b_i * a_{i-1} + c_i * a_{i+1} + d_i  (1 <= i <= n)
 *   where a_0, a_{n+1}, b_i, c_i, and d_i are given.
 *   The solution vector a can be obtained via:
 *     d = {  1, -1,  -1, ...,  -1,     1 }
 *     p = {  0, c_1, c_2, ..., c_n       }
 *     q = { b_1, b_2, ..., b_n, 0        }
 *     b = { a_0, d_1, d_2, ..., d_n, a_n+1 }
 * Numerical Stability:
 *   - Fails if the solution is not unique.
 *   - Numerically stable without pivot checks if:
 *     1) Strictly diagonally dominant:
 *        |d_i| > |p_i| + |q_{i-1}| for all i, OR
 *        |d_i| > |p_{i-1}| + |q_i| for all i
 *     2) The matrix is symmetric positive-definite.
 * Complexity: O(N) time, O(N) space. Status: Brute-force tested mod 5 and 7, stress-tested for real matrices. */
typedef double T;
vector<T> tridiagonal(vector<T> diag, const vector<T>& super,
    const vector<T>& sub, vector<T> b) {
  int n = sz(b); vi tr(n);
  rep(i,0,n-1) {
    if (abs(diag[i]) < 1e-9 * abs(super[i])) { // diag[i] == 0
      b[i+1] -= b[i] * diag[i+1] / super[i];
      if (i+2 < n) b[i+2] -= b[i] * sub[i+1] / super[i];
      diag[i+1] = sub[i]; tr[++i] = 1;
    } else {
      diag[i+1] -= super[i]*sub[i]/diag[i];
      b[i+1] -= b[i]*sub[i]/diag[i];
    }
  }
  for (int i = n; i--;) {
    if (tr[i]) {
      swap(b[i], b[i-1]);
      diag[i-1] = diag[i];
      b[i] /= super[i-1];
    } else {
      b[i] /= diag[i];
      if (i) b[i-1] -= b[i]*super[i-1];
    }
  }
  return b;
}
