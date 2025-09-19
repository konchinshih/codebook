// crt_general — Chinese Remainder Theorem for non-coprime moduli (exCRT)
// ----------------------------------------------------------------------
// Solve x ≡ r1 (mod m1), x ≡ r2 (mod m2) with m1,m2 > 0 (not necessarily coprime).
// Returns (ok, r, M):  ok=false if no solution; otherwise x ≡ r (mod M), with M = lcm(m1,m2).
// Uses __int128 for intermediate products.
// Requires: extgcd(a,b,x,y)  // gives x*a + y*b = gcd(a,b)
// Time: O(log max(m1,m2)) per merge; merging k congruences is O(k log MOD).

#include <cstdint>
using u64 = unsigned long long;
using i64 = long long;
using u128 = __uint128_t;

static inline bool crt_general_pair(u64 r1, u64 m1, u64 r2, u64 m2, u64 &r, u64 &M){
  if (m1 == 0 || m2 == 0) return false;
  r1 %= m1; r2 %= m2;
  i64 x, y;
  i64 g = extgcd((i64)m1, (i64)m2, x, y);          // x*m1 + y*m2 = g
  u64 gg = (u64)(g >= 0 ? g : -g);
  if (((r2 + m2) - (r1 + m1)) % gg != 0) return false; // (r2 - r1) % g == 0 ?

  // Reduce to modulo m2' = m2/g, m1' = m1/g
  u64 m1_g = m1 / gg, m2_g = m2 / gg;
  // t ≡ ((r2 - r1)/g) * inv(m1/g mod m2/g) (mod m2/g)
  i64 delta = (i64)((r2 >= r1) ? (r2 - r1) : (r2 - r1 + m2)); // (r2 - r1) mod m2
  i64 k = delta / (i64)gg;                                    // exact division since divisible
  // x is inverse of m1 mod m2 up to factor g; so x is inverse of (m1/g) mod (m2/g)
  i64 inv = x % (i64)m2_g; if (inv < 0) inv += (i64)m2_g;
  u64 t = (u64)(( ( (__int128) (k % (i64)m2_g + (i64)m2_g) % (i64)m2_g ) * inv ) % m2_g);

  u128 lcm = (u128)m1 * m2_g;                      // lcm = m1 * (m2/g)
  u128 rr  = (u128)r1 + (u128)m1 * t;              // solution mod lcm
  r = (u64)(rr % lcm);
  M = (u64)lcm;                                    // beware: may overflow u64 if lcm >= 2^64
  return true;
}

// n-way merge: (r[i] mod m[i]) for i=0..k-1. All m[i] > 0. Returns (ok, r, M).
static inline bool crt_general(const std::vector<u64>& r_in,
                               const std::vector<u64>& m_in,
                               u64 &r, u64 &M){
  if (r_in.size() != m_in.size() || r_in.empty()) return false;
  r = r_in[0] % m_in[0]; M = m_in[0];
  for (size_t i = 1; i < r_in.size(); ++i){
    u64 nr, nM;
    if (!crt_general_pair(r, M, r_in[i] % m_in[i], m_in[i], nr, nM)) return false;
    r = nr; M = nM;
  }
  return true;
}

// (Optional) 128-bit modulus variant: safe if lcm exceeds 64-bit
static inline bool crt_general_u128(const std::vector<u64>& r_in,
                                    const std::vector<u64>& m_in,
                                    __uint128_t &r, __uint128_t &M){
  if (r_in.size() != m_in.size() || r_in.empty()) return false;
  r = r_in[0] % m_in[0]; M = m_in[0];
  for (size_t i = 1; i < r_in.size(); ++i){
    u64 r2 = r_in[i] % m_in[i], m2 = m_in[i];
    // merge (r mod M) with (r2 mod m2)
    i64 x,y; i64 g = extgcd((i64)(M % m2), (i64)m2, x, y);
    u64 gg = (u64)(g >= 0 ? g : -g);
    if ((u64)((r2 + m2) - (u64)(r % m2)) % gg != 0) return false;
    u64 m1_g = (u64)(M / gg), m2_g = m2 / gg;
    i64 k = (i64)(( (r2 >= (u64)(r % m2)) ? (r2 - (u64)(r % m2)) : (r2 - (u64)(r % m2) + m2) ) / gg);
    i64 inv = x % (i64)m2_g; if (inv < 0) inv += (i64)m2_g;
    u64 t = (u64)(( (__int128) ( (k % (i64)m2_g + (i64)m2_g) % (i64)m2_g ) * inv ) % m2_g);
    r = r + M * t;
    M = M * m2_g;                     // LCM grows
    r %= M;
  }
  return true;
}

