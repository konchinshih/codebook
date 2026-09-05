// Author: std_abs
// state (i.e. node) -> all substr with the same endpos
// those substrs' length in range [len(link) + 1, len]
// state i's endpos set -> union of pos[i] over the subtree of i in the suffix link tree
// link[i] -> longest suffix with different endpos set  (suffix link tree edge)
// len[i]  -> length longest suffix of state i
// pos[i]  -> an example end position of state i (1-based)
// cnt[i]  -> size of endpos set of state i, built by build_cnt() (tree DP)
const int N = 5e5 + 10, C = 26;
struct SAM {
  int ch[2*N][C],len[2*N],link[2*N],pos[2*N],cnt[2*N],_id;
  SAM () { reset(); }
  void reset() { _id = 0, newnode(), link[0] = -1; }
  int newnode() {
    fill_n(ch[_id], C, 0);
    len[_id] = link[_id] = pos[_id] = cnt[_id] = 0;
    return _id++;
  }
  void build(string s) {
    int last = 0; for (int i = 0; i < (int)s.size(); i++) {
      char c = s[i]; int cur = newnode();
      len[cur] = len[last] + 1, pos[cur] = i + 1;
      int p = last;
      while (~p && !ch[p][c - 'a'])
        ch[p][c - 'a'] = cur, p = link[p];
      if (p == -1) link[cur] = 0;
      else {  // conflict: p --> q, p --> cur
        int q = ch[p][c - 'a'];
        if (len[p] + 1 == len[q]) { // q is suffix of cur
          link[cur] = q;
        } else {  // we need auxiliary state
          int nxt = newnode();
          len[nxt] = len[p] + 1, link[nxt] = link[q];
          pos[nxt] = 0;
          for (int j = 0; j < C; j++)
            ch[nxt][j] = ch[q][j];
          while (~p && ch[p][c - 'a'] == q)
            ch[p][c - 'a'] = nxt, p = link[p];
          link[q] = link[cur] = nxt;
      } }
      cnt[cur]++, last = cur;
  } }
} sam;
// void build_cnt() {
//   vector<int> p(_id); iota(all(p), 0); sort(all(p),
//     [&](int i, int j){ return len[i] > len[j]; });
//   for (int i = 0; i < _id; ++i) if (link[p[i]] != -1)
//     cnt[link[p[i]]] += cnt[p[i]];
// }
// bool match(string s) {
//   int p = 0; for (auto& c : s) {
//     if (!ch[p][c - 'a']) return false;
//     p = ch[p][c - 'a'];
//   } return true; }

