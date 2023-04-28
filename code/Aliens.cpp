int n; ll k;
vector<ll> a;
vector<pll> dp[2];
void init() {
	cin >> n >> k;
	Each(i, dp) i.clear(), i.resize(n);
	a.clear(); a.resize(n);
	Each(i, a) cin >> i;
}
pll calc(ll p) {
	dp[0][0] = mp(0, 0);
	dp[1][0] = mp(-a[0], 0);
	FOR(i, 1, n, 1) {
		if (dp[0][i-1].F > dp[1][i-1].F + a[i] - p) {
			dp[0][i] = dp[0][i-1];
		} else if (dp[0][i-1].F < dp[1][i-1].F + a[i] - p) {
			dp[0][i] = mp(dp[1][i-1].F + a[i] - p, dp[1][i-1].S+1);
		} else {
			dp[0][i] = mp(dp[0][i-1].F, min(dp[0][i-1].S, dp[1][i-1].S+1));
		}
		if (dp[0][i-1].F - a[i] > dp[1][i-1].F) {
			dp[1][i] = mp(dp[0][i-1].F - a[i], dp[0][i-1].S);
		} else if (dp[0][i-1].F - a[i] < dp[1][i-1].F) {
			dp[1][i] = dp[1][i-1];
		} else {
			dp[1][i] = mp(dp[1][i-1].F, min(dp[0][i-1].S, dp[1][i-1].S));
		}
	}
	return dp[0][n-1];
}
void solve() {
	ll l = 0, r = 1e7;
	pll res = calc(0);
	if (res.S <= k) return cout << res.F << endl, void();
	while (l < r) {
		ll mid = (l+r)>>1;
		res = calc(mid);
		if (res.S <= k) r = mid;
		else l = mid+1;
	}
	res = calc(l);
	cout << res.F + k*l << endl;
}