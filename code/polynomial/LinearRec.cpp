// k-th term of a recurrence in O(n^2 log k)
// S[i] = \sum C[j] * S[i-1-j]
// Example: linearRec({0,1},{1,1},k) returns Fib(k).
// Require: ModBasic.cpp
using Poly = vector<ll>;
ll linearRec(Poly S, Poly C, ll k) {
  int n = C.size();
  auto combine = [&](Poly a, Poly b) {
    Poly res(n * 2 + 1);
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= n; j++)
        res[i + j] = add(res[i + j], mul(a[i], b[j]));
    for (int i = 2 * n; i > n; i--)
      for (int j = 0; j < n; j++)
        res[i - 1 - j] = add(res[i - 1 - j],
                              mul(res[i], C[j]));
    res.resize(n + 1);
    return res;
  };
  Poly pol(n + 1), e(pol);
  pol[0] = e[1] = 1;
  for (++k; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }
  ll res = 0;
  for (int i = 0; i < n; i++)
    res = add(res, mul(pol[i + 1], S[i]));
  return res;
}
