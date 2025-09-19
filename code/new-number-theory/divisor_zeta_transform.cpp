// divisor_zeta_transform (on divisors)
// ------------------------------------
// In-place: F[n] = sum_{d | n} f[d]  for n = 1..N  (index 0 unused).
// Complexity: O(N log N).  Works for any T with operator+=.
//
// Usage:
//   vector<T> a = ...;  // a[1..N]
//   divisor_zeta_transform(a);  // now a[n] = sum_{d|n} original_a[d]
template<class T>
static inline void divisor_zeta_transform(std::vector<T>& a){
  int n = (int)a.size() - 1; if (n <= 0) return;
  for (int i = 1; i <= n; ++i)
    for (int j = i + i; j <= n; j += i)
      a[j] += a[i];
}

