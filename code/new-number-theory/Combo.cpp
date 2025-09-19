// Combo toolkit
// --------------------------------------------------------------
// Includes:
//   - factorial_invfac_table (prime MOD)
//   - nCk_mod_prime  (O(1) after O(N) table) + Lucas version
//   - nCk_mod_any    (factor M => ∏ p^e, compute mod p^e, CRT merge)
//   - stirling2_table (S2 up to N)
//   - derangement_number_mod (O(n) Montmort)
// Requires (from your codebook):
//   - extgcd(a,b,x,y)               // from your gcd/extgcd snippet
//   - factorize_u64(M, pf)          // from MR+Rho factorization snippet
//   - crt_general(...)              // from exCRT snippet

#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
using i64 = long long;
using u128 = __uint128_t;

// ---------- factorial_invfac_table (prime MOD) ----------
static inline void factorial_invfac_table(int N, int MOD, vector<int>& fact, vector<int>& ifact){
  fact.resize(N+1); ifact.resize(N+1);
  fact[0]=1; for(int i=1;i<=N;i++) fact[i]=(int)((1LL*fact[i-1]*i)%MOD);
  auto modpow = [&](long long a,long long e){ long long r=1%MOD; a%=MOD; while(e){ if(e&1) r=r*a%MOD; a=a*a%MOD; e>>=1; } return (int)r; };
  ifact[N]=modpow(fact[N], MOD-2);
  for(int i=N;i>0;i--) ifact[i-1]=(int)(1LL*ifact[i]*i%MOD);
}

// O(1) after table; assumes 0<=k<=n and MOD prime
static inline int nCk_mod_prime_table(int n,int k,int MOD,const vector<int>& fact,const vector<int>& ifact){
  if(k<0||k>n) return 0;
  return (int)(1LL*fact[n]*ifact[k]%MOD*ifact[n-k]%MOD);
}

// ---------- Lucas’s theorem (prime p), no large pretable needed ----------
static inline int nCk_mod_prime_lucas(long long n, long long k, int p){
  if(k<0||k>n) return 0;
  // per-digit factorial up to p-1
  static vector<int> F, IF; static int lastp=-1;
  auto modpow = [&](long long a,long long e){ long long r=1%p; a%=p; while(e){ if(e&1) r=r*a%p; a=a*a%p; e>>=1; } return (int)r; };
  auto comb_small = [&](int nn,int kk)->int{
    if(kk<0||kk>nn) return 0;
    if(lastp!=p){ F.assign(p,1); for(int i=1;i<p;i++) F[i]=(int)(1LL*F[i-1]*i%p);
                  IF.assign(p,1); IF[p-1]=modpow(F[p-1], p-2); for(int i=p-1;i>=1;i--) IF[i-1]=(int)(1LL*IF[i]*i%p);
                  lastp=p;
    }
    return (int)(1LL*F[nn]*IF[kk]%p*IF[nn-kk]%p);
  };
  int res=1;
  while(n>0||k>0){
    int ni=(int)(n%p), ki=(int)(k%p);
    res = (int)(1LL*res*comb_small(ni,ki)%p);
    if(!res) return 0;
    n/=p; k/=p;
  }
  return res;
}

// ---------- derangement D_n mod MOD (Montmort) ----------
static inline int derangement_number_mod(int n, int MOD){
  if(n==0) return 1%MOD;
  if(n==1) return 0;
  long long Dm2=1, Dm1=0;
  for(int i=2;i<=n;i++){
    long long Di = 1LL*(i-1)*((Dm1+Dm2)%MOD)%MOD;
    Dm2=Dm1; Dm1=Di;
  }
  return (int)Dm1;
}

// ---------- Stirling numbers of the 2nd kind S2(n,k) table up to N ----------
static inline void stirling2_table(int N, int MOD, vector<vector<int>>& S){
  S.assign(N+1, vector<int>(N+1,0));
  S[0][0]=1;
  for(int n=1;n<=N;n++){
    for(int k=1;k<=n;k++){
      S[n][k] = ( (S[n-1][k-1] + (int)(1LL*k*S[n-1][k]%MOD)) % MOD );
    }
  }
}

// (optional) Bell number from S2 row: B_n = sum_{k=0..n} S2(n,k) mod MOD
static inline int bell_from_s2_row(const vector<int>& row, int MOD){
  long long s=0; for(int x:row) s+=x; return (int)(s%MOD);
}

