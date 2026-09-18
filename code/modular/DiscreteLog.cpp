// Find the smallest N s.t. X^N = Y (mod P)
#define rep(i,a,b) for (int i = a; i <= b; i++)
ll Log(ll X, ll Y, ll P) {  // X, Y, P any
  X %= P, Y %= P; ll D = 1; int add = 0;
  while (true) {
    const auto g = gcd(X, P);
    if (g == 1) break;
    if (D == Y) return add;
    if (Y % g != 0) return -1;
    Y /= g, P /= g, add++;
    D = D * (X / g) % P;
  }
  const ll B = sqrtl(P) + 1;
  unordered_map<ll, int> mp;
  for (ll i = 0, cur = Y; i <= B; i++) {
    mp[cur] = i;
    cur = cur * X % P;
  }
  ll step = 1;
  rep (i, 1, B) step = step * X % P;
  for (ll p = 1, cur = D; p <= B; p++) {
    cur = cur * step % P;
    if (mp.contains(cur)) {
      return B * p - mp[cur] + add;
  } }
  return -1;
}
