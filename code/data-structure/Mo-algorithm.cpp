// segments are 0-based
ll cur = 0;  // current answer
int pl = 0, pr = -1;
for (auto& qi : Q) {
    // get (l, r, qid) from qi
    while (pl < l) del(pl++);
    while (pl > l) add(--pl);
    while (pr < r) add(++pr);
    while (pr > r) del(pr--);
    ans[qid] = cur;
}
