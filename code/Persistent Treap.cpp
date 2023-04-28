struct node {
	node *l, *r;
	char c; int v, sz;
	node(char x = '$'): c(x), v(mt()), sz(1) {
		l = r = nullptr;
	}
	node(node* p) {*this = *p;}
	void pull() {
		sz = 1;
		for (auto i : {l, r})
			if (i) sz += i->sz;
	}
} arr[maxn], *ptr = arr;
inline int size(node* p) {return p ? p->sz : 0;}
node* merge(node* a, node* b) {
	if (!a || !b) return a ? : b;
	if (a->v < b->v) {
		node* ret = new(ptr++) node(a);
		ret->r = merge(ret->r, b), ret->pull();
		return ret;
	}
	else {
		node* ret = new(ptr++) node(b);
		ret->l = merge(a, ret->l), ret->pull();
		return ret;
	}
}
P<node*> split(node* p, int k) {
	if (!p) return {nullptr, nullptr};
	if (k >= size(p->l) + 1) {
		auto [a, b] = split(p->r, k - size(p->l) - 1);
		node* ret = new(ptr++) node(p);
		ret->r = a, ret->pull();
		return {ret, b};
	}
	else {
		auto [a, b] = split(p->l, k);
		node* ret = new(ptr++) node(p);
		ret->l = b, ret->pull();
		return {a, ret};
	}
}