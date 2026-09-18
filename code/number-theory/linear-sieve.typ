  $O(n)$, each $i$ crossed out once by its least prime $p$:
  ```
  for i in 2..n:
    if lpf[i] == 0: lpf[i] = i, primes.pb(i), f[i] = f(p)
    for p in primes:
      if p > lpf[i] or i * p > n: break
      lpf[i*p] = p
      f[i*p] = (i % p ? f[i] * f[p] : <recurrence>)
  ```
  Recurrence for $i p$ when $p | i$ (let $i = p^k m$, $p ∤ m$):
  - $phi(i p) = phi(i) dot p$, $quad mu(i p) = 0$, $quad sigma_0 (i p) = sigma_0 (i) dot (k+2)/(k+1)$
  - General: keep $"pw"[i] = p^k$; $f(i p) = f(i / "pw"[i]) dot f("pw"[i] dot p)$
  - $phi(i p) = phi(i) dot (p - [p ∤ i])$ (one formula for both cases)
  Euler phi table alone (no primes): $O(n log log n)$ \
  `for i: phi[i]=i; for p prime: for j=p,2p..: phi[j] -= phi[j]/p`
