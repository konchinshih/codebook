// Pollard–Rho (64-bit) — finds a nontrivial factor of composite n
// ---------------------------------------------------------------
// Requires: miller_rabin_64(n), mul_mod_u64(a,b,mod)
// API: pollard_rho_64(n) -> factor in (1,n), may retry internally until found.
// Notes:
//   - Handles even n quickly.
//   - Uses Brent's cycle detection + batch GCD (faster in practice).
//   - For prime n, this routine may loop; typical usage first checks MR.
// Complexity (heuristic): ~ Õ(n^{1/4}) modular multiplications on random composites.

using u64 = uint64_t; using u128 = __uint128_t;

static inline u64 splitmix64(u64& s){
  u64 z = (s += 0x9e3779b97f4a7c15ull);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ull;
  z = (z ^ (z >> 27)) * 0x94d049bb133111ebull;
  return z ^ (z >> 31);
}

static inline u64 f_rho(u64 x, u64 c, u64 n){
  return (u64)(( (u128)x * x + c ) % n);
}

static inline u64 pollard_rho_64(u64 n){
  if ((n & 1ull) == 0) return 2;
  // It’s fine if caller first ensures n is composite via Miller–Rabin.
  static u64 seed = 0x123456789abcdef0ull;
  for(;;){
    u64 c = (splitmix64(seed) % (n - 1)) + 1;       // in [1, n-1]
    u64 y = (splitmix64(seed) % (n - 2)) + 2;       // in [2, n-1]
    u64 x = y, d = 1, q = 1;
    const u64 m = 128;                               // batch size for gcd
    // Brent's algorithm
    for(u64 r = 1; d == 1; r <<= 1){
      x = y;
      for(u64 i = 0; i < r; ++i) y = f_rho(y, c, n);
      for(u64 k = 0; k < r && d == 1; k += m){
        u64 lim = (r - k < m) ? (r - k) : m;
        for(u64 i = 0; i < lim; ++i){
          y = f_rho(y, c, n);
          u64 diff = x > y ? x - y : y - x;
          q = (u64)((u128)q * diff % n);
        }
        d = std::gcd(q, n);
      }
    }
    if (d == 1){
      // rare: try another (c, y)
      continue;
    } else if (d == n){
      // fallback: walk one-by-one to extract a factor
      do {
        y = f_rho(y, c, n);
        u64 diff = x > y ? x - y : y - x;
        d = std::gcd(diff, n);
      } while(d == 1);
      if (d == n) continue;
    }
    return d; // 1 < d < n
  }
}

