// preparation
// 1. write a 1-base BIT
// 2. init(n, mxc): n is number of elements, mxc = 值域
// 3. build info array CDQ.v by yourself (x, y, z, id)
// 4. call solve()
// => cdq.ans[i] is number of j s.t. (xj <= xi, yj <= yi, zj <= zi) (j != i)
struct CDQ {
    struct info {
        int x, y, z, id;
        info(int x, int y, int z, int id):
            x(x), y(y), z(z), id(id) {}
        info():
            x(0), y(0), z(0), id(0) {}
    };
    int n, mxc;
    BIT bit;
    vector<info> v;
    vector<ll> ans;
    void init(int _n, int _mxc) {
        n = _n; mxc = _mxc;
        v.assign(n, info{});
        ans.assign(n, 0);
    }
    void dfs(int l, int r) {
        if (l >= r) return;
        int mid = (l+r) >> 1;
        dfs(l, mid); dfs(mid+1, r);

        vector<info> tmp;
        vector<int> bit_op;
        int pl = l, pr = mid+1;

        while (pl <= mid && pr <= r) {
            if (v[pl].y <= v[pr].y) {
                tmp.emplace_back(v[pl]);
                bit.upd(v[pl].z, 1);
                bit_op.emplace_back(v[pl].z);
                pl++;
            }
            else {
                tmp.emplace_back(v[pr]);
                ans[v[pr].id] += bit.qry(v[pr].z);
                pr++;
            }
        }
        while (pl <= mid) {
            tmp.emplace_back(v[pl]);
            pl++;
        }
        while (pr <= r) {
            tmp.emplace_back(v[pr]);
            ans[v[pr].id] += bit.qry(v[pr].z);
            pr++;
        }
        for (int i = l, j = 0; i <= r; i++, j++) v[i] = tmp[j];
        for (auto& op : bit_op) bit.upd(op, -1);
    }
    void solve() {
        bit.init(mxc);
        sort(v.begin(), v.end(), [&](const info& a, const info& b){
            return (a.x == b.x ? (a.y == b.y ? (a.z == b.z ? a.id < b.id : a.z < b.z) : a.y < b.y) : a.x < b.x);
        });
        dfs(0, n-1);
        map<pair<int, pii>, int> s;
        sort(v.begin(), v.end(), [&](const info& a, const info& b){
            return a.id > b.id;
        });
        for (int i = 0, id = n-1; i < n; i++, id--) {
            pair<int, pii> tmp = make_pair(v[i].x, make_pair(v[i].y, v[i].z));
            auto it = s.find(tmp);
            if (it != s.end())
                ans[id] += it->second;
            s[tmp]++;
        }
    }
};
