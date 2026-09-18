  - If $n = product p_i^(a_i)$, then
    $tau(n) = product (a_i + 1)$

  - Maximum $tau(n)$ for $n <= 10^k$:
  #align(center)[
    #table(
      columns: 6,
      align: center,
      stroke: none,
      inset: (x: 0.6em, y: 0.15em),

      [$k$], [$max tau(n)$], [$k$], [$max tau(n)$], [$k$], [$max tau(n)$],
      [3],  [32],    [9],  [1344],  [15], [26880],
      [4],  [64],    [10], [2304],  [16], [41472],
      [5],  [128],   [11], [4032],  [17], [64512],
      [6],  [240],   [12], [6720],  [18], [103680],
      [7],  [448],   [13], [10752], [],   [],
      [8],  [768],   [14], [17280], [],   [],
    )
  ]

  // columns are: k, max tau(n), k, max tau(n), ...

  - Useful bounds:
    $n <= 10^6 => tau(n) <= 240$ \
    $n <= 10^9 => tau(n) <= 1344$ \
    $n <= 10^12 => tau(n) <= 6720$ \
    $n <= 10^15 => tau(n) <= 26880$ \
    $n <= 10^18 => tau(n) <= 103680$

  // == Divisor Sum Complexity
  // $sum_(i=1)^n tau(i)
  //   = sum_(d=1)^n floor(n/d)
  //   approx n ln n + (2 gamma - 1)n$

  // Therefore:
  // $sum_(i=1)^n tau(i) = O(n log n)$

  // Typical divisor-sieve loop:
  // for d = 1..n:
  //   for multiple = d, 2d, ... <= n
  // runs in O(n log n).
