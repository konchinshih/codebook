// min_of_linear_mod — minimize (a*x + b) mod m for x in [0, n)
// O(log max(|a|, m)). Handles negative a,b; uses __int128 for safety.
// uses: using ll = long long;

static inline ll _norm_mod(ll a, ll m){ a%=m; if(a<0) a+=m; return a; }
static inline ll _ceil_div(ll p, ll q){ if(q<0) p=-p, q=-q; if(p>=0) return (p+q-1)/q; return p/q; }

static inline ll min_of_linear_mod(ll n, ll m, ll a, ll b){
  if(n<=0) return 0; m = llabs(m); if(m==0) return 0;
  a = _norm_mod(a,m); b = _norm_mod(b,m); if(a==0) return b;
  ll best = b;
  while(true){
    if(a>=m) a%=m;
    if(b>=m){ best = min(best, b%m); b%=m; }
    ll y = (ll)((__int128)a*(n-1)+b)/m; if(y==0) return best;
    ll xq = _ceil_div((ll)((__int128)m*y - b), a);
    if(xq<0) xq=0; if(xq>=n) xq=n-1;
    ll cand = (ll)((__int128)a*xq + b - (__int128)m*y) % m; if(cand<0) cand+=m;
    if(cand<best) best=cand; if(best==0) return 0;
    ll b2 = (ll)((a - (((__int128)m*y - b) % a + a) % a) % a);
    n = y; ll t=a; a=m; m=t; b=b2;
  }
}

