// Author: std_abs
vector<int> Z(auto s){ int n=s.size(); vector<int> Z(n);
  for (int i = 0, l = 0, r = 0; i < n; ++i) {
    Z[i] = max(min(Z[i - l], r - i), 0);
    while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
      l = i, r = i + Z[i], Z[i]++;
  } return Z;
}