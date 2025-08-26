// Author: Gino
// Function: Find closest pair of points in O(n log n)
#define x first
#define y second
int N;
T ans = 9e18;  // don't use LINF!!!
vector<Pt> p, tmp;

void init() {
    cin >> N;
    p.clear(); p.resize(N);
    for (auto& i : p) cin >> i.x >> i.y;
    sort(p.begin(), p.end());
}

void divide(int l, int r) {

int n = r-l+1;
if (n <= 20) {
    for (int i = l; i <= r; i++)
        for (int j = l; j < i; j++)
            ans = min(ans, dis(p[i], p[j]));
    return;
}

int mid = (l+r) >> 1;
int ml = mid, mr = mid;
T midx = p[mid].x;
while (l <= ml && p[ml].x == midx) ml--;
while (mr <= r && p[mr].x == midx) mr++;
divide(l, ml);
divide(mr, r);

tmp.clear();
for (int i = mid; i >= l; i--) {
    if ((p[i].x-midx) * (p[i].x-midx) <= ans)
        tmp.emplace_back(p[i]);
    else break;
}
for (int i = mid+1; i <= r; i++) {
    if ((p[i].x-midx) * (p[i].x-midx) <= ans)
        tmp.emplace_back(p[i]);
    else break;
}
sort(tmp.begin(), tmp.end(),
[&](const Pt& a, const Pt& b) {
    return a.y < b.y;
});

int nt = (int)tmp.size();
for (int i = 0; i < nt; i++)
    for (int j = i+1, cnt = 0; j < nt && cnt < 3; j++, cnt++)
        ans = min(ans, dis(tmp[i], tmp[j]));

}
