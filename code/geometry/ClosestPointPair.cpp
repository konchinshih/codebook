// returns {min squared dist, {i, j}}, n >= 2, |coord| < 1e9
pair<T, pair<int, int>> closestPair(vector<Pt> p) {
  vector<int> id(sz(p)); iota(all(id), 0);
  sort(all(id),
    [&](int a, int b) { return p[a].y < p[b].y; });
  set<pair<Pt, int>> s; // (point, id)
  pair<T, pair<int, int>> best = {(T)9e18, {-1, -1}};
  int l = 0; for (int i : id) {
    if (!best.first) break;
    T d = sqrtl(best.first) + is_integral_v<T>;
    while (p[id[l]].y <= p[i].y - d)
      s.erase({p[id[l]], id[l]}), l++;
    auto lo = s.lower_bound({p[i] - Pt{d, 0}, 0});
    auto hi = s.upper_bound({p[i] + Pt{d, 0}, sz(p)});
    for (; lo != hi; lo++) {
      auto [q, j] = *lo;
      best = min(best,
          {abs2(q - p[i]), {min(i, j), max(i, j)}});
    }
    s.insert({p[i], i});
  }
  return best;
}