// count how many times t occurs in s
string s, t;
int ns, nt;
const ll C = 26;
const ll MOD = 1e9 + 7;
ll Cexp[maxn], ht[maxn], hs;

void build_Cexp() {
    Cexp[0] = 1;
    FOR(i, 1, nt, 1) {
        Cexp[i] = Cexp[i-1] * C;
        if (Cexp[i] >= MOD) Cexp[i] %= MOD;
    }
}

void build_hash() {
    REP(i, ns) {
        hs += Cexp[ns-1-i] * (s[i] - 'a');
        if (hs >= MOD) hs %= MOD;
    }
    ht[0] = (t[0] - 'a');
    FOR(i, 1, nt, 1) {
        ht[i] = ht[i-1] * C + (t[i] - 'a');
        if (ht[i] >= MOD) ht[i] %= MOD;
    }
}

inline ll ht_query(int l, int r) {
    ll res = ht[r] - (l ? ht[l-1] * Cexp[len(l, r)] : 0);
    res = (res%MOD + MOD) % MOD;
    return res;
}
