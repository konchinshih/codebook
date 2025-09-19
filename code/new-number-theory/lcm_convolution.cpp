// lcm_convolution
// ---------------
// Given f,g on 1..N, compute h where
//   h[n] = sum_{lcm(i,j)=n} f[i] * g[j].
// Trick: divisor-zeta on f,g  → pointwise multiply → divisor-mobius inverse.
// Proof sketch: Let F(n)=∑_{d|n}f(d), G(n)=∑_{d|n}g(d).
// Then H(n)=∑_{d|n}h(d) = F(n)G(n) since lcm(i,j)|n ⇔ i|n and j|n.
// So h = mobius_divisor(H).
// Complexity: O(N log N). Index 0 unused.
template<class T>
static inline std::vector<T> lcm_convolution(const std::vector<T>& f,
                                             const std::vector<T>& g){
  int n = (int)std::min(f.size(), g.size()) - 1;
  std::vector<T> A(f.begin(), f.begin()+n+1), B(g.begin(), g.begin()+n+1);

  auto div_zeta = [&](std::vector<T>& a){
    for (int i = 1; i <= n; ++i)
      for (int j = i + i; j <= n; j += i)
        a[j] += a[i];            // a[j] = ∑_{d|j} f[d]
  };
  auto div_mobius = [&](std::vector<T>& a){
    for (int i = 1; i <= n; ++i)
      for (int j = i + i; j <= n; j += i)
        a[j] -= a[i];            // inverse of the above
  };

  div_zeta(A); div_zeta(B);
  for (int i = 1; i <= n; ++i) A[i] *= B[i];  // H(n) = F(n)G(n)
  div_mobius(A);                              // recover h
  return A; // A[n] = ∑_{lcm(i,j)=n} f[i]g[j]
}

