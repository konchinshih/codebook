#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define iter(v) v.begin(), v.end()

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

/* ============================================= */
// debug(), output()
#define GRAY       "\x1b[90m"
#define COLOREND   "\x1b[0m"

void _debug() {}
template<typename A,typename... B> void _debug(A a,B... b) { cerr << a << ' ', _debug(b...); }
#define debug(...) cerr<<GRAY<<#__VA_ARGS__<<": "<<COLOREND,_debug(__VA_ARGS__),cerr<<endl

const int INF = 1.05e9;
const ll LINF = 4e18;

/* ============================================= */

void init(int &TEST) {
    // 如果有 t 筆測資的話，取消底下的註解
    //cin >> TEST;
}

void input() {}
void solve(int kase) {}

/* ============================================= */
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int TEST = 1; init(TEST);
    for (int kase = 1; kase <= TEST; kase++) {
        input();
        solve(kase);
    }
    return 0;
}
