// ======= Fast NTT (u32) + 3-prime CRT helpers (C++17) ======================
#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t; using u64 = uint64_t; using u128 = __uint128_t; using ll = long long;

// --- pow mod (64-bit) ---
static inline u32 pow_mod_u32(u32 a, u64 e, u32 mod){
  u64 r = 1, x = a;
  while(e){ if(e&1) r = (r * x) % mod; x = (x * x) % mod; e >>= 1; }
  return (u32)r;
}

// --- FastNTT over friendly prime P with primitive root G (Cooley–Tukey, cached twiddles)
template<u32 P, u32 G>
struct FastNTT {
  // roots[len + j] stores stage twiddle for that level; rev cached per n
  static vector<u32> roots;   // roots[1] == 1, roots[2].. filled by ensure_base
  static vector<int>  rev;    // bitrev indices for last n
  static int last_n;

  static void ensure_base(int need){
    int have = (int)roots.size();
    if(have >= (1<<need)) return;
    if(have == 0){ roots.resize(2); roots[0]=0; roots[1]=1; have=2; }
    roots.resize(1<<need);
    while(have < (1<<need)){
      u32 z = pow_mod_u32(G, (P-1) / (have<<1), P); // primitive root for this stage
      for(int i=have/2;i<have;i++){
        roots[2*i]   = roots[i];
        roots[2*i+1] = (u32)((u64)roots[i] * z % P);
      }
      have <<= 1;
    }
  }
  static void bitrev_prepare(int n){
    if(last_n == n) return;
    rev.assign(n, 0);
    int lg = __builtin_ctz(n);
    for(int i=0;i<n;i++) rev[i] = (rev[i>>1]>>1) | ((i&1)<<(lg-1));
    last_n = n;
  }
  static void ntt(vector<u32>& a, bool invert){
    int n = (int)a.size();
    bitrev_prepare(n);
    for(int i=0;i<n;i++) if(i < rev[i]) swap(a[i], a[rev[i]]);
    for(int len=1, lvl=0; (len<<1) <= n; len <<= 1, ++lvl){
      ensure_base(lvl+1);
      const u32* w = &roots[len];
      for(int i=0;i<n;i += (len<<1)){
        for(int j=0;j<len; ++j){
          u32 u = a[i+j];
          u32 v = (u32)((u64)a[i+j+len] * w[j] % P);
          u32 x = u + v; if(x >= P) x -= P;
          u32 y = (u >= v) ? (u - v) : (u + P - v);
          a[i+j] = x; a[i+j+len] = y;
        }
      }
    }
    if(invert){
      if(n > 1) reverse(a.begin()+1, a.end());             // DIF inverse trick
      u32 inv_n = pow_mod_u32((u32)n, P-2, P);
      for(u32 &x : a) x = (u32)((u64)x * inv_n % P);
    }
  }
  static vector<u32> convolution(vector<u32> a, vector<u32> b){
    if(a.empty() || b.empty()) return {};
    size_t need = a.size() + b.size() - 1;
    if(min(a.size(), b.size()) < 32u){
      vector<u32> c(need);
      for(size_t i=0;i<a.size();++i) for(size_t j=0;j<b.size();++j){
        u64 t = (u64)c[i+j] + (u64)a[i]*b[j];
        c[i+j] = (u32)(t % P);
      }
      return c;
    }
    int n = 1; while((size_t)n < need) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for(int i=0;i<n;i++) a[i] = (u32)((u64)a[i] * b[i] % P);
    ntt(a, true);
    a.resize(need);
    return a;
  }
};
template<u32 P,u32 G> vector<u32> FastNTT<P,G>::roots = {0u,1u};
template<u32 P,u32 G> vector<int>  FastNTT<P,G>::rev;
template<u32 P,u32 G> int FastNTT<P,G>::last_n = 0;

// --- Three friendly primes for CRT (AtCoder/KACTL standard set)
static constexpr u32 M1 = 167772161u,  G1 = 3;   // 2^25 * 5 + 1
static constexpr u32 M2 = 469762049u,  G2 = 3;   // 2^26 * 7 + 1
static constexpr u32 M3 = 1224736769u, G3 = 3;   // 2^24 * 73 + 1
using NTT1 = FastNTT<M1,G1>;
using NTT2 = FastNTT<M2,G2>;
using NTT3 = FastNTT<M3,G3>;

// --- CRT merge (3 residues -> MOD)
static inline vector<long long> crt_merge_3(const vector<u32>& c1,
                                            const vector<u32>& c2,
                                            const vector<u32>& c3,
                                            long long MOD){
  size_t n = c1.size(); vector<long long> out(n);
  const u64 m1=M1, m2=M2, m3=M3, m1m2=m1*m2;
  const u64 inv_m1_mod_m2    = pow_mod_u32((u32)(m1 % m2), m2-2, m2);
  const u64 inv_m1m2_mod_m3  = pow_mod_u32((u32)(m1m2 % m3), m3-2, m3);
  const u64 MODu = (MOD>=0? (u64)MOD : (u64)(-MOD));
  for(size_t i=0;i<n;i++){
    u64 r1=c1[i], r2=c2[i], r3=c3[i];
    u64 t12 = ((r2 + m2 - (r1 % m2)) % m2) * inv_m1_mod_m2 % m2;
    u128 x12 = (u128)r1 + (u128)t12 * m1;           // mod m1*m2
    u64 r12m3 = (u64)(x12 % m3);
    u64 t123 = ((r3 + m3 - r12m3) % m3) * inv_m1m2_mod_m3 % m3;
    u128 x = x12 + (u128)t123 * m1m2;               // exact
    long long v = (long long)(x % (u128)MODu);
    if(v < 0) v += MOD;
    out[i] = v;
  }
  return out;
}

