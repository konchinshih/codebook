// Author: Ian
// Function: 插入、刪除最小值、合併兩個左偏樹都能 O(log n)
struct node{
    node *l,*r;
    int v;
    node(int x):v(x){
        l=r=nullptr;
    }
};
node* merge(node* a,node* b){
    if(!a||!b) return a?:b;
//  min heap
    if(a->v>b->v) swap(a,b);
    a->r=merge(a->r,b);
    swap(a->l,a->r);
    return a;
}
