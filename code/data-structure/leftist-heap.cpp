struct node{
    node *l,*r;
    int d, v;
    node(int x):d(1),v(x){
        l=r=nullptr;
    }
};
static inline int d(node* x){return x?x->d:0;}
node* merge(node* a,node* b){
    if(!a||!b) return a?:b;
//  min heap
    if(a->v>b->v) swap(a,b);
    a->r=merge(a->r,b);
    if(d(a->l)<d(a->r))
        swap(a->l,a->r);
    a->d=d(a->r)+1;
    return a;
}
