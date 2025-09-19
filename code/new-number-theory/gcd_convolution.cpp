// gcd_convolution (correct)
// -------------------------
// Given f,g on 1..N, compute h where
//   h[n] = sum_{gcd(i,j)=n} f[i] * g[j].
// Steps: multiples zeta on f,g → pointwise multiply → Möbius inversion.
// Complexity: O(N log N). Index 0 unused.
// T must support default T(0), +=, -=, *=.

template<class T>
static inline std::vector<T> gcd_convolution(const std::vector<T>& f,
                                             const std::vector<T>& g){
  int n = (int)std::min(f.size(), g.size()) - 1;
  if (n <= 0) return std::vector<T>(1, T(0));

  std::vector<T> F(f.begin(), f.begin()+n+1),
                 G(g.begin(), g.begin()+n+1);

  // multiples zeta: A[i] = sum_{m: i|m, m<=n} a[m]
  auto mult_zeta = [&](std::vector<T>& a){
    for (int i = 1; i <= n; ++i)
      for (int j = i + i; j <= n; j += i)
        a[i] += a[j];
  };
  mult_zeta(F); mult_zeta(G);

  // pointwise multiply
  std::vector<T> P(n+1);
  for (int i = 1; i <= n; ++i) P[i] = F[i] * G[i];

  // Möbius μ[1..n] by linear sieve
  std::vector<int> mu(n+1, 0), lp(n+1, 0), primes;
  mu[1] = 1;
  for (int i = 2; i <= n; ++i){
    if (!lp[i]){ lp[i] = i; primes.push_back(i); mu[i] = -1; }
    for (int p : primes){
      long long v = 1LL * i * p;
      if (v > n) break;
      lp[v] = p;
      if (i % p == 0){ mu[v] = 0; break; }  // square factor
      else mu[v] = -mu[i];
    }
  }

  // Möbius inversion over multiples:
  // h[i] = sum_{t>=1, i*t<=n} μ[t] * P[i*t]
  std::vector<T> H(n+1);
  for (int i = 1; i <= n; ++i){
    T s = T(0);
    for (int t = 1, k = i; k <= n; ++t, k += i){
      if (mu[t] == 0) continue;
      if (mu[t] > 0) s += P[k];
      else           s -= P[k];
    }
    H[i] = s;
  }
  return H;
}

