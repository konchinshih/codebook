// sum_phi_1_to_n — Φ(n) = sum_{i=1}^n φ(i)
// -----------------------------------------------------------
// Identity:  ∑_{v=1}^n Φ(⌊n/v⌋) = n(n+1)/2  ⇒
//            Φ(n) = n(n+1)/2 − ∑_{v=2}^n Φ(⌊n/v⌋).
// Enumerate v by blocks of equal ⌊n/v⌋ to get ~O(√n) states.
// Time Complexity: O(√n) with memoization.
// Notes:
//   - Uses memo on queried n values.
//   - Internal arithmetic uses unsigned __int128 to avoid overflow.
//   - Return type is unsigned long long; Φ(n) ~ 3 n^2 / π^2. For very large n
//     (e.g., > 10^10) consider changing the return type to unsigned __int128.

using u64 = unsigned long long;
using u128 = __uint128_t;

static inline u64 sum_phi_1_to_n(u64 n){
  static std::unordered_map<u64, u64> memo;
  auto it = memo.find(n);
  if (it != memo.end()) return it->second;

  u128 ans = (u128)n * (n + 1) / 2;     // n(n+1)/2
  for (u64 l = 2, r, q; l <= n; l = r + 1){
    q = n / l;
    r = n / q;
    u64 sub = sum_phi_1_to_n(q);
    ans -= (u128)(r - l + 1) * sub;
  }
  u64 ret = (u64)ans;                    // may overflow if n extremely large
  memo.emplace(n, ret);
  return ret;
}

