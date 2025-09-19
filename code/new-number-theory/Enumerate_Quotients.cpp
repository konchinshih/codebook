// harmonic_decomposition — Enumerate Quotients blocks for floor(N / i)
// -------------------------------------------------------------------
// Idea: floor(N/i) takes only ~2*sqrt(N) distinct values. We iterate by blocks:
//   for l = 1..N:
//     q = N / l
//     r = N / q        // largest r s.t. floor(N/i) == q for all i in [l..r]
//     process block [l, r] with constant quotient q
// Time Complexity: O(sqrt(N)) blocks, O(1) work per block (plus your callback).
//
// 1) Callback version (recommended)
//
// Usage:
//   enumerate_quotients(N, [&](ll L, ll R, ll q){
//     // floor(N/i) == q for all i in [L..R]
//     // e.g., sum += (R - L + 1) * F(q);
//   });
//
using ll = long long;

template<class F>
static inline void enumerate_quotients(ll N, F fn){
  for(ll l = 1, r, q; l <= N; l = r + 1){
    q = N / l;
    r = N / q;
    fn(l, r, q);
  }
}

// 2) Vector version (if you need to store blocks)
//
// Returns vector of (L, R, q) with floor(N/i) == q on [L..R].
static inline std::vector<std::tuple<ll,ll,ll>> harmonic_blocks(ll N){
  std::vector<std::tuple<ll,ll,ll>> v;
  v.reserve(2 * (ll)std::sqrt((long double)N) + 5);
  for(ll l = 1, r, q; l <= N; l = r + 1){
    q = N / l;
    r = N / q;
    v.emplace_back(l, r, q);
  }
  return v;
}

// 3) Common pattern helper: sum_{i=1..N} F(floor(N/i))
//    Provide F(q) as a callable returning value type T.
//
template<class T, class F>
static inline T sum_over_quotients(ll N, F F_of_q){
  T acc = T(0);
  enumerate_quotients(N, [&](ll L, ll R, ll q){
    acc += (T)(R - L + 1) * F_of_q(q);
  });
  return acc;
}

