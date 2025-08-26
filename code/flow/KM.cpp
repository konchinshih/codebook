// Author: Unknown
// Function: Weighted Max Bipartite Matching in O(V^3)
#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

struct KuhnMunkres {
    int n;
    vector<vector<int>> g;
    vector<int> lx, ly, slack;
    vector<int> match, visx, visy;
    KuhnMunkres(int n) : n(n), g(n, vector<int>(n)),
        lx(n), ly(n), slack(n), match(n), visx(n), visy(n) {}
    vector<int> & operator[](int i) { return g[i]; }
    bool dfs(int i, bool aug) { // aug = true 表示要更新 match
        if(visx[i]) return false;
        visx[i] = true;
        for(int j = 0; j < n; j++) {
            if(visy[j]) continue;
            // 一邊擴增交錯樹、尋找增廣路徑
            // 一邊更新slack：樹上的點跟樹外的點所造成的最小權重
            int d = lx[i] + ly[j] - g[i][j];
            if(d == 0) {
                visy[j] = true;
                if(match[j] == -1 || dfs(match[j], aug)) {
                    if(aug)
                        match[j] = i;
                    return true;
                }
            } else {
                slack[j] = min(slack[j], d);
            }
        }
        return false;
    }
    bool augment() { // 回傳是否有增廣路
        for(int j = 0; j < n; j++) if(!visy[j] && slack[j] == 0) {
            visy[j] = true;
            if(match[j] == -1 || dfs(match[j], false)) {
                return true;
            }
        }
        return false;
    }
    void relabel() {
        int delta = inf;
        for(int j = 0; j < n; j++) if(!visy[j]) delta = min(delta, slack[j]);
        for(int i = 0; i < n; i++) if(visx[i]) lx[i] -= delta;
        for(int j = 0; j < n; j++) {
            if(visy[j]) ly[j] += delta;
            else slack[j] -= delta;
        }
    }
    int solve() {
        for(int i = 0; i < n; i++) {
            lx[i] = 0;
            for(int j = 0; j < n; j++) lx[i] = max(lx[i], g[i][j]);
        }
        fill(ly.begin(), ly.end(), 0);
        fill(match.begin(), match.end(), -1);
        for(int i = 0; i < n; i++) {
            // slack 在每一輪都要初始化
            fill(slack.begin(), slack.end(), inf);
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            if(dfs(i, true)) continue;
            // 重複調整頂標直到找到增廣路徑
            while(!augment()) relabel();
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            dfs(i, true);
        }
        int ans = 0;
        for(int j = 0; j < n; j++) if(match[j] != -1) ans += g[match[j]][j];
        return ans;
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    while(cin >> n && n) {
        KuhnMunkres KM(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int c;
                cin >> c;
                if(c > 0)
                    KM[i][j] = c;
            }
        }
        cout << KM.solve() << '\n';
    }
}
