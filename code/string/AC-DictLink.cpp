// Author: Gino, paste this in `struct AC {...}`
// 3 Modifications to the original AC Automaton:
// int np; vector<int> pid; bool is_pattern[N];
// fail[_id] = 0, is_pattern[_id] = false; return _id++;
// np++; pid.emplace_back(ptr); is_pattern[ptr] = true;
int dict[N];
void build_dict() { // call this after build_fail()!
  for (int i = 0; i < order_cnt; i++) {
    int u = order[i], f = fail[u];
    dict[u] = is_pattern[f] ? f: dict[f];
  }
}