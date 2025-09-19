// tonelli_shanks — modular square root x^2 ≡ a (mod p), p an odd prime
// --------------------------------------------------------------------
// Returns true and sets x in [0, p-1] if a is a quadratic residue mod p;
// otherwise returns false.  The other root (if x != 0) is p - x.
// Complexity: O(log p) modular multiplications.
//
// Requires: pow_mod_ll(long long a, long long e, long long m)

using u64 = unsigned long long;
using u128 = __uint128_t;

static inline bool tonelli_shanks(u64 a, u64 p, u64 &x){
  a %= p;
  if (p == 2) { x = a; return true; }
  if (a == 0) { x = 0; return true; }

  // Euler criterion: a^{(p-1)/2} ≡ 1 (mod p) iff quadratic residue
  if (pow_mod_ll((long long)a, (long long)((p - 1) >> 1), (long long)p) != 1) return false;

  // Shortcut p ≡ 3 (mod 4): x = a^{(p+1)/4} mod p
  if ((p & 3ULL) == 3ULL) {
    x = (u64)pow_mod_ll((long long)a, (long long)((p + 1) >> 2), (long long)p);
    return true;
  }

  // Write p-1 = q * 2^s with q odd
  u64 q = p - 1, s = 0;
  while ((q & 1) == 0) { q >>= 1; ++s; }

  // Find a quadratic non-residue z
  u64 z = 2;
  while (pow_mod_ll((long long)z, (long long)((p - 1) >> 1), (long long)p) != p - 1) ++z;

  // Initialize
  u64 c = (u64)pow_mod_ll((long long)z, (long long)q, (long long)p);
  u64 t = (u64)pow_mod_ll((long long)a, (long long)q, (long long)p);
  u64 r = (u64)pow_mod_ll((long long)a, (long long)((q + 1) >> 1), (long long)p);
  u64 m = s;

  // Loop until t == 1
  while (t != 1) {
    // Find least i in [1..m-1] s.t. t^(2^i) == 1
    u64 t2i = t, i = 0;
    for (i = 1; i < m; ++i) {
      t2i = (u64)((u128)t2i * t2i % p);
      if (t2i == 1) break;
    }

    // b = c^{2^{m-i-1}}
    u64 e = m - i - 1;
    u64 b = 1;
    u64 c_pow = c;
    while (e--) c_pow = (u64)((u128)c_pow * c_pow % p); // c^{2^{m-i-1}}
    b = c_pow;

    // Update r, t, c, m
    r = (u64)((u128)r * b % p);
    u64 bb = (u64)((u128)b * b % p);
    t = (u64)((u128)t * bb % p);
    c = bb;
    m = i;
  }

  x = r;
  return true;
}

