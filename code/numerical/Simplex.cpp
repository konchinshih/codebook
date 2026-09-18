// Maximize c^T x subject to Ax <= b, x >= 0.
// Returns -inf if infeasible, inf if unbounded.
// Otherwise returns the maximum value and stores x.
// Numerical stability is not guaranteed.
using T = double;
using vd = vector<T>;
using vvd = vector<vd>;

const T eps = 1e-8;
const T inf = numeric_limits<T>::infinity();

struct LPSolver {
  int m, n;
  vi N, B;
  vvd D;

  LPSolver(const vvd& A, const vd& b, const vd& c)
      : m(sz(b)), n(sz(c)), N(n + 1), B(m),
        D(m + 2, vd(n + 2)) {
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) D[i][j] = A[i][j];
    for (int i = 0; i < m; i++) {
      B[i] = n + i;
      D[i][n] = -1;
      D[i][n + 1] = b[i];
    }
    for (int j = 0; j < n; j++) D[m][j] = -c[j];
    N[n] = -1;
    D[m + 1][n] = 1;
  }

  void pivot(int r, int s) {
    T* a = D[r].data();
    T inv = 1 / a[s];
    for (int i = 0; i < m + 2; i++) if (i != r &&
        abs(D[i][s]) > eps) {
      T* b = D[i].data();
      T inv2 = b[s] * inv;
      for (int j = 0; j < n + 2; j++) b[j] -= a[j] * inv2;
      b[s] = a[s] * inv2;
    }
    for (int j = 0; j < n + 2; j++)
      if (j != s) D[r][j] *= inv;
    for (int i = 0; i < m + 2; i++)
      if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }

  bool simplex(int phase) {
    int x = m + phase - 1;
    for (;;) {
      int s = -1;
      for (int j = 0; j <= n; j++) {
        if (N[j] == -phase) continue;
        if (s == -1 || pair(D[x][j], N[j]) <
            pair(D[x][s], N[s])) s = j;
      }
      if (D[x][s] >= -eps) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
        if (D[i][s] <= eps) continue;
        if (r == -1 || pair(D[i][n + 1] / D[i][s], B[i]) <
            pair(D[r][n + 1] / D[r][s], B[r])) r = i;
      }
      if (r == -1) return false;
      pivot(r, s);
    }
  }

  T solve(vd& x) {
    int r = 0;
    for (int i = 1; i < m; i++)
      if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -eps) {
      pivot(r, n);
      if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
      for (int i = 0; i < m; i++) if (B[i] == -1) {
        int s = 0;
        for (int j = 1; j <= n; j++)
          if (s == 0 || pair(D[i][j], N[j]) <
              pair(D[i][s], N[s])) s = j;
        pivot(i, s);
      }
    }
    bool ok = simplex(1);
    x = vd(n);
    for (int i = 0; i < m; i++)
      if (B[i] < n) x[B[i]] = D[i][n + 1];
    return ok ? D[m][n + 1] : inf;
  }
};
