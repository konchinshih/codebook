const int N = 2e5+5;
vector<int> adj[N];
 
int dsu[N], sz[N], head[N], heavy[N], arr[N], num[N], dep[N], par[N], visited[N], val[N], t;
 
int tr[N<<2], tag[N<<2];
 
int combine(int a, int b){
    return max(a,b);
}
 
void push(int idx){
    if(tag[idx]){
        tr[idx<<1] = tag[idx];
        tr[idx<<1|1] = tag[idx];
        tag[idx<<1] = tag[idx];
        tag[idx<<1|1] = tag[idx];
        tag[idx] = 0;
    }
}
 
void modify(int ml, int mr, int val, int idx, int l, int r){
    if(ml > mr) swap(ml,mr);
    if(l!=r) push(idx);
    if(ml <= l && r <= mr){
        tr[idx] = val;
        tag[idx] = val;
        return;
    }
    int mid = l+r>>1;
    if(ml <= mid) modify(ml,mr,val,idx<<1,l,mid);
    if(mr > mid) modify(ml,mr,val,idx<<1|1,mid+1,r);
    tr[idx] = combine(tr[idx<<1],tr[idx<<1|1]);
}
 
int query(int ml, int mr, int idx, int l, int r){
    if(ml > mr) swap(ml,mr);
    if(l!=r) push(idx);
    if(ml <= l && r <= mr){
        return tr[idx];
    }
    int mid = l+r>>1;
    if(mr <= mid) return query(ml,mr,idx<<1,l,mid);
    if(ml > mid) return query(ml,mr,idx<<1|1,mid+1,r);
    return combine(query(ml,mr,idx<<1,l,mid),query(ml,mr,idx<<1|1,mid+1,r));
}
 
void dfs(int u, int p){
    int mxsz = 0, idx = 0;
    sz[u] = 1;
    visited[u] = 1;
    for(auto v : adj[u]){
        if(v==p) continue;
        dep[v] = dep[u]+1;
        par[v] = u;
        dfs(v,u);
        if(sz[v] > mxsz) mxsz = sz[v], idx = v;
        sz[u] += sz[v];
    }
    heavy[u] = idx;
}
 
 
void decompose(int u, int h){
    head[u] = h;
    arr[u] = ++t;
    visited[u] = 1;
    if(heavy[u]) decompose(heavy[u],h);
 
    for(auto v : adj[u]){
        if(v==par[u]||v==heavy[u]) continue;
        decompose(v,v);
    }
}
 
int hld_query(int u, int v){
    int res = 0;
    while(head[u]!=head[v]){
        if(dep[head[u]] < dep[head[v]]) swap(u,v);
        res = max(res,query(arr[head[u]],arr[u],1,1,t));
        u = par[head[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    res = max(res,query(arr[u],arr[v],1,1,t));
    return res;
}
 
void hld_modify(int u, int v, int val){
    if(dep[u] > dep[v]) swap(u,v);
    while(head[u]!=head[v]){
        if(dep[head[u]] < dep[head[v]]) swap(u,v);
        modify(arr[head[u]],arr[u],val,1,1,t);
        u = par[head[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    modify(arr[u],arr[v],val,1,1,t);
}
 