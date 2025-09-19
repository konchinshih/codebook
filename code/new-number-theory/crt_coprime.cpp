// crt_coprime — Chinese Remainder Theorem for pairwise-coprime moduli
// --------------------------------------------------------------------
// Pair merge: x ≡ r1 (mod m1), x ≡ r2 (mod m2), with gcd(m1,m2)=1, m1,m2>0.
// Returns (r, M) where M=m1*m2 and r in [0, M-1]. Uses __int128 internally.
//
// Requires: extgcd(a,b,x,y)

using u64 = unsigned long long;
using u128 = __uint128_t;

static inline std::pair<u64,u64> crt_coprime(u64 r1, u64 m1, u64 r2, u64 m2){
  long long x, y;                     // x*m1 + y*m2 = 1
  extgcd((long long)m1, (long long)m2, x, y);
  u64 inv_m1_mod_m2 = (u64)((x % (long long)m2 + (long long)m2) % (long long)m2);

  r1 %= m1; r2 %= m2;
  u64 delta = (r2 >= r1) ? (r2 - r1) : (r2 - r1 + m2);   // (r2 - r1) mod m2
  u64 t = (u64)((u128)delta * inv_m1_mod_m2 % m2);       // t s.t. m1*t ≡ r2-r1 (mod m2)

  u128 M = (u128)m1 * m2;
  u128 r = (u128)r1 + (u128)m1 * t;                      // in [0, M-1]
  if (r >= M) r %= M;
  return {(u64)r, (u64)M}; // NOTE: M may overflow u64 if m1*m2 > 2^64-1
}

// n-way merge for pairwise-coprime moduli
// --------------------------------------
// Assumes all m[i] > 0 and pairwise coprime. M grows as product of m[i].
// Returns (r, M) with x ≡ r (mod M).  Uses sequential pair merges.
static inline std::pair<u64,u64> crt_coprime(const std::vector<u64>& r, const std::vector<u64>& m){
  u64 R = 0, M = 1;
  for (size_t i = 0; i < r.size(); ++i){
    auto nm = crt_coprime(R, M, r[i] % m[i], m[i]);
    R = nm.first; M = nm.second;
  }
  return {R, M};
}

// Optional: 128-bit modulus variant (safer if product exceeds 64-bit)
// -------------------------------------------------------------------
static inline std::pair<u128,u128> crt_coprime_u128(const std::vector<u64>& r, const std::vector<u64>& m){
  u128 R = 0, M = 1;
  for (size_t i = 0; i < r.size(); ++i){
    // merge (R mod M) with (ri mod mi)
    long long x, y; extgcd((long long)(M % m[i]), (long long)m[i], x, y);
    u64 inv = (u64)((x % (long long)m[i] + (long long)m[i]) % (long long)m[i]);
    u64 ri = r[i] % m[i];
    u64 delta = (ri >= (u64)(R % m[i])) ? (ri - (u64)(R % m[i])) : (ri - (u64)(R % m[i]) + m[i]);
    u64 t = (u64)((u128)delta * inv % m[i]);
    R = R + M * t;
    M = M * m[i];
    if (R >= M) R %= M;
  }
  return {R, M};
}

