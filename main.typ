// ============================================================
//  NYCU_LLLemonade_Jam Codebook — converted from main.tex to Typst
// ============================================================

#let page-header-size = 7pt
#let page-number-size = 8pt

#let heading1-size = 15pt
#let heading2-size = 11.5pt
#let body-size = 9pt

#let code-size = 9pt
#let line-number-size = 6pt
#let code-line-number-color = rgb("#c0c7d2")
#let code-line-spacing = -0.3em
#let code-wrap-leading = 0.3em

#let table-of-contents-size = 7pt
#let table-of-contents-section-spacing = 0.5em
#let table-of-contents-entry-spacing = 0.3em


#let heading1-background = rgb("#c9c9c9")
#let heading2-background = rgb("#e3e3e3")

#set text(
  // The W3 and W6 files are registered as one family. Typst selects W3
  // for normal text and W6 when weight: "bold" is requested.
  font: "Hiragino Mincho ProN",
  size: body-size,
)
#set raw(theme: "themes/codeblock-theme.tmTheme")


#let team = "NYCU_This_Page_Was_Intentionally_Left_Blank"
#let univ = "National Yang Ming Chiao Tung University"

#set page(
  paper: "a4",
  margin: (top: 1.3cm, bottom: 1cm, x: 1cm),
  numbering: none,
  footer: context [
    #align(center, text(size: page-number-size)[#counter(page).display()])
  ],
  header: context [
    #set text(size: page-header-size)
    #grid(
      columns: (1fr, 1.8fr, 1fr),
      align: (left, center, right),
      [#team], [#univ], [#counter(page).display()],
    )
    #v(-0.7em)
    #line(length: 100%, stroke: 0.4pt)
  ],
)

#set heading(numbering: "1.1")
#show heading.where(level: 1): it => {
  v(0.2em, weak: true)
  block(
    fill: heading1-background,
    width: 100%,
    inset: (x: 4pt, y: 2pt),
  )[
    #text(size: heading1-size, weight: "bold")[#counter(heading).display() #h(0.4em) #it.body]
  ]
  v(-0.35em)
}
#show heading.where(level: 2): it => {
  v(0.2em, weak: true)
  block(
    fill: heading2-background,
    width: 100%,
    inset: (x: 4pt, y: 2pt),
  )[
    #text(size: heading2-size, weight: "bold")[#counter(heading).display() #h(0.4em) #it.body]
  ]
  v(-0.35em)
}

#set list(marker: [•], indent: 0.3em, spacing: 0.5em, tight: true)
#set enum(indent: 0.5em, spacing: 0.3em, tight: true)
#set par(justify: true, leading: 0.3em)

