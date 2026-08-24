// Author: Ian
// Function: min-heap, with amortized O(lg n) merge
struct node {
  node *l, *r; int v;
  node(int x): v(x) { l = r = nullptr; }
};
node* merge(node* a,node* b) {
  if (!a || !b) return a ?: b;
  if (a->v > b->v) swap(a, b);
  return a->r = merge(a->r, b), swap(a->l, a->r), a;
}
