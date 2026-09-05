// Author: Gino, paste this in `struct AC {...}`
ll val[N];
void count_patterns(string& text, vector<string>& patterns){
  for (auto& p : patterns) insert(p);  build_fail();
  ranges::fill(val, 0LL);
  int ptr = 0; for (auto& c : text) {
    ptr = to[ptr][c - 'a']; val[ptr]++;
  }
  for (int x : span(order, order_cnt) | views::reverse)
    val[fail[x]] += val[x];
  for (auto& i : pid) cout << val[i] << endl;
}