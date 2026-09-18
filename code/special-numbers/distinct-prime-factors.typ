  - Let $omega(n) =$ number of distinct prime factors.
  - Minimum number with $k$ distinct prime factors is the product
    of the first $k$ primes.
    - $2 dot 3 dot 5 dot 7 dot 11 dot 13 dot 17 dot 19 = 9699690$
    - $2 dot 3 dot ... dot 23 = 223092870$
    - $2 dot 3 dot ... dot 29 = 6469693230$
    - $n <= 10^9 => omega(n) <= 9$, $n <= 10^18 => omega(n) <= 15$
  - Number of square-free divisors $= 2^omega(n)$
    - $n <= 10^9 => <= 512$, $n <= 10^18 => <= 32768$
