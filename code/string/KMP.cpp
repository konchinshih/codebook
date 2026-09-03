// Author: Gino
vector<int> kmp(string& s) {
  int n = (int)s.size();
  vector<int> f(n, 0);
  for (int i = 1, ptr = 0; i < n; i++) {
    while (ptr && s[i] != s[ptr]) ptr = f[ptr - 1];
    if (s[i] == s[ptr]) ptr++;
    f[i] = ptr;
  }
  return f;
}