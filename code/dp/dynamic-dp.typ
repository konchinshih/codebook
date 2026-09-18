  - 適用情境：$d p_i = M_i dot d p_(i-1) arrow.double d p_i = M_i M_(i-1) dots.c M_1 d p_0$
  - 當 $M_i$ 需要動態修改，且 $M_i$ 是廣義矩陣乘法：

  $ C_(i j) = limits(op("⨁"))_k A_(i k) times.o B_(k j)
     $
  - 滿足 $(plus.o, times.o)$ 是半環（$times.o$ 對 $plus.o$ 有分配律、$times.o$ 和 $plus.o$ 有結合律、$plus.o$ 有交換律）
  - 此時便可用線段樹維護 $M_n M_(n-1) dots.c M_1$ 的乘積。線段樹上的 pos 是 $M_"pos"$，但 pull 時要 `st[idx] = mul(st[cr], st[cl])`
