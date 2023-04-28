struct node {
    int c[26];
    ll cnt;
    node() {
        memset(c, 0, sizeof(c));
        cnt = 0;
    }
    node(ll x) {
        memset(c, 0, sizeof(c));
        cnt = x;
    }
};
struct Trie {
    vector<node> t;
    void init() {
        t.clear();
        t.emplace_back(node());
    }
    void insert(string s) {
        int ptr = 0;
        Each(i, s) {
            if (!t[ptr].c[i-'a']) {
                t.emplace_back(node());
                t[ptr].c[i-'a'] = (int)t.size()-1;
            }
            ptr = t[ptr].c[i-'a'];
        }
        t[ptr].cnt++;
    }
};
Trie trie;