// ---- code block with line numbers + custom theme ----
#let codebox(body) = block(
  inset: (y: 0pt),
  width: 100%,
  breakable: true,
)[
  #set text(font: ("CodeNewRoman Nerd Font Propo", "Hiragino Mincho ProN"), size: code-size)
  #set par(justify: false, leading: code-wrap-leading, spacing: 0pt)
  #show raw.line: it => {
    grid(
      columns: (0em, 1fr),
      column-gutter: 0.2em,
      inset: (bottom: code-line-spacing),
      [#align(right, text(fill: code-line-number-color, size: line-number-size)[#it.number])],
      //align: (right + horizon, left + top),
      //[#text(fill: code-line-number-color, size: line-number-size)[#it.number]],
      [#it.body],
    )
  }
  #body
]
// Trim only the rendered source so trailing blank lines remain untouched on disk.
#let listing(path, lang: "cpp") = codebox(raw(read(path).trim(at: end), lang: lang, block: true))
#let sh(path) = listing(path, lang: "bash")
#let py(path) = listing(path, lang: "python")
#let txt(path) = listing(path, lang: none)

// ---- math helpers (Typst requires multi-letter bare words to resolve to
// a binding; these stand in for LaTeX's un-\text'd multi-letter variables) ----
#let DP = math.italic("dp")
#let pos = math.italic("pos")
#let tight = math.italic("tight")
#let property = math.italic("property")
#let lcm = math.op("lcm")

// ---- grid scratch-paper block (replaces the tikzpicture grid overlays) ----
#let gridcell = square(size: 0.5cm, stroke: 0.3pt + rgb("#b0b0b0"))
#let gridpat = tiling(size: (0.5cm, 0.5cm))[#gridcell]
#let gridbox(h) = rect(width: 100%, height: h, fill: gridpat, stroke: none)

// ---- small numeric table helper (Catalan / Fibonacci style) ----
#let numtable(rows) = table(
  columns: 5,
  stroke: none,
  align: (right, left, left, left, left),
  inset: (x: 6pt, y: 2pt),
  table.vline(x: 1, stroke: 0.4pt),
  ..rows.map(r => r.map(v => [#v])).flatten()
)

// ---- Table of contents, then body — both flow through the same 2-col layout ----
#show outline.entry.where(level: 1): it => {
  v(table-of-contents-section-spacing, weak: true)
  text(size: table-of-contents-size, weight: "bold", it)
}
#show outline.entry.where(level: 2): it => {
  v(table-of-contents-entry-spacing, weak: true)
  text(size: table-of-contents-size, it)
}

#columns(2, gutter: 12pt)[

#outline(title: none, indent: 1.2em, depth: 2)

= Reminder

== Observations and Tricks

- Contribution Technique
- 二分圖/Spanning Tree/DFS Tree
- 行、列操作互相獨立
- 奇偶性
- 當 $s, t$ 遞增並且 $t = f(s)$，對 $s$ 二分搜不好做，可以改成對 $t$ 二分搜，再算 $f(t)$
- 啟發式合併
- Permutation Normalization（做一些平移對齊兩個 permutation）
- 枚舉 $a_1 tilde.op a_n$ 再枚舉 $a_n tilde.op a_1$ 可以包在一個迴圈
- 兩個凸型函數相加還是凸型函數，相減不一定
- 一個區間的 mex $= k$，表示這個區間包含 $0 tilde.op k - 1$ 所有數字，並且「$U -$ 區間」的最小值 $= k$。

== Bug List

- 沒開 long long
- 陣列戳出界／陣列開不夠大
- 寫好的函式忘記呼叫
- 0-base / 1-base
- 忘記初始化
- \=\= 打成 \=
- \<= 打成 \<+
- dp[i] 從 dp[i-1] 轉移時忘記特判 i > 0
- std::sort 比較運算子寫成 < 或是讓 = 的情況為 true
- 漏 case
- 線段樹改值懶標初始值不能設為 0
- DFS 的時候不小心覆寫到全域變數
- 浮點數誤差
- unsigned int128
- 多筆測資不能沒讀完直接 return
- 記得刪 cerr
- vector 超級肥，小 vector 請用 array，例如矩陣快速冪

#gridbox(11cm)

= Init (Linux)

開場流程：

#sh("code/basic/開場流程 (Linux).sh")

== vimrc

#sh("code/basic/vimrc")

== run.sh

#sh("code/basic/run.sh")

= Basic

== PBDS

#listing("code/basic/PBDS.cpp")

== Random

#listing("code/basic/Random.cpp")

= Python

== I/O

#py("code/python/PythonIO.py")

== Decimal

#py("code/python/PythonDecimal.py")

= Data Structure

== CDQ

#listing("code/data-structure/CDQ.cpp")

== Mo's Algorithm

#listing("code/data-structure/Mo-algorithm.cpp")

== Heavy Light Decomposition

#listing("code/data-structure/HLD-Ian.cpp")

== Leftist Heap

#listing("code/data-structure/leftist-heap.cpp")

== Persistent Treap

#listing("code/data-structure/persistent-treap.cpp")

== Li Chao Tree

#listing("code/data-structure/li-chao-tree.cpp")

== Time Segment Tree

#listing("code/data-structure/time-segtree.cpp")

= DP

- 區間 DP
  - 狀態：$DP[l][r]$ = 區間 $[l,r]$ 的最佳值/方案數
  - 轉移：枚舉劃分點 $k$
  - 思考：是否滿足四邊形不等式、Knuth 優化可加速
- 背包 DP
  - 狀態：$DP[i][w]$ = 前 $i$ 個物品容量 $w$ 的最佳值
  - 判斷是 0/1、多重、分組 $=>$ 決定轉移方式
  - 若容量大 $=>$ bitset / 數學變形 / meet-in-the-middle
- 樹形 DP
  - 狀態：$DP[u]["flag"]$ = 子樹 $u$ 的最佳值
  - 合併子樹資訊 $=>$ 小到大合併 / 捲積式轉移
  - 注意 reroot 技巧（dp on tree + dp2 上傳）
- 數位 DP
  - 狀態：$(pos, tight, property)$
  - tight 控制是否貼上界
  - property 常為「餘數、數字和、相鄰限制」
- 狀壓 DP
  - 狀態：$DP["mask"]["last"]$
  - 常見於 TSP / Hamiltonian path / 覆蓋問題
  - $n <= 20$ 可做，否則要容斥 / FFT
- 期望 / 機率 DP
  - 狀態 $E[s]$ = 從狀態 $s$ 到終點的期望
  - 式子：$E[s] = c + sum P(s -> s') E[s']$
  - 線性期望：能拆就拆，少算分布
  - 輸出 mod $=>$ 分數化 $=>$ 模逆元
- 計數 DP / 組合數
  - 狀態表示方案數，常搭配「模數取餘」
  - 若轉移是捲積型 $=>$ FFT/NTT 加速
  - 若能公式化（Catalan / Ballot / Stirling） $=>$ 直接套公式
- 優化 DP
  - 判斷轉移方程 $DP[i] = min_j (DP[j] + C(j,i))$ 的性質
  - 單調性 $=>$ 分治優化
  - 凸性 $=>$ Convex Hull Trick / 斜率優化
  - 四邊形不等式 $=>$ Knuth 優化

== Aliens

#listing("code/dp/Aliens.cpp")

== SOS DP

#listing("code/dp/SOS_DP.cpp")

== 期望 DP (Expected Value DP)

- 狀態設計：$E[s]$ = 從狀態 $s$ 出發到終點的期望值
- 列式子：$E[s] = "(當前代價)" + sum_(s') P(s -> s') dot E[s']$
- 若存在自環，把 $E[s]$ 移到左邊，整理成 $(1 - P(s -> s)) E[s] = c + sum_(s' != s) P(s -> s') dot E[s']$
- 線性期望技巧：能拆就拆，避免處理整個分布
- 輸出 mod 時，分母要用模逆元：$q^(-1) equiv q^(M-2) (mod M)$（質數模數）

*常見題型*

- 擲骰子遊戲（到達終點的期望步數）
- 隨機遊走 hitting time
- 重複試驗直到成功
- 博弈遊戲的期望值
- 機率 DP：計算到某步時在某狀態的機率

*範例：擲骰子到 $n$ 格*

$ E[i] = 1 + 1/6 sum_(d=1)^6 E[i+d], quad (i<n), quad E[n] = 0 $

#listing("code/dp/dice_expectation.cpp")

== 數位 DP (Digit DP)

- 狀態：$(pos, tight, property)$
  - $pos$ = 當前處理到第幾位
  - $tight$ = 是否受限於上界 $N$
  - $property$ = 額外屬性（如數位和、餘數、相鄰限制…）
- 遞迴：枚舉當前位數字，遞迴下一位
- 終止條件：$pos == "長度"$ $=>$ 回傳屬性是否滿足
- 記憶化：$DP[pos][tight][property]$

*常見題型*

- 計算 $[0,N]$ 中數位和可被 $k$ 整除的數字個數
- 不含連續相同數字的數字個數
- 含特定數字次數的數字個數
- 位數和 / 餘數 / mod pattern

*範例：計算 $[0,N]$ 中數位和 $mod k = 0$ 的數字個數*

$ DP[pos][tight]["sum mod " k] $

#listing("code/dp/digit_dp_sum_mod.cpp")

= Graph

== Blossom

#listing("code/graph/Blossom.cpp")

== Weighted Blossom

#listing("code/graph/WeightedBlossom.cpp")

== Max Clique

#listing("code/graph/MaxClique.cpp")

== Bellman-Ford + SPFA

#listing("code/graph/BellmanFord + SPFA.cpp")

== BCC - AP

#listing("code/graph/BCC-AP.cpp")

== BCC - Bridge

#listing("code/graph/BCC-Bridge.cpp")

== SCC - Tarjan with 2-SAT

#listing("code/graph/2SAT-SCC.cpp")

== Eulerian Path - Undir

#listing("code/graph/EulerianPath-Undir.cpp")

== Eulerian Path - Dir

#listing("code/graph/EulerianPath-Dir.cpp")

== Kth Shortest Path

#listing("code/graph/KSP.cpp")

== System of Difference Constraints

#listing("code/graph/DiffConstraints.cpp")

- $x_u - x_v <= c =>$ `add(v, u, c)`
- $x_u - x_v >= c =>$ `add(u, v, -c)`
- $x_u - x_v = c =>$ `add(v, u, c), add(u, v -c)`
- $x_u >= c =>$ add super vertex $x_0 = 0$, then $x_u - x_0 >= c$ $=>$ `add(u, 0, -c)`
- Don't for get non-negative constraints for every variable if specified implicitly.
- Interval sum $=>$ Use prefix sum to transform into differential constraints. Don't for get $S_(i+1) - S_i >= 0$ if $x_i$ needs to be non-negative.
- $x_u/x_v <= c =>$ $log x_u - log x_v <= log c$

= String

  == Rolling Hash
  #listing("code/string/RollingHash.cpp")

  == Trie
  #listing("code/string/Trie.cpp")

  == KMP
  #listing("code/string/KMP.cpp")

  == Z Value
  #listing("code/string/Zval.cpp")

  == Manacher
  #listing("code/string/Manacher.txt")

  == Suffix Array
  #listing("code/string/SA-Optimized.cpp")

  == Suffix Automaton
  #listing("code/string/SAM.cpp")

  == SA-IS
  #listing("code/string/SA-IS.cpp")

  == Minimum Rotation
  #listing("code/string/MinRotation.cpp")

  == Aho Corasick
  #listing("code/string/ACAutomaton.txt")




= Geometry

== Template

#listing("code/geometry/GeometryDefault.cpp")

== Basic Operations

#listing("code/geometry/InPoly.cpp")
#listing("code/geometry/SortByAngle.cpp")
#listing("code/geometry/LineIntersectCheck.cpp")
#listing("code/geometry/LineIntersection.cpp")
#listing("code/geometry/ConvexHull.cpp")
#listing("code/geometry/PolygonArea.cpp")

== Lower Concave Hull

#listing("code/geometry/LowerConcaveHull.cpp")

== Pick's Theorem

Consider a polygon which vertices are all lattice points.

Let $i$ = number of points inside the polygon.

Let $b$ = number of points on the boundary of the polygon.

Then we have the following formula:

$ "Area" = i + b/2 - 1 $

== Minimum Enclosing Circle

#listing("code/geometry/MinEnclosingCircle.cpp")

== PolyUnion

#listing("code/geometry/PolyUnion.cpp")

== Minkowski Sum

#listing("code/geometry/MinkowskiSum.cpp")

= Number Theory

== Prime Sieve and Defactor

#listing("code/number-theory/PrimeSeive+Defactor.cpp")

== Harmonic Series

#listing("code/number-theory/Harmonic_Series.cpp")

== Count Number of Divisors

#listing("code/number-theory/Number_of_Divisors.cpp")

== 數論分塊

#listing("code/number-theory/數論分塊.cpp")

== Pollard's rho

#listing("code/number-theory/PollardRho.cpp")
#py("code/number-theory/PollardRho.py")

== Miller Rabin

#listing("code/number-theory/MillerRabin.cpp")

== Discrete Log

#listing("code/number-theory/DiscreteLog.cpp")

== Discrete Sqrt

#listing("code/number-theory/DiscreteSqrt.cpp")

== Fast Power

Note: $a^n equiv a^((n mod (p-1))) (mod p)$

== Extend GCD

#listing("code/number-theory/ExtGCD.cpp")

== Mu + Phi

#listing("code/number-theory/Mu + Phi.cpp")

== Other Formulas

- Pisano Period: 任何線性遞迴（比如費氏數列）模任何一個數字 $M$ 都會循環，找循環節 $pi(M)$ 先質因數分解 $M = product p_i^(e_i)$，然後 $pi(M) = lcm(pi(p_i^(e_i)))$，
- Inversion: \
  $a a^(-1) equiv 1 (mod m)$. $a^(-1)$ exists iff $gcd(a,m)=1$.
- Linear inversion: \
  $a^(-1) equiv (m - floor(m/a)) times (m mod a)^(-1) (mod m)$
- Fermat's little theorem: \
  $a^p equiv a (mod p)$ if $p$ is prime.
- Euler function: \
  $phi(n)=n product_(p|n) (p-1)/p$
- Euler theorem: \
  $a^(phi(n)) equiv 1 (mod n)$ if $gcd(a,n) = 1$. If a, n are not coprime: 質因數分解 $n = product p_i^(e_i)$，對每個 $p_i^(e^i)$ 分開看他們跟 $a$ 是否互質（互質：Fermat／不互質：夠大的指數會直接削成 $0$），最後用 CRT 合併。
- Extended Euclidean algorithm: \
  $a x+b y=gcd(a,b)=gcd(b, a mod b)=gcd(b, a-floor(a/b) b)=b x_1+(a-floor(a/b) b) y_1=a y_1+b(x_1-floor(a/b) y_1)$
- Divisor function: \
  $sigma_x (n) = sum_(d|n) d^x$. $n=product_(i=1)^r p_i^(a_i)$. \
  $sigma_x (n)=product_(i=1)^r (p_i^((a_i+1)x)-1)/(p_i^x-1)$ if $x != 0$. $sigma_0 (n)=product_(i=1)^r (a_i+1)$.
- Chinese remainder theorem (Coprime Moduli): \
  $x equiv a_i (mod m_i)$. \
  $M=product m_i$. $M_i=M/m_i$. $t_i=M_i^(-1)$. \
  $x = k M + sum a_i t_i M_i$, $k in bb(Z)$.
- Chinese remainder theorem: \
  $x equiv a_1 (mod m_1), x equiv a_2 (mod m_2) => x = m_1 p + a_1 = m_2 q + a_2 => m_1 p - m_2 q = a_2 - a_1$ \
  Solve for $(p, q)$ using ExtGCD. \
  $x equiv m_1 p + a_1 equiv m_2 q + a_2 (mod lcm(m_1, m_2))$
- Avoiding Overflow: $c a mod c b = c(a mod b)$
- Dirichlet Convolution: $(f * g)(n) = sum_(d|n) f(n)g(n/d)$
- Important Multiplicative Functions + Properties:
  + $epsilon(n) = [n = 1]$
  + $1(n) = 1$
  + $italic("id") (n) = n$
  + $mu(n) = 0$ if $n$ has squared prime factor
  + $mu(n) = (-1)^k$ if $n = p_1 p_2 dots.h.c p_k$
  + $epsilon = mu * 1$
  + $phi = mu * italic("id")$
  + $[n=1] = sum_(d|n) mu(d)$
  + $[gcd=1] = sum_(d|gcd) mu(d)$
- Möbius inversion: $f = g * 1 <=> g = f * mu$

== Polynomial

#listing("code/number-theory/Polynomial.cpp")

== Counting Primes

#listing("code/new-number-theory/counting_primes.cpp")

== Linear Sieve for Other Number Theoretic Functions

#listing("code/new-number-theory/linear_sieve.cpp")

= Linear Algebra

== Gaussian-Jordan Elimination

#listing("code/linear-algebra/GaussElimination.cpp")

== Determinant

+ Use GJ Elimination, if there's any row consists of only 0, then det = 0, otherwise det = product of diagonal elements.
+ Properties of det:
  - Transpose: Unchanged
  - Row Operation 1 - Swap 2 rows: $-det$
  - Row Operation 2 - $k accent(r_i, arrow)$: $k times det$
  - Row Operation 3 - $k accent(r_i, arrow)$ add to $accent(r_j, arrow)$: Unchanged

= Flow / Matching

== Flow Methods

#txt("code/flow/FlowMethod.txt")

== Dinic

#listing("code/flow/Dinic.cpp")

== ISAP

#listing("code/flow/ISAP.cpp")

== Bounded Max Flow

#listing("code/flow/BoundedMaxFlow.cpp")

== MCMF

#listing("code/flow/MCMF.cpp")

== Hopcroft-Karp

#listing("code/flow/HopcroftKarp.cpp")

== Cover / Independent Set

#txt("code/flow/CoverIndepend.txt")

== Kuhn Munkres

#listing("code/flow/KM2.cpp")

= Combinatorics

== Catalan Number

$ C_0=1, C_n=sum_(i=0)^(n-1) C_i C_(n-1-i), C_n=C_n^(2n)-C_(n-1)^(2n) $

#align(center)[#numtable((
  (0, 1, 1, 2, 5),
  (4, 14, 42, 132, 429),
  (8, 1430, 4862, 16796, 58786),
  (12, 208012, 742900, 2674440, 9694845),
))]

