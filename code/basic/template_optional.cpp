typedef pair<int, ll> pil;
typedef pair<ll, int> pli;

/* ============================================= */
// STL and I/O
// pair
template<typename T1, typename T2>
ostream& operator<<(ostream& os, pair<T1, T2> p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template<typename T1, typename T2>
istream& operator>>(istream& is, pair<T1, T2>& p) { return is >> p.first >> p.second; }

// vector
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
#define RED        "\x1b[31m"
#define GREEN      "\x1b[32m"
#define YELLOW     "\x1b[33m"

void _output() {}
template<typename A,typename... B> void _output(A a,B... b) { cout << a << ' ', _output(b...); }
#define output(...) _output(__VA_ARGS__),cout<<endl
/* ============================================= */
// BASIC ALGORITHM
string binary(ll x, int b = -1) {
    if (b == -1) b = __lg(x) + 1;
    string s = "";
    for (int k = b - 1; k >= 0; k--) {
        s.push_back((x & (1LL<<k)) ? '1' : '0');
    }
    return s;
}
/* ============================================= */
// CONSTANT
const int MOD = 1e9 + 7;
//const int MOD = 998244353;
const int maxn = 2e5 + 3;
