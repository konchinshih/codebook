// linear_sieve(n, primes, lp, phi, mu, d, sigma)
// Outputs over the index range 0..n (n >= 1):
//   primes : all primes in [2..n], increasing.
//   lp     : lowest prime factor; lp[1]=0, lp[x] is the smallest prime dividing x.
//   phi    : Euler totient, phi[x] = |{1<=k<=x : gcd(k,x)=1}|.  Multiplicative.
//   mu     : Möbius; mu[1]=1, mu[x]=0 if x has a squared prime factor, else (-1)^{#distinct primes}.
//   d      : number of divisors; if x=∏ p_i^{e_i}, then d[x]=∏(e_i+1).  Multiplicative.
//   sigma  : sum of divisors; if x=∏ p_i^{e_i}, then sigma[x]=∏(1+p_i+...+p_i^{e_i}). (use ll)
//
// Complexity: O(n) time, O(n) memory.
// Notes: Arrays are resized inside; primes is cleared and reserved. sigma uses ll to avoid 32-bit overflow.

static inline void linear_sieve(
  int n,
  std::vector<int> &primes,
  std::vector<int> &lp,
  std::vector<int> &phi,
  std::vector<int> &mu,
  std::vector<int> &d,
  std::vector<ll>  &sigma
) {
  lp.assign(n + 1, 0); phi.assign(n + 1, 0); mu.assign(n + 1, 0); d.assign(n + 1, 0); sigma.assign(n + 1, 0);
  primes.clear(); primes.reserve(n > 1 ? n / 10 : 0);
  std::vector<int> cnt(n + 1, 0), core(n + 1, 1);
  std::vector<ll>  p_pow(n + 1, 1), sum_p(n + 1, 1);
  phi[1] = mu[1] = d[1] = sigma[1] = 1;

  for (int i = 2; i <= n; ++i) {
    if (!lp[i]) {
      lp[i] = i; primes.push_back(i);
      phi[i] = i - 1; mu[i] = -1; d[i] = 2;
      cnt[i] = 1; p_pow[i] = i; core[i] = 1;
      sum_p[i] = 1 + (ll)i; sigma[i] = sum_p[i];
    }
    for (int p : primes) {
      long long ip = 1LL * i * p;
      if (ip > n) break;
      lp[ip] = p;
      if (p == lp[i]) {
        cnt[ip] = cnt[i] + 1; p_pow[ip] = p_pow[i] * p; core[ip] = core[i];
        sum_p[ip] = sum_p[i] + p_pow[ip];
        phi[ip] = phi[i] * p; mu[ip] = 0;
        d[ip] = d[core[ip]] * (cnt[ip] + 1);
        sigma[ip] = sigma[core[ip]] * sum_p[ip];
        break; // critical for linear complexity
      } else {
        cnt[ip] = 1; p_pow[ip] = p; core[ip] = i;
        sum_p[ip] = 1 + (ll)p;
        phi[ip] = phi[i] * (p - 1); mu[ip] = -mu[i];
        d[ip] = d[i] * 2;
        sigma[ip] = sigma[i] * sum_p[ip];
      }
    }
  }
}

// Optional helper: factorize x in O(log x) using lp (requires x in [2..n])
static inline std::vector<std::pair<int,int>> factorize(int x, const std::vector<int>& lp) {
  std::vector<std::pair<int,int>> res;
  while (x > 1) {
    int p = lp[x], e = 0;
    do { x /= p; ++e; } while (x % p == 0);
    res.push_back({p, e});
  }
  return res;
}

