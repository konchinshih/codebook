  - Pisano Period: 任何線性遞迴（比如費氏數列）模任何一個數字 $M$ 都會循環，找循環節 $pi(M)$ 先質因數分解 $M = product p_i^(e_i)$，然後 $pi(M) = lcm(pi(p_i^(e_i)))$
  - Inversion: $a a^(-1) equiv 1 (mod m)$, exists iff $gcd(a,m)=1$. Linear: $a^(-1) equiv (m - floor(m/a)) times (m mod a)^(-1) (mod m)$
  - Fermat: $a^p equiv a (mod p)$; Euler: $a^(phi(n)) equiv 1 (mod n)$ if $gcd(a,n)=1$. Not coprime: 分解 $n = product p_i^(e_i)$，對每個 $p_i^(e_i)$ 分開看（互質：Euler／不互質：指數 $>= e_i$ 直接是 $0$），最後 CRT 合併. Also $a^b equiv a^(b mod phi(n) + phi(n))$ for $b >= log_2 n$.
  - Wilson: $(p-1)! equiv -1 (mod p)$
  - $phi(n)=n product_(p|n) (1 - 1/p)$, $quad sum_(d|n) phi(d) = n$
  - Divisor function: $n=product p_i^(a_i)$, $sigma_x (n)=product (p_i^((a_i+1)x)-1)/(p_i^x-1)$ ($x != 0$), $sigma_0 (n)=product (a_i+1)$
  - CRT (coprime): $M=product m_i$, $M_i=M/m_i$, $x = sum a_i M_i (M_i^(-1) mod m_i) (mod M)$ \
    General: $x = m_1 p + a_1 = m_2 q + a_2 => m_1 p - m_2 q = a_2 - a_1$, solve by extgcd, answer mod $lcm(m_1,m_2)$
  - Avoiding overflow: $c a mod c b = c(a mod b)$
  - Dirichlet convolution: $(f * g)(n) = sum_(d|n) f(d)g(n/d)$. $epsilon(n)=[n=1]$, $1(n)=1$, $italic("id")(n)=n$;
    $mu * 1 = epsilon$, $phi = mu * italic("id")$, $italic("id") = phi * 1$, $sigma_0 = 1 * 1$, $sigma_1 = italic("id") * 1$
  - $[gcd(a,b)=1] = sum_(d | gcd(a,b)) mu(d)$; Möbius inversion: $f = g * 1 <=> g = f * mu$
  - $sum_(i=1)^n sum_(j=1)^m [gcd(i,j)=1] = sum_d mu(d) floor(n/d) floor(m/d)$ (divisor block, $O(sqrt n)$ per query)
  - Legendre: $v_p (n!) = sum_(k>=1) floor(n / p^k) = (n - s_p (n)) / (p - 1)$, $s_p$ = digit sum in base $p$
  - Lucas ($p$ prime): $binom(n, m) equiv product_i binom(n_i, m_i) (mod p)$ over base-$p$ digits; Kummer: $v_p binom(n, m)$ = number of carries adding $m + (n-m)$ in base $p$