== Bertrand's Ballot Theorem

- $A$ always $> B$: $C(p+q, p) - 2 C(p+q-1, p)$
- $A$ always >= $B$: $C(p+q, p) times (p + 1 - q)/(p + 1)$

== Burnside's Lemma

Let $X$ be the original set.

Let $G$ be the group of operations acting on $X$.

Let $X^g$ be the set of $x$ not affected by $g$.

Let $X"/"G$ be the set of orbits.

Then the following equation holds:

$ |X"/"G| = 1/(|G|) sum_(g in G) |X^g| $

= Special Numbers

== Fibonacci Series

#align(center)[#numtable((
  (1, 1, 1, 2, 3),
  (5, 5, 8, 13, 21),
  (9, 34, 55, 89, 144),
  (13, 233, 377, 610, 987),
  (17, 1597, 2584, 4181, 6765),
  (21, 10946, 17711, 28657, 46368),
  (25, 75025, 121393, 196418, 317811),
  (29, 514229, 832040, 1346269, 2178309),
  (33, 3524578, 5702887, 9227465, 14930352),
))]

$f(45) approx 10^9, f(88) approx 10^18$

== Prime Numbers

- $pi(n) equiv$ Number of primes $<= n approx n/((ln n) - 1)$ \
  $pi(100) = 25, pi(200) = 46$ \
  $pi(500) = 95, pi(1000) = 168$ \
  $pi(2000) = 303, pi(4000) = 550$ \
  $pi(10^4) = 1229, pi(10^5) = 9592$ \
  $pi(10^6) = 78498, pi(10^7) = 664579$

#gridbox(20cm)

]
