// euler_phi_single — φ(n) via prime factorization (64-bit)
// Requires: factorize_u64(u64 n, vector<pair<u64,int>>& pf)
// Assumes: n >= 1.  Expected time: ~ Õ(n^{1/4}) via Pollard–Rho on 64-bit.
static inline long long euler_phi_single(unsigned long long n){
  std::vector<std::pair<unsigned long long,int>> pf;
  factorize_u64(n, pf);
  unsigned long long r = n;
  for(auto &kv : pf){ unsigned long long p = kv.first; r = r / p * (p - 1); }
  return (long long)r;
}

