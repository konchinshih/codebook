int n, m, p[maxn], rk[maxn];
vector<pil> E; // u, v, w

bool cmp(pil a, pil b) {
    return a.S < b.S;
}

int main() {
    Optimize
    
    // n: |V|, m: |E|
    cin >> n >> m;
    while (m--) {
        int u, v; ll w;
        cin >> u >> v >> w;
        E.emplace_back(mp(mp(u, v), w));
    }
    for (int i = 0; i <= n; i++) {
        rk[i] = 1;
        p[i] = i;
    }

    ll ans = 0;
    sort(E.begin(), E.end(), cmp);
    for (auto& i : E) {
        if (find(i.F.F) != find(i.F.S)) {
            ans += i.S;
            Union(i.F.F, i.F.S);
        }
    }

    cout << ans << '\n';
    return 0;
}
