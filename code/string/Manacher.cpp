// Author: std_abs
// return array Z (length == 2N - 1)
// Example: s = "aaaa"
//  a       a       a       a
// Z_0 Z_1 Z_2 Z_3 Z_4 Z_5 Z_6
//  1   2   3	  4   3   2   1
// The corresponding palindrome s[l..r]:
// l = (i - Z[i] + 1) / 2
// r = (i + Z[i] - 1) / 2
vector<int> manacher(auto tmp) {
  vector<int> s(1, -1);
  for (auto c : tmp) s.push_back(c), s.push_back(-1);
  int l = 0, r = 0, n = (int)s.size();
  vector<int> Z(n);
  for (int i = 0; i < n; ++i) {
    Z[i] = r > i ? min(Z[2 * l - i], r - i) : 1;
    while (i - Z[i] >= 0 && i + Z[i] < n && 
           s[i + Z[i]] == s[i - Z[i]]) Z[i]++;
    if (Z[i] + i > r) l = i, r = Z[i] + i;
  }
  for (int i = 0; i < n; ++i)
    Z[i] = (Z[i] - (i & 1)) / 2 * 2 + (i & 1);
  return vector<int>(Z.begin() + 1, Z.end() - 1);
}