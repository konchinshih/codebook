int n;
ll mod;
vector<ll> inv;
vector<vector<ll> > v;
void build() {
	inv.clear(); inv.resize(mod, 0);
	inv[1] = 1;
	FOR(i, 2, mod, 1) {
		inv[i] = (mod-mod/i)*inv[mod%i]%mod;
	}
}
void init() {
	cin >> n >> mod;
	build();
	v.resize(n, vector<ll>(n+1, 0LL));
	REP(i, n) cin >> v[i][n];
	REP(i, n) REP(j, n) cin >> v[j][i];
}
void gauss(vector<vector<ll>>& v) {
	int r = 0;
	REP(i, n) {
		bool ok = false;
		FOR(j, r, n, 1) {
			if (v[j][i] == 0) continue;
			swap(v[j], v[r]);
			ok = true;
			break;
		}
		if (!ok) continue;
		ll div = inv[v[r][i]];
		REP(j, n+1) {
			v[r][j] *= div;
			if (v[r][j] >= mod) v[r][j] %= mod;
		}
		REP(j, n) {
			if (j == r) continue;
			ll t = v[j][i];
			REP(k, n+1) {
				v[j][k] -= v[r][k] * t % mod;
				if (v[j][k] < 0) v[j][k] += mod;
			}
		}
		r++;
	}
}
void solve() {
	gauss(v);
	REP(i, n) {
		cout << v[i][n] << ' ';
	}
	cout << endl;
}