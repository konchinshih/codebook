vector<int> lpf;
vector<int> prime;
 
void seive() {
    lpf.resize(maxn, 1);
    for (int i = 2; i < maxn; i++) {
        if (lpf[i] == 1) {
            lpf[i] = i;
            prime.eb(i);
        }
        Each(j, prime) {
            if (i*j >= maxn) break;
            lpf[i*j] = j;
            if (j == lpf[i]) break;
        }
    }
}
 
vector<pii> fac;
void defactor(int u) {
    fac.clear();
    while (u > 1) {
        int d = lpf[u];
        fac.eb(mp(d, 0));
        while (u % d == 0) {
            u /= d;
            fac[(int)fac.size()-1].S++;
        }
    }
}
