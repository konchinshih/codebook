mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
#define RANDINT(a, b) uniform_int_distribution<int> (a, b)(rng) // inclusive
#define RANDLL(a, b) uniform_int_distribution<long long>(a, b)(rng)  // inclusive
#define RANDFLOAT(a, b) uniform_real_distribution<float>(a, b)(rng)  // exclusive
#define RANDDOUBLE(a, b) uniform_real_distribution<double>(a, b)(rng)  // exclusive
shuffle(v.begin(), v.end(), gen);
