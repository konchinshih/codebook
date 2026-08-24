// Author: Gino
// Function: TODO
int n; ll k;
vector<ll> a;
vector<pll> dp[2];
void init() {
	cin >> n >> k;
	for (auto& d : dp) d.clear(), d.resize(n);
	a.clear(); a.resize(n);
	for (auto& i : a) cin >> i;
}
pll calc(ll p) {
	dp[0][0] = make_pair(0, 0);
	dp[1][0] = make_pair(-a[0], 0);
    for (int i = 1; i < n; i++) {
		if (dp[0][i-1].first > dp[1][i-1].first + a[i] - p) {
			dp[0][i] = dp[0][i-1];
		} else if (dp[0][i-1].first < dp[1][i-1].first + a[i] - p) {
			dp[0][i] = make_pair(dp[1][i-1].first + a[i] - p, dp[1][i-1].second+1);
		} else {
			dp[0][i] = make_pair(dp[0][i-1].first, min(dp[0][i-1].second, dp[1][i-1].second+1));
		}
		if (dp[0][i-1].first - a[i] > dp[1][i-1].first) {
			dp[1][i] = make_pair(dp[0][i-1].first - a[i], dp[0][i-1].second);
		} else if (dp[0][i-1].first - a[i] < dp[1][i-1].first) {
			dp[1][i] = dp[1][i-1];
		} else {
			dp[1][i] = make_pair(dp[1][i-1].first, min(dp[0][i-1].second, dp[1][i-1].second));
		}
	}
	return dp[0][n-1];
}
void solve() {
	ll l = 0, r = 1e7;
	pll res = calc(0);
	if (res.second <= k) return cout << res.first << endl, void();
	while (l < r) {
		ll mid = (l+r)>>1;
		res = calc(mid);
		if (res.second <= k) r = mid;
		else l = mid+1;
	}
	res = calc(l);
	cout << res.first + k*l << endl;
}
