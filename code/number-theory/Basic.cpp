const int maxc = 5e5;
ll pw(ll a, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}

vector<ll> fac, ifac;
void build_fac() {
    reset(fac, maxc + 1, 1LL);
    reset(ifac, maxc + 1, 1LL);
    for (int x = 2; x <= maxc; x++) {
        fac[x] = x * fac[x - 1] % MOD;
        ifac[x] = pw(fac[x], MOD - 2);
    }
}

ll C(ll n, ll k) {
    if (n < k) return 0LL;
    return fac[n] * ifac[n - k] % MOD * ifac[k] % MOD;
}
