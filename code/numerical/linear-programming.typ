  Standard form: max $bold(c)^T bold(x)$ s.t. $A bold(x) <= bold(b)$, $bold(x) >= 0$.
  Dual: min $bold(b)^T bold(y)$ s.t. $A^T bold(y) >= bold(c)$, $bold(y) >= 0$; optima equal (strong duality).
  Complementary slackness: $overline(x), overline(y)$ optimal iff for all $i$: $overline(x)_i = 0$ or $sum_j A_(j i) overline(y)_j = c_i$, and for all $j$: $overline(y)_j = 0$ or $sum_i A_(j i) overline(x)_i = b_j$.
  To standard form: minimize $=>$ negate $c$; $>=$ row $=>$ negate row; $=$ row $=>$ both $<=$ and $>=$; free $x_i$ $=>$ $x_i - x_i'$.
