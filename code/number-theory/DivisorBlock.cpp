template<class F>
void divisorBlock(ll n, F handle) {
  for (ll l = 1, r = 1, q = n; l <= n; l = r + 1) {
    q = n / l;
    r = n / q;
    // handle [l, r], floor(n/i) = n / l
    handle(l, r, q);
  }
}

void divisorBlock(ll n) {
  divisorBlock(n, [](ll, ll, ll) {});
}
