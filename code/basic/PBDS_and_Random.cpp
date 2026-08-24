#include <bits/extc++.h>
using namespace __gnu_pbds;
// map
tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update> tr;
tr.order_of_key(element);
tr.find_by_order(rank);
// set
tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> tr;
tr.order_of_key(element);
tr.find_by_order(rank);
// priority queue
__gnu_pbds::priority_queue<int, less<int>> big_q;
__gnu_pbds::priority_queue<int, greater<int>> small_q;
q1.join(q2);  // join

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int>(a, b)(rng) // [a, b]
uniform_real_distribution<double>(a, b)(rng)  // (a, b)
shuffle(v.begin(), v.end(), gen);

