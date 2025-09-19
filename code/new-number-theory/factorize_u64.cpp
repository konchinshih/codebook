// factorize_u64 — 64-bit integer factorization via Miller–Rabin + Pollard–Rho
// ---------------------------------------------------------------------------
// API:
//   void factorize_u64(u64 n, std::vector<std::pair<u64,int>>& pf);
//     -> fills pf with (prime, exponent), ascending by prime; n=1 yields empty.
// Requires:
//   - miller_rabin_64(u64) from your MR snippet
//   - pollard_rho_64(u64)  from your Rho snippet
//   - mul_mod_u64(...)     (already used by MR/Rho)
// Notes:
//   - Strips a few small primes first, then uses MR to detect primes,
//     otherwise splits with Rho and recurses.
//   - Heuristic expected time ≈ Õ(n^{1/4}) on random composites.

static inline void _factor_core(u64 n, std::vector<u64>& fac){
  if (n == 1) return;
  if ((n & 1ull) == 0){ fac.push_back(2); _factor_core(n >> 1, fac); return; }
  static const u64 sp[] = {3,5,7,11,13,17,19,23,29,31,37,0};
  for (int i = 0; sp[i]; ++i){
    u64 p = sp[i];
    if (n % p == 0){ do{ fac.push_back(p); n /= p; }while(n % p == 0); if (n == 1) return; }
  }
  if (miller_rabin_64(n)){ fac.push_back(n); return; }
  u64 d = pollard_rho_64(n);
  _factor_core(d, fac); _factor_core(n / d, fac);
}

static inline void factorize_u64(u64 n, std::vector<std::pair<u64,int>>& pf){
  std::vector<u64> fac; fac.reserve(16);
  if (n >= 2) _factor_core(n, fac);
  std::sort(fac.begin(), fac.end());
  pf.clear(); pf.reserve(fac.size());
  for (size_t i = 0; i < fac.size(); ){
    size_t j = i; while (j < fac.size() && fac[j] == fac[i]) ++j;
    pf.push_back({fac[i], (int)(j - i)});
    i = j;
  }
}

