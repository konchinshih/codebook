// floor_sum — S = sum_{i=0}^{n-1} floor((a*i + b) / m)
// Assumes: n >= 0, m > 0. Supports negative a,b (normalized).
// Returns __int128; wrapper returns ll.  Time: O(log max(|a|, m)).
// uses: using ll = long long;

static inline __int128 floor_sum_i128(ll n, ll m, ll a, ll b){
  __int128 ans = 0;
  if(a < 0){ ll a2=a%m; if(a2<0) a2+=m; ans += (__int128)(a-a2)/m * n*(n-1)/2; a=a2; }
  if(b < 0){ ll b2=b%m; if(b2<0) b2+=m; ans += (__int128)(b-b2)/m * n; b=b2; }
  while(true){
    if(a >= m){ ans += (__int128)(a/m) * (n-1) * n / 2; a %= m; }
    if(b >= m){ ans += (__int128)(b/m) * n; b %= m; }
    ll y = ((__int128)a * n + b) / m; if(y == 0) return ans;
    ll x = y * m - b;
    ll n2 = (a ? n - ( ( (__int128)x + a - 1 ) / a ) : 0);
    ans += (__int128)n2 * y;
    n = y; b = (a - ((x % a + a) % a)) % a;
    ll t = a; a = m; m = t;
  }
}
static inline ll floor_sum(ll n, ll m, ll a, ll b){
  return (ll)floor_sum_i128(n, m, a, b); // beware overflow in caller
}

