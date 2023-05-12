int n, m;
string s, p;
vector<int> f;
void build() {
	f.clear(); f.resize(m, 0);
	int ptr = 0; for (int i = 1; i < m; i++) {
		while (ptr && p[i] != p[ptr]) ptr = f[ptr-1];
		if (p[i] == p[ptr]) ptr++;
		f[i] = ptr;
}}
void init() {
	cin >> s >> p;
	n = (int)s.size();
	m = (int)p.size();
	build(); }
void solve() {
	int ans = 0, pi = 0;
	for (int si = 0; si < n; si++) {
		while (pi && s[si] != p[pi]) pi = f[pi-1];
		if (s[si] == p[pi]) pi++;
		if (pi == m) ans++, pi = f[pi-1];
	}
cout << ans << endl; }
