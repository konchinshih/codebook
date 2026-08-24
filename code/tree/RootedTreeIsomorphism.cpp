// Author: Gino
// Checks if 2 rooted trees are isomorphic
// Time: O(V log V)
// vector<vector<int>> G1, G2;
// int root_1, root_2;
map<vector<int>, int> dict;
int encode(const auto& G, int u, int pa = -1) {
  vector<int> codes;
  for (auto& v : G[u])
    if (v != pa)
      codes.emplace_back(encode(G, v, u));
  ranges::sort(codes);
  auto [it, _] = dict.try_emplace(codes, dict.size());
  return it->second;
}
bool isomorphic() {
  dict.clear();  dict[{}] = 0;
  return encode(G1, root_1) == encode(G2, root_2);
}
