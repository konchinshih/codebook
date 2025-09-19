// dirichlet_convolution
// ---------------------
// Given f,g on indices 1..n, returns h where
//   h[n] = sum_{d | n} f[d] * g[n/d]   (Dirichlet convolution).
// Input: f.size() == g.size() == n+1 (index 0 unused).
// Complexity: O(n log n).  Works with plain integers or your ModInt type.
template<class T>
static inline std::vector<T> dirichlet_convolution(const std::vector<T>& f,
                                                   const std::vector<T>& g){
  int n = (int)std::min(f.size(), g.size()) - 1;
  std::vector<T> h(n + 1, T(0));
  for (int i = 1; i <= n; ++i){
    if (f[i] == T(0)) continue;
    T fi = f[i];
    int j = i, k = 1;
    for (; j <= n; j += i, ++k) h[j] += fi * g[k]; // k == j / i
  }
  return h;
}

