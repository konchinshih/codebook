// Dependency: sameVec(), cmp(); T = long long
/* Having solution, check size > 2 */
/* --^-- Line.a --^-- Line.b --^-- */
auto halfPlaneIntersection(vector<Line> arr) {
  auto areaPair = [&](Line a, Line b) {
    return make_pair((a.b - a.a) ^ (b.a - a.a),
                     (a.b - a.a) ^ (b.b - a.a));
  };
  auto isin = [&](Line l0, Line l1, Line l2) {
    // Check inter(l1, l2) strictly in l0
    auto [a02X, a02Y] = areaPair(l0, l2);
    auto [a12X, a12Y] = areaPair(l1, l2);
    if (a12X - a12Y < 0) a12X *= -1, a12Y *= -1;
    return (__int128)a02Y * a12X -
      (__int128)a02X * a12Y > 0; // C^4
  };
  sort(all(arr), [&](Line a, Line b) {
    if (sameVec(a, b, 1))
      return ori(a.a, a.b, b.b) < 0;
    return cmp(a.b - a.a, b.b - b.a);
  });
  deque<Line> dq(1, arr[0]);
  auto popBack = [&](int t, Line p) {
    while (sz(dq) >= t &&
           !isin(p, dq[sz(dq) - 2], dq.back()))
      dq.pop_back();
  };
  auto popFront = [&](int t, Line p) {
    while (sz(dq) >= t && !isin(p, dq[0], dq[1]))
      dq.pop_front();
  };
  for (auto p : arr) if (!sameVec(dq.back(), p, 1))
    popBack(2, p), popFront(2, p), dq.pb(p);
  popBack(3, dq[0]), popFront(3, dq.back());
  return vector<Line>(all(dq));
}