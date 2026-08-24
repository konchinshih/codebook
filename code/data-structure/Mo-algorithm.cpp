// segments are 0-based
int B = max(1, (int)sqrt(n));
sort(Q.begin(), Q.end(), [&](const auto& a, const auto& b) {
  if (a[0]/B != b[0]/B) return a[0]<b[0];
  return (a[0]/B & 1) ? a[1]<b[1] : a[1]>b[1];
});
ll cur = 0;  // current answer
int pl = 0, pr = -1;
for (auto& qi : Q) {
  // get (l, r, qid) from qi
  while (pl < l) del(pl++); while (pl > l) add(--pl);
  while (pr < r) add(++pr); while (pr > r) del(pr--);
  ans[qid] = cur;
}
