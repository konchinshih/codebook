// Author: std_abs (slightly modified by Gino)
// Recap: fail[s] = s 的出現在 trie 上（也就是某個 pattern 的前綴）的最長 proper 後綴
// N := sum(length of all patterns) + 1
// 1. ac.insert(pat) -> end-node id recorded in ac.pid)
// 2. ac.build_fail()
// 3. run text: ptr = to[ptr][c-'a'] each char; accumulate on your own arrays
// - pull: rep(i ac.order_cnt-1 ~ 0) val[fail[x]] += val[x]
// - push: rep(i 0 ~ ac.order_cnt-1) val[x] += val[fail[x]]
// Tested @yosupo, N <= 1e6, 323ms on building AC
const int N = 1e6 + 5, C = 26;
struct AC {
  int ch[N][C], to[N][C], fail[N], _id, order[N], order_cnt;
  int np; vector<int> pid;  // pattern ID on trie
  // order[r] := which trie node has BFS order r
  // fail link tree: (parent) fail[i] <--- i (child)
  void reset() { _id = np = order_cnt = 0, pid.clear(), newnode(); }
  int newnode() {
    fill_n(ch[_id], C, 0), fill_n(to[_id], C, 0);
    fail[_id] = 0; return _id++;
  }
  AC () { reset(); }

  void insert(string s) {
    int ptr = 0;
    for (char c : s) {
      if (!ch[ptr][c - 'a'])
        ch[ptr][c - 'a'] = newnode();
      ptr = ch[ptr][c - 'a'];
    }
    np++; pid.emplace_back(ptr);
  }
  void build_fail() {
    queue <int> q;
    order_cnt = 0;
    for (int i = 0; i < C; ++i) if (ch[0][i])
      q.push(ch[0][i]), to[0][i] = ch[0][i];
    while (!q.empty()) {
      int u = q.front(); q.pop();
      order[order_cnt++] = u;
      for (int i = 0; i < C; ++i) {
        if (!ch[u][i]) to[u][i] = to[fail[u]][i];
        else {
          int v = ch[u][i], k = fail[u];
          while (k && !ch[k][i]) k = fail[k];
          if (ch[k][i]) k = ch[k][i];
          fail[v] = k, to[u][i] = v;
          q.push(v);
  } } } }
} ac;