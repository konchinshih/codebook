// rep(i,a,b) here is INCLUSIVE: for (i = a; i <= b; i++)
i64 BSGS(i64 X, i64 Y, i64 P) {
  X %= P, Y %= P;
  assert(gcd(X, P) == 1);
  const i64 B = sqrtl(P) + 1;
  unordered_map<i64, int> mp;
  for (i64 i = 0, cur = Y; i <= B; i++) {
    mp[cur] = i;
    cur = cur * X % P;
  }
  i64 step = 1;
  rep (i, 1, B) step = step * X % P;
  for (i64 p = 1, cur = 1; p <= B; p++) {
    cur = cur * step % P;
    if (mp.contains(cur)) {
      return B * p - mp[cur];
    }
  }
  return -1;
}

i64 exBSGS(i64 X, i64 Y, i64 P) {
  X %= P, Y %= P;
  i64 D = 1;
  int add = 0;
  while (true) {
    const auto g = gcd(X, P);
    if (g == 1) break;
    if (D == Y) return add;
    if (Y % g != 0) return -1;
    Y /= g;
    P /= g;
    add++;
    D = D * (X / g) % P;
  }
  const i64 B = sqrtl(P) + 1;
  unordered_map<i64, int> mp;
  for (i64 i = 0, cur = Y; i <= B; i++) {
    mp[cur] = i;
    cur = cur * X % P;
  }
  i64 step = 1;
  rep (i, 1, B) step = step * X % P;
  for (i64 p = 1, cur = D; p <= B; p++) {
    cur = cur * step % P;
    if (mp.contains(cur)) {
      return B * p - mp[cur] + add;
    }
  }
  return -1;
}
