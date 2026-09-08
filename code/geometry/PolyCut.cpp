// Dependency: bananaPoint(); T = double
// Cut a convex polygon with line (s -> e), keep right side
vector<Pt> polyCut(vector<Pt> poly, Pt s, Pt e) {
  vector<Pt> res; for (int i = 0; i < sz(poly); i++) {
    Pt cur = poly[i], prv = i ? poly[i - 1] : poly.back();
    bool side = ori(s, e, cur) < 0;
    if (side != (ori(s, e, prv) < 0)) {
      auto [p, d] = bananaPoint({s, e}, {cur, prv});
      res.pb(p / d);
    }
    if (side) res.pb(cur);
  } return res;
}