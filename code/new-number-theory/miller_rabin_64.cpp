// Miller–Rabin Primality Test (deterministic for 64-bit)
// ------------------------------------------------------
// What it does: Quickly checks if a 64-bit integer n is prime.
// How: Write n-1 = d * 2^s (d odd). For fixed bases a, verify that
//   a^d ≡ 1 (mod n) or a^{d*2^r} ≡ -1 (mod n) for some 0 <= r < s.
// If any base fails, n is composite. With the bases below, the test is
// *deterministic* for all 0 <= n < 2^64.
// Complexity: O(k * log n) modular multiplications, where k = 7 bases
// (each base needs one binary-exponentiation with ~log n squarings/mults).
// Notes: Skip small primes first; use 128-bit mul to avoid overflow.

using u64 = uint64_t; using i64 = int64_t; using u128 = __uint128_t;

static inline u64 mul_mod_u64(u64 a, u64 b, u64 mod){ return (u64)((u128)a * b % mod); }

static inline u64 pow_mod_u64(u64 a, u64 e, u64 mod){
  u64 r = 1 % mod, x = a % mod;
  while(e){ if(e&1) r = mul_mod_u64(r, x, mod); x = mul_mod_u64(x, x, mod); e >>= 1; }
  return r;
}

// Deterministic bases for 64-bit: {2, 325, 9375, 28178, 450775, 9780504, 1795265022}
static inline bool miller_rabin_64(u64 n){
  if(n < 2) return false;
  static const u64 small[] = {2,3,5,7,11,13,17,19,23,0};
  for(int i=0; small[i]; ++i){ if(n % small[i] == 0) return n == small[i]; }
  u64 d = n - 1, s = 0; while((d & 1) == 0){ d >>= 1; ++s; }
  auto check = [&](u64 a)->bool{
    if(a % n == 0) return true;
    u64 x = pow_mod_u64(a, d, n);
    if(x == 1 || x == n-1) return true;
    for(u64 r=1; r<s; ++r){ x = mul_mod_u64(x, x, n); if(x == n-1) return true; }
    return false;
  };
  static const u64 A[] = {2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL};
  for(u64 a : A) if(!check(a)) return false;
  return true;
}

