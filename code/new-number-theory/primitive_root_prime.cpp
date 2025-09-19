// primitive_root_prime — smallest primitive root modulo a prime p
// ---------------------------------------------------------------
// Requires: pow_mod_u64(a,e,mod), factorize_u64(n, pf)
// Returns: the least g in [1..p-1] with ord_p(g) = p-1 (i.e., generator of F_p*).
// Edge: p=2 -> 1.  Complexity: factoring p-1 (via Pollard–Rho) + O(π(p-1) * log p) checks.

static inline uint64_t primitive_root_prime(uint64_t p){
  if (p == 2) return 1;
  std::vector<std::pair<uint64_t,int>> pf; factorize_u64(p - 1, pf);
  std::vector<uint64_t> q; q.reserve(pf.size());
  for (auto &kv : pf) q.push_back(kv.first); // distinct prime factors of p-1
  for (uint64_t g = 2;; ++g){
    bool ok = true;
    for (uint64_t pr : q) if (pow_mod_u64(g, (p - 1) / pr, p) == 1){ ok = false; break; }
    if (ok) return g;
  }
}

