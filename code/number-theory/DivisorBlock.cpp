// calls f(l, r, q) for each maximal [l, r] with floor(n/i) = q
void divisorBlock(ll n, auto f) {
  for (ll l = 1, r, q; l <= n; l = r + 1) {
    q = n / l, r = n / q;
    f(l, r, q);
  }
}
