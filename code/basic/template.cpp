#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false); cin.tie(0);
#define endl '\n'
#define iter(v) v.begin(), v.end()

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;

/* ============================================= */
// STL and I/O

// pair
template<typename T1, typename T2>
istream& operator>>(istream& is, pair<T1, T2>& p) { return is >> p.first >> p.second; }

template<typename T1, typename T2>
ostream& operator<<(ostream& os, pair<T1, T2> p) {
    return os << "(" << p.first << ", " << p.second << ")";
}


// vector
template<typename T>
void reset(vector<T>& v, int n) {v.clear(); v.resize(n);}

template<typename T>
void reset(vector<T>& v, int n, T x) {v.clear(); v.resize(n, x);}

template<typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (const auto& x : v) os << x << ' ';
    return os;
}


/* ============================================= */
// debug(), output()
#define COLOREND   "\x1b[0m"
#define RED        "\x1b[31m"
#define GREEN      "\x1b[32m"
#define YELLOW     "\x1b[33m"
#define GRAY       "\x1b[90m"
void _debug() {}
template<typename A,typename... B> void _debug(A a,B... b) { cerr << a << ' ', _debug(b...); }
#define debug(...) cerr<<GRAY<<#__VA_ARGS__<<": "<<COLOREND,_debug(__VA_ARGS__),cerr<<endl

void _output() {}
template<typename A,typename... B> void _output(A a,B... b) { cout << a << ' ', _output(b...); }
#define output(...) _output(__VA_ARGS__),cout<<endl


/* ============================================= */
// BASIC ALGORITHM

template<typename T>
void bpre(vector<T>& pv, vector<T>& v) {
    int n = (int)v.size();
    pv.clear(); pv.resize(n);
    for (int i = 0; i < n; i++)
        pv[i] = (i ? pv[i - 1] : 0) + v[i];
}
template<typename T>
void bsuf(vector<T>& sv, vector<T>& v) {
    int n = (int)v.size();
    sv.clear(); sv.resize(n);
    for (int i = n - 1; i >= 0; i--)
        sv[i] = (i + 1 < n ? sv[i + 1] : 0) + v[i];
}
template<typename T>
T qpre(vector<T>& pv, int l, int r) {
    if (l > r) return 0;
    return pv[r] - (l ? pv[l - 1] : 0);
}
template<typename T>
T qsuf(vector<T>& sv, int l, int r) {
    if (l > r) return 0;
    return sv[l] - (r + 1 < (int)sv.size() ? sv[r + 1] : 0);
}

void binary(ll x, int b = -1) {
    if (b == -1) b = __lg(x) + 1;
    for (int k = b - 1; k >= 0; k--) {
        cerr << ((x & (1LL<<k)) ? 1 : 0);
    }
    cerr << ' ' << " (" << x << ")" << endl;
}

/* ============================================= */
// CONSTANT

const int MOD = 1e9 + 7;
//const int MOD = 998244353;
const int INF = 1.05e9;
const ll LINF = 4e18;

const int maxn = 2e5 + 3;

/* ============================================= */
// ALGORITHM TEMPLATE


/* ============================================= */
// TEMPLATE (ver. 2025 05/08)

void init(int &TEST) {
    // comment this if there's only single testcase
    cin >> TEST;
}

void input() {}
void solve() {}

/* ============================================= */
int main() {
    fastio
    int TEST = 1;
    init(TEST);
    for (int _ti = 1; _ti <= TEST; _ti++) {
        input();
        solve();
    }
    return 0;
}

