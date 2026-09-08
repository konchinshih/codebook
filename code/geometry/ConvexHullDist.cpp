// Dependency: minkowski(), inConvex(), pointSegDist()
// T = double
double convexHullDist(vector<Pt> A, vector<Pt> B) {
  Pt O(0, 0); for (auto& p : B) p = O - p;
  auto C = minkowski(A, B);
  if (inConvex(C, O)) return 0;
  double ans = pointSegDist(O, C.back(), C[0]);
  for (int i = 0; i + 1 < sz(C); i++)
    ans = min(ans, pointSegDist(O, C[i], C[i + 1]));
  return ans; }