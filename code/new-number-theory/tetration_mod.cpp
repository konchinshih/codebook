// tetration_mod — compute A↑↑B mod M (handles composite M via prime-power + CRT)
// Complexity: O(#prime factors * log M) per prime power + factorization.
// Requires from your codebook: factorize_u64(u64 n, vector<pair<u64,int>>& pf)
// Uses local: pow_mod_ll (128-bit safe), simple CRT merge for coprime prime powers.

using ll = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

// ---------- forward decls ----------
static inline ll tetration_mod(ll A, ll B, ll M);            // used inside prime-power case
extern void factorize_u64(u64 n, vector<pair<u64,int>>& pf); // bring your MR+Rho here

// ---------- utils ----------
static inline ll norm_mod_ll(ll a, ll m){ a%=m; if(a<0) a+=m; return a; }
static inline ll pow_mod_ll(ll a, long long e, ll m){
  i128 base = norm_mod_ll(a, m), res = 1;
  while(e>0){ if(e&1) res = (res*base)%m; base = (base*base)%m; e >>= 1; }
  return (ll)res;
}
static inline ll phi_prime_power(ll p, int k){ // φ(p^k) = (p-1)*p^{k-1}
  ll pk1 = 1; for(int i=1;i<k;i++) pk1 = (ll)((i128)pk1 * p);
  return (ll)((i128)pk1 * (p - 1));
}
static inline ll ipow_ll(ll a, ll e){ // integer power (clamped)
  i128 r=1, x=a;
  while(e>0){ if(e&1){ r*=x; if(r>(i128)LLONG_MAX) return LLONG_MAX; }
              x*=x; if(x>(i128)LLONG_MAX) x=LLONG_MAX; e>>=1; }
  return (ll)r;
}
static inline ll ceil_log_ge(ll a, ll T){ // min s>=0 : a^s >= T
  if(T<=1) return 0;
  if(a<=1) return (a==1? LLONG_MAX : 1);
  ll s=0; i128 cur=1;
  while(cur < T){ ++s; cur*=a; if(s>62) break; }
  return s;
}
static bool tower_ge(ll A, ll b, ll T){ // is A↑↑b >= T ?
  if(T<=1) return true;
  if(b<=0) return 1 >= T;
  if(b==1) return A >= T;
  if(A==0) return 0 >= T;      // for b>=2, 0^exp = 0
  if(A==1) return 1 >= T;
  ll need = ceil_log_ge(A, T);
  if(need==LLONG_MAX) return false;
  return tower_ge(A, b-1, need);
}
static ll tower_bounded_value(ll A, ll b, ll CAP){ // returns min(A↑↑b, CAP+1)
  if(b<=0) return 1;
  if(b==1) return (A <= CAP ? A : CAP+1);
  if(CAP<=1){
    if(A<=1) return (A<=CAP ? A : CAP+1);
    return CAP+1;
  }
  if(A<=1) return (A==0?0:1);
  ll need = ceil_log_ge(A, (CAP+1));
  ll exp = tower_bounded_value(A, b-1, need-1);
  if(exp >= need) return CAP+1;
  ll val = ipow_ll(A, exp);
  return (val <= CAP ? val : CAP+1);
}

// ---------- CRT for coprime moduli ----------
static inline long long exgcd_ll(long long a,long long b,long long& x,long long& y){
  if(b==0){ x=(a>=0?1:-1); y=0; return a>=0?a:-a; }
  long long x1,y1; long long g=exgcd_ll(b,a%b,x1,y1); x=y1; y=x1-(a/b)*y1; return g;
}
static inline bool crt_pair(ll r1, ll m1, ll r2, ll m2, ll &r, ll &m){
  long long x,y; long long g = exgcd_ll(m1, m2, x, y);
  if(g != 1 && g != -1) return false; // prime powers of distinct primes are coprime
  i128 t = r2 - r1; t = (t % m2 + m2) % m2;
  i128 k = ((i128)x % m2 + m2) % m2;
  t = (t * k) % m2;
  i128 mod = (i128)m1 * m2;
  i128 res = (i128)r1 + t * m1;
  res %= mod; if(res<0) res += mod;
  r = (ll)res; m = (ll)mod; return true;
}

// ---------- per prime-power ----------
static ll tetration_mod_prime_power(ll A, ll B, ll p, int k){
  ll pk = 1; for(int i=0;i<k;i++) pk = (ll)((i128)pk * p);
  if(B<=0) return 1 % pk;
  if(B==1) return norm_mod_ll(A, pk);
  if(pk==1) return 0;

  ll a = norm_mod_ll(A, pk);
  if(a==0){
    // FIX: handle 0^0 = 1 when the exponent E = A↑↑(B-1) equals 0.
    // For A=0: E = 0↑↑(B-1) = (B-1 is odd ? 0 : 1).
    if (A == 0 && ((B - 1) & 1)) return 1 % pk; // E==0  → 0^0 = 1
    return 0;                                    // otherwise 0^E = 0 (E>=1)
  }
  // v_p(A)
  int s=0; ll tmp=a;
  while(tmp % p == 0){ tmp/=p; ++s; if(s>=k) break; }
  ll A1 = tmp % pk;

  if(s>0){
    ll need = (k + s - 1) / s;
    if(tower_ge(A, B-1, need)) return 0;
    ll e = tower_bounded_value(A, B-1, need-1); // small exact exponent
    ll p_pow = 1; for(int i=0;i<s*e;i++) p_pow = (ll)((i128)p_pow * p);
    ll mod2 = 1; for(int i=0;i<k - s*e;i++) mod2 = (ll)((i128)mod2 * p);
    ll part = pow_mod_ll(A1 % mod2, e, mod2);
    return (ll)(( (i128)part * p_pow ) % pk);
  }
  // coprime: use Euler reduction; exponent ≡ (A↑↑(B-1) mod φ) + φ
  ll ph = phi_prime_power(p, k);
  ll r = tetration_mod(A, B-1, ph);    // only need exponent mod φ(p^k)
  return pow_mod_ll(a, r + ph, pk);
}

// ---------- main wrapper ----------
static inline ll tetration_mod(ll A, ll B, ll M){
  if(M==1) return 0;
  if(B<=0) return 1 % M;
  if(B==1) return norm_mod_ll(A, M);

  vector<pair<u64,int>> pf; factorize_u64((u64)M, pf);

  ll R = 0, MOD = 1;
  for(auto [pp, kk] : pf){
    ll pk = 1; for(int i=0;i<kk;i++) pk = (ll)((i128)pk * (ll)pp);
    ll ri = tetration_mod_prime_power(A, B, (ll)pp, kk);
    ll r2, m2;
    bool ok = crt_pair(R, MOD, ri % pk, pk, r2, m2);
    if(!ok) return 0; // shouldn't happen for prime-power CRT
    R = r2; MOD = m2;
  }
  R %= M; if(R<0) R += M;
  return R;
}