// ---------- nCk mod any positive M via prime-power + CRT ----------
static inline i64 exgcd(i64 a,i64 b,i64& x,i64& y){ if(b==0){ x=(a>=0?1:-1); y=0; return a>=0?a:-a; } i64 x1,y1; i64 g=exgcd(b,a%b,x1,y1); x=y1; y=x1-(a/b)*y1; return g; }
static inline i64 mod_inv_coprime(i64 a, i64 mod){ i64 x,y; i64 g=exgcd(a,mod,x,y); (void)g; x%=mod; if(x<0) x+=mod; return x; }

// count v_p(n!)
static inline u64 vp_fact(u64 n, u64 p){ u64 v=0; while(n){ n/=p; v+=n; } return v; }

// unit product per full block (product of units mod p^e) — known values
static inline u64 unit_block_prod(u64 p, int e){
  if(p==2 && e>=3) return 1ULL;
  return (u64)((p==2 && e==1) ? 1 : (u64)(-1)); // for 2^1 => 1; for odd p^e => -1 (≡ p^e−1)
}

// factorial modulo p^e, removing p-factors
// returns product_{i=1..n, p∤i} i  (mod pe)
static inline u64 factmod_pe_without_p(u64 n, u64 p, int e, u64 pe){
  if(n==0) return 1%pe;
  u64 res = 1%pe;
  u64 block = unit_block_prod(p,e); if((long long)block==-1) block = pe-1;
  while(n){
    u64 full = n/pe, rem = n%pe;
    if(full) res = (u64)((u128)res * (u128) ( (u128) (block) % pe ) % pe); // block^(n/pe) each loop? (approx)
    // Multiply 1..rem excluding multiples of p
    for(u64 i=1;i<=rem;i++) if(i%p) res = (u64)((u128)res * i % pe);
    n/=p;
  }
  return res%pe;
}

// C(n,k) mod p^e
static inline u64 nCk_mod_primepower(u64 n,u64 k,u64 p,int e){
  if(k>n) return 0;
  u64 pe=1; for(int i=0;i<e;i++) pe*=p;
  u64 v = vp_fact(n,p) - vp_fact(k,p) - vp_fact(n-k,p);
  if(v >= (u64)e) return 0;
  // numerator/denominator without p
  u64 A = factmod_pe_without_p(n, p, e, pe);
  u64 B = factmod_pe_without_p(k, p, e, pe);
  u64 C = factmod_pe_without_p(n-k, p, e, pe);
  u64 denom = (u64)((u128)B * C % pe);
  u64 inv = mod_inv_coprime((i64)denom, (i64)pe);
  u64 res = (u64)((u128)A * inv % pe);
  // multiply p^v
  for(u64 i=0;i<v;i++) res = (u64)((u128)res * p % pe);
  return res;
}

// nCk mod any M>0 via factorization + CRT (general CRT from your snippet)
static inline u64 nCk_mod_any(u64 n, u64 k, u64 M){
  if(M==1) return 0;
  if(k>n) return 0;
  // factorize M
  vector<pair<u64,int>> pf; factorize_u64(M, pf);
  // residues per prime power
  vector<u64> r, m;
  r.reserve(pf.size()); m.reserve(pf.size());
  for(auto &kv: pf){
    u64 p=kv.first; int e=kv.second;
    u64 pe=1; for(int i=0;i<e;i++) pe*=p;
    r.push_back( nCk_mod_primepower(n,k,p,e) );
    m.push_back( pe );
  }
  // exCRT merge
  u64 R=0, MOD=1;
  for(size_t i=0;i<r.size();++i){
    u64 nr, nM;
    if(!crt_general_pair(R, MOD, r[i]%m[i], m[i], nr, nM)) return 0; // inconsistent should not happen
    R=nr; MOD=nM;
  }
  return R % M;
}

// ---------- nCk_mod_prime (table-based) convenience wrapper ----------
struct CombPrime {
  int P; vector<int> fact, ifact;
  CombPrime(int P_=998244353,int N=1<<20):P(P_){ factorial_invfac_table(N,P,fact,ifact); }
  int C(long long n,long long k){
    if(n<0||k<0||k>n) return 0;
    if(n<(int)fact.size()-1) return nCk_mod_prime_table((int)n,(int)k,P,fact,ifact);
    // fallback to Lucas when n beyond table
    return nCk_mod_prime_lucas(n,k,P);
  }
};

