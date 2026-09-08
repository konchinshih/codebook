struct Face { int a, b, c; };
auto preprocess(auto pts) {
  auto G = pts.begin(); vector<int> id;
  auto fail = tuple{-1, -1, -1, id};
  int a = find_if(all(pts), [&](P3 z) {
    return z.x != G->x || z.y != G->y || z.z != G->z;
  }) - G;
  if (a == sz(pts)) return fail;
  int b = find_if(all(pts), [&](P3 z) {
    return cross3(*G, pts[a], z) *
      cross3(*G, pts[a], z) > eps * eps;
  }) - G;
  if (b == sz(pts)) return fail;
  int c = find_if(all(pts), [&](P3 z) {
    return fabs(volume(*G, pts[a], pts[b], z)) > eps;
  }) - G;
  if (c == sz(pts)) return fail;
  for (int i = 0; i < sz(pts); i++)
    if (i != a && i != b && i != c) id.pb(i);
  return tuple{a, b, c, id};
}
// return the faces with point indexes
vector<Face> convexHull3D(vector<P3> pts) {
  int n = sz(pts); if (n <= 3) return {};
  vector<Face> now;
  vector<vector<int>> z(n, vector<int>(n));
  auto [a, b, c, ord] = preprocess(pts);
  if (a == -1) return {};
  now.emplace_back(a, b, c);
  now.emplace_back(c, b, a);
  for (auto i : ord) {
    vector<Face> nxt;
    for (auto& f : now) {
      auto v = volume(pts[f.a], pts[f.b], pts[f.c], pts[i]);
      if (v <= eps) nxt.pb(f);
      z[f.a][f.b] = z[f.b][f.c] = z[f.c][f.a] =
        v > eps ? 1 : v < -eps ? -1 : 0;
    }
    auto F = [&](int x, int y) {
      if (z[x][y] > 0 && z[y][x] <= 0)
        nxt.emplace_back(x, y, i);
    };
    for (auto& f : now)
      F(f.a, f.b), F(f.b, f.c), F(f.c, f.a);
    now = nxt;
  }
  return now;
}