// ================= Public: three convolutions you asked for =================

// (1) Convolution mod 998244353 (small/normal n). Falls back to (3) if too big.
static inline vector<long long> convolution_mod_998244353(vector<long long> A,
                                                          vector<long long> B){
  if(A.empty() || B.empty()) return {};
  constexpr u32 P = 998244353u, G = 3;
  size_t need = A.size() + B.size() - 1;
  int n=1; while((size_t)n<need) n<<=1;
  if(n <= (1<<23)){
    vector<u32> a(A.size()), b(B.size());
    for(size_t i=0;i<A.size();++i){ long long x=A[i]%P; if(x<0)x+=P; a[i]=(u32)x; }
    for(size_t i=0;i<B.size();++i){ long long x=B[i]%P; if(x<0)x+=P; b[i]=(u32)x; }
    auto c = FastNTT<P,G>::convolution(a,b);
    vector<long long> C(c.size()); for(size_t i=0;i<c.size();++i) C[i]=c[i];
    return C;
  }
  // else large case -> (3)
  // (Reuse inputs to avoid extra copies)
  vector<long long> C = {}; C.swap(A); // no-op to appease compilers; falls through call:
  return /* (3) */ [&]{
    // use 3-prime CRT to 998244353
    vector<u32> a1, a2, a3, b1, b2, b3;
    a1.resize(A.size()); a2.resize(A.size()); a3.resize(A.size());
    b1.resize(B.size()); b2.resize(B.size()); b3.resize(B.size());
    for(size_t i=0;i<A.size();++i){
      long long x=A[i]; if(x<0) x%= (long long)M1, x+=M1;
      a1[i]=(u32)( (x%M1+M1)%M1 ); a2[i]=(u32)( (x%M2+M2)%M2 ); a3[i]=(u32)( (x%M3+M3)%M3 );
    }
    for(size_t i=0;i<B.size();++i){
      long long x=B[i];
      b1[i]=(u32)( (x%M1+M1)%M1 ); b2[i]=(u32)( (x%M2+M2)%M2 ); b3[i]=(u32)( (x%M3+M3)%M3 );
    }
    auto c1 = NTT1::convolution(a1,b1);
    auto c2 = NTT2::convolution(a2,b2);
    auto c3 = NTT3::convolution(a3,b3);
    return crt_merge_3(c1,c2,c3, (long long)P);
  }();
}

// (2) Convolution under MOD = 1e9+7 (using 3–prime CRT)
static inline vector<long long> convolution_mod_1e9p7(vector<long long> A,
                                                       vector<long long> B){
  if(A.empty() || B.empty()) return {};
  for(auto &x:A) if(x<0) x%=1000000007LL, x+=1000000007LL;
  for(auto &x:B) if(x<0) x%=1000000007LL, x+=1000000007LL;
  vector<u32> a1(A.size()),a2(A.size()),a3(A.size()),
              b1(B.size()),b2(B.size()),b3(B.size());
  for(size_t i=0;i<A.size();++i){
    a1[i]=(u32)(A[i]%M1); a2[i]=(u32)(A[i]%M2); a3[i]=(u32)(A[i]%M3);
  }
  for(size_t i=0;i<B.size();++i){
    b1[i]=(u32)(B[i]%M1); b2[i]=(u32)(B[i]%M2); b3[i]=(u32)(B[i]%M3);
  }
  auto c1 = NTT1::convolution(a1,b1);
  auto c2 = NTT2::convolution(a2,b2);
  auto c3 = NTT3::convolution(a3,b3);
  return crt_merge_3(c1,c2,c3, 1000000007LL);
}

// (3) Convolution mod 998244353 for BIG n via 3–prime CRT
static inline vector<long long> convolution_mod_998244353_big(vector<long long> A,
                                                               vector<long long> B){
  if(A.empty() || B.empty()) return {};
  vector<u32> a1(A.size()),a2(A.size()),a3(A.size()),
              b1(B.size()),b2(B.size()),b3(B.size());
  for(size_t i=0;i<A.size();++i){
    a1[i]=(u32)( (A[i]%M1 + M1)%M1 );
    a2[i]=(u32)( (A[i]%M2 + M2)%M2 );
    a3[i]=(u32)( (A[i]%M3 + M3)%M3 );
  }
  for(size_t i=0;i<B.size();++i){
    b1[i]=(u32)( (B[i]%M1 + M1)%M1 );
    b2[i]=(u32)( (B[i]%M2 + M2)%M2 );
    b3[i]=(u32)( (B[i]%M3 + M3)%M3 );
  }
  auto c1 = NTT1::convolution(a1,b1);
  auto c2 = NTT2::convolution(a2,b2);
  auto c3 = NTT3::convolution(a3,b3);
  return crt_merge_3(c1,c2,c3, 998244353LL);
}
