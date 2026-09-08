// Dependency: ref()
struct Event {
  Pt d; int u, v;
  bool operator<(const Event& o) const {
    return sgn(d ^ o.d) > 0;
} };
void rotatingSweepLine(vector<Pt> pts) {
  int n = sz(pts);
  vector<int> ord(n), pos(n); vector<Event> e;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      e.push_back({ref(pts[i] - pts[j]), i, j});
  sort(all(e)); iota(all(ord), 0);
  sort(all(ord), [&](int i, int j) {
    return sgn(pts[i].y - pts[j].y) == 0 ?
      pts[i].x < pts[j].x : pts[i].y < pts[j].y;
  });
  for (int i = 0; i < n; i++) pos[ord[i]] = i;
  auto makeReverse = [](auto v) {
    sort(all(v));
    v.resize(unique(all(v)) - v.begin());
    vector<pii> segs;
    for (int i = 0, j = 0; i < sz(v); i = j) {
      for (; j < sz(v) && v[j] - v[i] <= j - i; j++);
      segs.emplace_back(v[i], v[j - 1] + 1 + 1);
    }
    return segs;
  };
  for (int i = 0, j = 0; i < sz(e); i = j) {
    vector<int> tmp;
    for (; j < sz(e) && !(e[i] < e[j]); j++)
      tmp.pb(min(pos[e[j].u], pos[e[j].v]));
    for (auto [l, r] : makeReverse(tmp)) {
      reverse(ord.begin() + l, ord.begin() + r);
      for (int t = l; t < r; t++) pos[ord[t]] = t;
      // update value here
} } }