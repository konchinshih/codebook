// For Building Suffix Array and LCP Array
int n;
string s;
vector<int> suf, lcp, rk;

// For Radix Sort
vector<int> cnt, pos;
vector<pair<pii, int> > buc[2];  // 0: result, 1: temp


void init() {
    n = (int)s.size();
    suf.resize(n);
    rk.resize(n);
    cnt.resize(n);
    pos.resize(n);
    Each(i, buc) i.resize(n);
}

void radix_sort() {
    REP(t, 2) {
        fill(iter(cnt), 0);
        Each(i, buc[t]) cnt[ (t ? i.F.F : i.F.S) ]++;
        REP(i, n) {
            pos[i] = (!i ? 0 : pos[i-1] + cnt[i-1]);
        }
        Each(i, buc[t]) {
            buc[t^1][pos[ (t ? i.F.F : i.F.S) ]++] = i;
        }
    }
}

bool fill_suf() {
    bool end = true;
    REP(i, n) suf[i] = buc[0][i].S;
    rk[suf[0]] = 0;
    FOR(i, 1, n, 1) {
        int dif = (buc[0][i].F != buc[0][i-1].F);
        end &= dif;
        rk[suf[i]] = rk[suf[i-1]] + dif;
    }
    return end;
}

void sa() {
    s += (char)30;
    init();

    REP(i, n) buc[0][i] = mp(mp(s[i], s[i]), i);
    sort(iter(buc[0]));
    if (fill_suf()) return;

    for (int k = 0; (1<<k) < n; k++) {
        REP(i, n) {
            buc[0][i] = mp(mp(rk[i], rk[(i + (1<<k)) % n]), i);
        }
        radix_sort();
        if (fill_suf()) return;
    }
}

// lcp[i] = lcp(rank_i, rank_(i-1))
// lcp[0] = 0
void LCP() {
    int k = 0;
    REP(i, n-1) {
        int pi = rk[i];
        int j = suf[pi-1];
        while (s[i+k] == s[j+k]) k++;
        lcp[pi] = k;
        k = max(k-1, 0);
    }
}

int main() {
    elpsycongroo

    cin >> s;

    sa();

    REP(i, n) cout << suf[i] << ' ';
    cout << '\n';
    REP(i, n) cout << lcp[i] << ' ';
    cout << '\n';

    return 0;
}