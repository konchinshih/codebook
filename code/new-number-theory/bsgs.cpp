// bsgs — discrete logarithm via Baby-Step Giant-Step
// ---------------------------------------------------
// Solve for the smallest x >= 0 such that a^x ≡ b (mod m), assuming gcd(a, m) = 1 and m > 1.
// Returns true and sets x if a solution exists; otherwise returns false.
// Time Complexity: O(√m) time and memory.
// Requires: norm_mod(a,m), pow_mod_ll(a,e,m), inv_mod_any(a,m,inv)

static inline bool bsgs(long long a, long long b, long long m, long long &x){
  if (m == 1){ x = 0; return (b % m) == 0; }
  a = norm_mod(a, m);
  b = norm_mod(b, m);
  if (b == 1 % m){ x = 0; return true; }
  // n = ceil(sqrt(m))
  long long n = (long long)std::sqrt((long double)m) + 1;

  // baby steps: table[a^j] = j, for j in [0..n-1]
  std::unordered_map<long long, int> table;
  table.reserve((size_t)(n * 1.3));
  table.max_load_factor(0.7f);

  long long aj = 1 % m;
  for (int j = 0; j < n; ++j){
    // store first occurrence only
    if (!table.count(aj)) table.emplace(aj, j);
    aj = (long long)((__int128)aj * a % m);
  }

  // factor = a^{-n} mod m
  long long an = pow_mod_ll(a, n, m);
  long long inv_an;
  if (!inv_mod_any(an, m, inv_an)) return false; // should not happen if gcd(a,m)=1

  // giant steps: cur = b * (a^{-n})^i
  long long cur = b;
  for (long long i = 0; i <= n; ++i){
    auto it = table.find(cur);
    if (it != table.end()){
      long long j = it->second;
      x = i * n + j;
      return true;
    }
    cur = (long long)((__int128)cur * inv_an % m);
  }
  return false;
}

