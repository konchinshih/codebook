// Author: chilli, Takanori MAEHARA (kactl)
// <!> Dependency: PushRelabel.cpp
// Given a list of edges representing an undirected flow graph,
// returns edges of the Gomory-Hu tree.
// maxflow / mincut of (u, v) => min edge from u to v on Gomory-Hu tree
// Time: O(V) * O(PushRelabel)
typedef array<ll, 3> Edge; // (u, v, w)
vector<Edge> gomoryHu(int N, vector<Edge> ed) {
	vector<Edge> tree;
	vi par(N);
	rep(i,1,N) {
		PushRelabel D(N); // Dinic also works
		for (Edge t : ed) D.addEdge(t[0], t[1], t[2], t[2]);
		tree.push_back({i, par[i], D.calc(i, par[i])});
		rep(j,i+1,N)
			if (par[j] == par[i] && D.leftOfMinCut(j)) par[j] = i;
	}
	return tree;
}
