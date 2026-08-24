 /**
 * Author: koukanni
 * Date: 2025
 * License: CC0
 * Source: 
 * Description: 
 * $f_{prime}(n) = \sum f(p), \; 2 \leq p \leq n \texttt{ and p is prime}$
 * $f_k(p, c) = f(p^c)$
 * Time : $O(N^{3/4} / \log N)$
 * Status: tested
 */

 template<class T, class F1, class F2>
 T Black(const i64 N, const F1 f_prime, const F2 f_k) {
   const i64 sqrtN = sqrtl(N);
   const int np = int(size(primes));
   T res = 1 + f_prime(N);
   function<void(i64, i64, i64, T, T)> rec = [&](i64 t, i64 i, i64 c, T ft, T fu) {
     const auto f_next = fu * f_k(primes[i], c + 1);
     res += f_next + ft * (f_prime(f64(N) / t) - f_prime(primes[i]));
     const i64 lim = sqrtl(f64(N) / t);
     if (primes[i] <= lim) {
       rec(t * primes[i], i, c + 1, f_next, fu);
     }
     for (int j = i + 1; j < np; j++) {
       if (primes[j] > lim) break;
       rec(t * primes[j], j, 1, ft * f_k(primes[j], 1), ft);
     }
   };
   for (int i = 0; i < np; i++) {
     if (primes[i] <= sqrtN) {
       rec(primes[i], i, 1, f_k(primes[i], 1), 1);
     }
   }
   return res;
 }