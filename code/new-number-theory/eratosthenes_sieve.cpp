// Classic Eratosthenes sieve: O(n log log n)
// Fills: is_prime[0..n] (char: 1=prime,0=not), and primes list in increasing order.
static inline void eratosthenes_sieve(int n, std::vector<int>& primes, std::vector<char>& is_prime) {
  is_prime.assign(n + 1, 1); if (n >= 0) is_prime[0] = 0; if (n >= 1) is_prime[1] = 0;
  primes.clear(); primes.reserve(n > 1 ? n / 10 : 0);
  if (n >= 2) primes.push_back(2);
  for (int j = 4; j <= n; j += 2)
    is_prime[j] = 0;
  for (int i = 3; 1LL * i * i <= n; i += 2) if (is_prime[i])
    for (long long j = 1LL * i * i; j <= n; j += i << 1)
      is_prime[(int)j] = 0;
  for (int i = 3; i <= n; i += 2) if (is_prime[i])
    primes.push_back(i);
}

