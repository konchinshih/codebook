// sum_mu_1_to_n — M(n) = sum_{i=1}^n μ(i)  (Mertens function)
// ------------------------------------------------------------
// μ (Möbius function) basics:
//   μ(1)=1; μ(n)=0 if n has a squared prime factor; otherwise μ(n)=(-1)^{ω(n)}
//   where ω(n) is the number of distinct prime factors.  Key identity:
//   ∑_{d|n} μ(d) = [n == 1], which makes μ the inverse of the divisor–zeta transform.
// Recurrence used here:
//   M(n) = 1 − ∑_{v=2}^n M(⌊n/v⌋)
// Enumerate v by blocks where ⌊n/v⌋ is constant to reduce states to ~O(√n).
// Time Complexity: O(√n) with memoization.

#include <unordered_map>
#include <cstdint>
using u64 = unsigned long long;

static inline long long sum_mu_1_to_n(u64 n){
  static std::unordered_map<u64, long long> memo = {{0,0},{1,1}};
  auto it = memo.find(n);
  if (it != memo.end()) return it->second;

  long long ans = 1;  // start from μ(1)=1
  for (u64 l = 2, r, q; l <= n; l = r + 1){
    q = n / l;
    r = n / q;
    long long sub = sum_mu_1_to_n(q);
    ans -= (long long)(r - l + 1) * sub;
  }
  memo.emplace(n, ans);
  return ans;
}

