// Author: std_abs
string rotate(auto s){ int n=s.size(), i=0, j=1;
  string t = s + s;
  while (i < n && j < n) {
    int k = 0; while (k < n && t[i + k] == t[j + k]) ++k;
    if (t[i + k] <= t[j + k]) j += k + 1; else i += k + 1;
    if (i == j) ++j;
  } return t.substr((i < n ? i : j), n);
}