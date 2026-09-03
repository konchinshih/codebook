// Author: std_abs
// Z[i] = length of the longest substring starting from s[i] which is also a prefix of s
vector<int> buildZ(auto s) {
  int n = (int)s.size(), l = 0, r = 0;
  vector<int> Z(n);
  for (int i = 0; i < n; ++i) {
    Z[i] = max(min(Z[i - l], r - i), 0);
    while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
      l = i, r = i + Z[i], Z[i]++;
  }
  return Z;
}