// Author: Ian
// TODO: (2025/08/26) Debug Lazy Segment Tree
constexpr int maxn=2e5+5;
int arr[(maxn+1)<<2];
#define m ((l+r)>>1)
void build(V<int>& v,int i=1,int l=0,int r=maxn){
    if((int)v.size()<=l) return;
    if(r-l==1){arr[i]=v[l];return;}
    build(v,i<<1,l,m),build(v,i<<1|1,m,r);
    arr[i]=max(arr[i<<1],arr[i<<1|1]);
}
void modify(int p,int k,int i=1,int l=0,int r=maxn){
    if(p<l||r<=p) return;
    if(r-l==1){arr[i]=k;return;}
    if(p<m) modify(p,k,i<<1,l,m);
    else modify(p,k,i<<1|1,m,r);
    arr[i]=max(arr[i<<1],arr[i<<1|1]);
}
int query(int ql,int qr,int i=1,int l=0,int r=maxn){
    if(qr<=l||r<=ql) return 0;
    if(ql<=l&&r<=qr) return arr[i];
    if(qr<=m) return query(ql,qr,i<<1,l,m);
    if(m<=ql) return query(ql,qr,i<<1|1,m,r);
    return max(query(ql,qr,i<<1,l,m),query(ql,qr,i<<1|1,m,r));
}
#undef m
inline void solve(){
    int n,q;cin>>n>>q;
    V<int> v(n);
    for(auto& i:v) 
        cin>>i;
    V<V<int>> e(n);
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b,a--,b--;
        e[a].emplace_back(b);
        e[b].emplace_back(a);
    }
    V<int> d(n,0),f(n,0),sz(n,1),son(n,-1);
    F<void(int,int)> dfs1=
    [&](int x,int pre){
        for(auto i:e[x]) if(i!=pre){
            d[i]=d[x]+1,f[i]=x;
            dfs1(i,x),sz[x]+=sz[i];
            if(!~son[x]||sz[son[x]]<sz[i])
                son[x]=i;
        }
    };dfs1(0,0);
    V<int> top(n,0),dfn(n,-1),rnk(n,0);
    F<void(int,int)> dfs2=
    [&](int x,int t){
        static int cnt=0;
        dfn[x]=cnt++,rnk[dfn[x]]=x,top[x]=t;
        if(!~son[x]) return;
        dfs2(son[x],t);
        for(auto i:e[x]) 
            if(!~dfn[i]) dfs2(i,i);
    };dfs2(0,0);
    V<int> dfnv(n);
    for(int i=0;i<n;i++)
        dfnv[dfn[i]]=v[i];
    build(dfnv);
    while(q--){
        int op,a,b;cin>>op>>a>>b;
        switch(op){
        case 1:{
            modify(dfn[a-1],b);
        }break;
        case 2:{
            a--,b--;
            int ans=0;
            while(top[a]!=top[b]){
                if(d[top[a]]>d[top[b]]) swap(a,b);
                ans=max(ans,query(dfn[top[b]],dfn[b]+1));
                b=f[top[b]];
            }
            if(dfn[a]>dfn[b]) swap(a,b);
            ans=max(ans,query(dfn[a],dfn[b]+1));
            cout<<ans<<endl;
        }break;
        }
    }
}
