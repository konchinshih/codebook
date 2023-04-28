ll pw(ll a, ll b) {
    ll ret = 1;
    while (b > 0) {
        if (b & 1) {
            ret *= a;
            ret %= MOD;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return ret;
}
