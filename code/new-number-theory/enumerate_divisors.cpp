// enumerate_divisors — all positive divisors of n (ascending)
// Requires: factorize_u64(u64 n, vector<pair<u64,int>>& pf)

static inline void enumerate_divisors_from_pf(
  const std::vector<std::pair<uint64_t,int>>& pf,
  std::vector<uint64_t>& divs
){
  divs.assign(1, 1);
  for (auto [p, e] : pf) {
    size_t m = divs.size();
    uint64_t pe = 1;
    for (int k = 1; k <= e; ++k) {
      pe *= p;
      for (size_t i = 0; i < m; ++i) divs.push_back(divs[i] * pe);
    }
  }
  std::sort(divs.begin(), divs.end());
}

static inline void enumerate_divisors(uint64_t n, std::vector<uint64_t>& divs){
  if (n == 0) { divs.clear(); return; }        // convention: no divisors for 0
  if (n == 1) { divs.assign(1, 1); return; }
  std::vector<std::pair<uint64_t,int>> pf;
  factorize_u64(n, pf);
  enumerate_divisors_from_pf(pf, divs);
}

