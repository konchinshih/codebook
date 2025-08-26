// Author: Benson
// Function: Max Flow, O(V^2 E)
struct Dinic {
    struct Edge {
        int t, c, r;
        Edge() {}
        Edge(int _t, int _c, int _r):
            t(_t), c(_c), r(_r) {}
    };
    vector<vector<Edge>> G;
    vector<int> dis, iter;
    int s, t;
    void init(int n) {
        G.resize(n), dis.resize(n), iter.resize(n);
        for(int i = 0; i < n; ++i)
            G[i].clear();
    }
    void add(int a, int b, int c) {
        G[a].eb(b, c, G[b].size());
        G[b].eb(a, 0, G[a].size() - 1);
    }
    bool bfs() {
        fill(ALL(dis), -1);
        dis[s] = 0;
        queue<int> que;
        que.push(s);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(auto& e : G[u]) {
                if(e.c > 0 && dis[e.t] == -1) {
                    dis[e.t] = dis[u] + 1;
                    que.push(e.t);
                }
            }
        }
        return dis[t] != -1;
    }
    int dfs(int u, int cur) {
        if(u == t) return cur;
        for(int &i = iter[u]; i < (int)G[u].size(); ++i) {
            auto& e = G[u][i];
            if(e.c > 0 && dis[u] + 1 == dis[e.t]) {
                int ans = dfs(e.t, min(cur, e.c));
                if(ans > 0) {
                    G[e.t][e.r].c += ans;
                    e.c -= ans;
                    return ans;
                }
            }
        }
        return 0;
    }
    
    int flow(int a, int b) {
        s = a, t = b;
        int ans = 0;
        while(bfs()) {
            fill(ALL(iter), 0);
            int tmp;
            while((tmp = dfs(s, INF)) > 0)
                ans += tmp;
        }
        return ans;
    }
};
