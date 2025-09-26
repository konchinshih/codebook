// Author: Unknown, Modified by Gino
// Function: Check if a number is a prime in O(100 * log^2(n))
//      miller_rabin(): return 1 if prime, 0 otherwise
inline ll mul(ll x, ll y, ll mod) {
    return (__int128)(x) * y % mod;
}
ll mypow(ll a, ll b, ll mod) {
    ll r = 1;
    while (b > 0) {
        if (b & 1) r = mul(r, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return r;
}
bool witness(ll a, ll n, ll u, int t){
	ll x = mypow(a, u, n);
	for(int i = 0; i < t; i++) {
		ll nx = mul(x, x, n);
		if (nx == 1 && x != 1 && x != n-1) return true;
		x = nx;
	}
	return x != 1;
}
bool miller_rabin(ll n) {
    // if n >= 3,474,749,660,383
    // change {2, 3, 5, 7, 11, 13} to
    // {2, 325, 9375, 28178, 450775, 9780504, 1795265022}
	if (n < 2) return false;
	if(!(n & 1)) return n == 2;
	ll u = n - 1; int t = 0;
	while(!(u & 1)) u >>= 1, t++;
    for (ll a : {2, 3, 5, 7, 11, 13}) {
        if (a % n == 0) continue;
        if (witness(a, n, u, t)) return false;
    }
	return true;
}
// bases that make sure no pseudoprimes flee from test
// if WA, replace randll(n - 1) with these bases:
// n < 4,759,123,141        3 :  2, 7, 61
// n < 1,122,004,669,633    4 :  2, 13, 23, 1662803
// n < 3,474,749,660,383          6 :  pirmes <= 13
// n < 2^64                       7 :
// 2, 325, 9375, 28178, 450775, 9780504, 1795265022
