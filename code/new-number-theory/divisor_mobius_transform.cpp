// divisor_mobius_transform (inverse of divisor zeta)
// --------------------------------------------------
// In-place: given F[n] = sum_{d|n} f[d] (n=1..N), transform array back to f.
// Complexity: O(N log N). Works for any T with operator-=.
//
// Usage:
//   vector<T> a = F;            // a[1..N] holds zeta-transformed values
//   divisor_mobius_transform(a); // now a[n] == original f[n]
template<class T>
static inline void divisor_mobius_transform(std::vector<T>& a){
  int n = (int)a.size() - 1; if (n <= 0) return;
  for (int i = n; i >= 1; --i)
    for (int j = i + i; j <= n; j += i)
      a[j] -= a[i];
}

