// Author: Ian
struct Op; // reversible operation
const int maxn=2e5+5;
vector<Op> arr[(maxn+1)<<2];
#define m ((l + r) >> 1)
void insert(int ql, int qr, Op x, int i=1, int l=0, int r=maxn) {
    if (qr<=l || r<=ql) return;
    if (ql<=l && r<=qr) { arr[i].push_back(x); return; }
    if (qr<=m)
        insert(ql, qr, x, i<<1, l, m);
    else if (m<=ql)
        insert(ql, qr, x, i<<1|1, m, r);
    else {
        insert(ql, qr, x, i<<1, l, m);
        insert(ql, qr, x, i<<1|1, m, r);
    }
}
void traversal(vector<int>& ans, int i=1, int l=0, int r=maxn) {
    int opcnt = 0;
    for (auto val: arr[i])
        if (DO_SOMETHING(val))
            opcnt++;
    if (r-l==1) ans[l] = CALC_ANS();
    else {
        traversal(ans, i<<1, l, m);
        traversal(ans, i<<1|1, m, r);
    }
    while (opcnt--)
        UNDO_SOMETHING();
    arr[i].clear();
}
#undef m
