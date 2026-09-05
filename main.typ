// ============================================================
//  NYCU_LLLemonade_Jam Codebook — converted from main.tex to Typst
// ============================================================

#let page-header-size = 6pt
#let page-number-size = 8pt

#let heading1-size = 12pt
// #let heading2-size = 11.5pt
#let heading2-size = 10pt
#let body-size = 9pt

#let code-size = 9pt
#let line-number-size = 6pt
#let code-line-number-color = rgb("#c0c7d2")
#let code-line-spacing = -0.3em
#let code-wrap-leading = 0.3em
#let hash-size = 6pt
#let hash-color = black

// ---- hash.sha256 lookup: "path" -> "sha256sum", parsed once at compile time ----
// Each line is "<right-padded path> <hash>"; the hash never contains spaces,
// so it's always the last whitespace-separated token on the line.
#let code-hashes = {
  let table = (:)
  for line in read("hash.sha256").split("\n") {
    let trimmed = line.trim()
    if trimmed == "" { continue }
    let parts = trimmed.split(" ")
    if parts.len() < 2 { continue }
    table.insert(parts.slice(0, -1).join(" "), parts.last())
  }
  table
}

#let table-of-contents-size = 7pt
#let table-of-contents-section-spacing = 0.5em
#let table-of-contents-entry-spacing = 0.3em


#let heading1-background = rgb("#c9c9c9")
#let heading2-background = rgb("#e3e3e3")


#set text(
  font: ("Libertinus Serif", "Anthropic Serif Text"),
  size: body-size,
)
#set raw(theme: "themes/codeblock-theme.tmTheme")


#let team = "NYCU_Trick_or_TREE"
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
  v(0.4em, weak: true)
  block(
    fill: heading1-background,
    width: 100%,
    inset: (x: 4pt, y: 2pt),
  )[
    #text(size: heading1-size, weight: "bold")[#counter(heading).display() #h(0.4em) #it.body]
  ]
  v(-0.25em)
}
// Set right before a heading whose title should carry a hash badge (see
// `sub` below), and cleared immediately after — read only by the level-2
// show rule, so it never leaks into outline()'s reuse of heading bodies.
#let heading-hash = state("codebook-heading-hash", none)

#show heading.where(level: 2): it => {
  v(0.3em, weak: true)
  block(
    fill: heading2-background,
    width: 100%,
    inset: (x: 4pt, y: 2pt),
  )[
    #text(size: heading2-size, weight: "bold")[#counter(heading).display() #h(0.4em) #it.body]
    #context {
      let hash = heading-hash.get()
      if hash != none {
        place(right + horizon, text(size: hash-size, weight: "bold", fill: hash-color, font: "CodeNewRoman Nerd Font Propo")[#hash])
      }
    }
  ]
  v(-0.25em)
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
  #set text(font: ("CodeNewRoman Nerd Font Propo", "Noto Serif TC"), size: code-size)
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

// ---- "== Title" + single-file listing, collapsed into one call ----
// Builds a normal (numbered, outlined) level-2 heading via heading(level: 2),
// so it goes through the same #show heading.where(level: 2) rule as a
// manually written "==" heading — only the hash overlay and language
// auto-detection are new.
#let lang-for(path) = {
  if path.ends-with(".py") { "python" }
  else if path.ends-with(".sh") { "bash" }
  else if path.ends-with(".txt") { none }
  else { "cpp" }
}
#let sub(title, path) = {
  let hash = code-hashes.at(path, default: none)
  let hash-short = if hash != none { hash.slice(0, 6) } else { none }
  heading-hash.update(hash-short)
  heading(level: 2)[#title]
  heading-hash.update(none)
  listing(path, lang: lang-for(path))
}

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
  - 寫好的函式（例如 `init()`、`build()`）忘記呼叫
  - 0-base / 1-base
  // - \=\= 打成 \=
  // - \<= 打成 \<+
  // - dp[i] 從 dp[i-1] 轉移時忘記特判 i > 0
  // - std::sort 比較運算子寫成 < 或是讓 = 的情況為 true
  // - 漏 case
  - 線段樹改值懶標初始值不能設為 0
  - DFS 的時候不小心覆寫到全域變數
  // - 浮點數誤差
  // - unsigned int128
  - 多筆測資不能沒讀完直接 return
  // - 記得刪 cerr
  - vector 超級肥，小 vector 請用 array，例如矩陣快速冪


= Init (Linux)
  == vimrc
  #sh("code/basic/vimrc")
  #sh("code/basic/vimrc-gino")
  #sub("bashrc", "code/basic/bashrc")


= Basic
  #sub("Template (Using Codebook)", "code/basic/template_codebook.cpp")
  #sub("PBDS, Random", "code/basic/PBDS_and_Random.cpp")
  #sub("Debug", "code/basic/debug.cpp")
  == SVG Writer
  #listing("code/basic/SVGWriter.cpp")
  #listing("code/basic/SVGWriterUsage.cpp")
  #sub("Python", "code/basic/Python.py")
  == Stress Tests
  #py("code/stress-test/gen.py")
  #sh("code/stress-test/test.sh")


= Data Structure
  #sub("Mo's Algorithm", "code/data-structure/Mo-algorithm.cpp")
  #sub("CDQ", "code/data-structure/CDQ.cpp")
  #sub("Persistent Treap", "code/data-structure/persistent-treap.cpp")
  #sub("Li Chao Tree", "code/data-structure/li-chao-tree.cpp")
//   目前這份 沒有支援線段／射線插入；insert(line x) 代表這條線在整個 \([0,\text{maxn})\) 都有效。

// 但這份結構很好改，直接外掛一個 range insert：

// void insert_seg(line x, int ql, int qr,
//                 int i = 1, int l = 0, int r = maxn) {
//     if (qr <= l || r <= ql) return;
//     if (ql <= l && r <= qr) {
//         insert(x, i, l, r);
//         return;
//     }
//     insert_seg(x, ql, qr, i << 1, l, m);
//     insert_seg(x, ql, qr, i << 1 | 1, m, r);
// }

// 這樣：

// insert_seg(L, l, r);     // L 只在 [l,r) 有效
// insert_seg(L, x, maxn);  // 向右射線
// insert_seg(L, 0, x + 1); // 向左射線（若 x 是整數且含端點）

// 複雜度大約變成

// $$ O(\log^2 C) $$

// 每次 segment insertion；point query 還是 \(O(\log C)\)。

// 不過你們這份還有一個值得修的地方：arr 是 global static，所以預設 line 是 \(y=0\)。如果合法答案可能是負數，空節點會錯誤貢獻 0。最好加 bool has[] 或初始化成真正的 \(-\infty\) line。
  #sub("Time Segment Tree", "code/data-structure/time-segtree.cpp")

= DP
  #sub("SOS DP", "code/dp/SOS_DP.cpp")
  #sub("Divide and Conquer DP", "code/dp/DivideAndConquerDP.cpp")
  == Dynamic DP
  - 適用情境：$d p_i = M_i dot d p_(i-1) arrow.double d p_i = M_i M_(i-1) dots.c M_1 d p_0$
  - 當 $M_i$ 需要動態修改，且 $M_i$ 是廣義矩陣乘法：

  $ C_(i j) = limits(op("⨁"))_k A_(i k) times.o B_(k j)
     $
  - 滿足 $(plus.o, times.o)$ 是半環（$times.o$ 對 $plus.o$ 有分配律、$times.o$ 和 $plus.o$ 有結合律、$plus.o$ 有交換律）
  - 此時便可用線段樹維護 $M_n M_(n-1) dots.c M_1$ 的乘積。線段樹上的 pos 是 $M_"pos"$，但 pull 時要 `st[idx] = mul(st[cr], st[cl])`

  

= Graph
  #sub("Max Clique", "code/graph/MaxClique.cpp")
  #sub("Bellman-Ford", "code/graph/BellmanFord.cpp")
  #sub("System of Difference Constraints", "code/graph/DiffConstraints.cpp")
  - $x_u - x_v <= c =>$ `add(v, u, c)`
  - $x_u - x_v >= c =>$ `add(u, v, -c)`
  - $x_u - x_v = c =>$ `add(v, u, c), add(u, v -c)`
  - $x_u >= c =>$ add super vertex $x_0 = 0$, then $x_u - x_0 >= c$ $=>$ `add(u, 0, -c)`
  - Don't for get non-negative constraints for every variable if specified implicitly.
  - Interval sum $=>$ Use prefix sum to transform into differential constraints. Don't for get $S_(i+1) - S_i >= 0$ if $x_i$ needs to be non-negative.
  - $x_u \/ x_v <= c =>$ $log x_u - log x_v <= log c$
  == Graph Girth
  Run BFS for every node, when encountered non-BFS-tree edge, update answer (min cycle length) with `dis[u] + dis[v] + 1`.  Time O(VE).
  #sub("Euler Trail", "code/graph/Eulerian.cpp")
  #sub("Vertex BCC (Round Square Tree)", "code/graph/VBCC.cpp")
  #sub("Edge BCC", "code/graph/EBCC.cpp")
  #sub("Kth Shortest Path", "code/graph/KSP.cpp")
  #sub("SCC - Tarjan", "code/graph/SCC.cpp")
  #sub("2SAT", "code/graph/2SAT.cpp")

= Tree
  #sub("Tree Isomorphism (Rooted Trees)", "code/tree/RootedTreeIsomorphism.cpp")
  == Tree Isomorphism (Unrooted Trees)
  Find the centroid(s) of $T_1$, $T_2$. \
  Case 1: $T_1, T_2$ have different number of centroids $->$ NO \
  Case 2: $T_1$ has centroid $c_1$, $T_2$ has centroid $c_2$ \
  $->$ $r o o t e d \_ i s o m o r p h i c(c_1, c_2)$ \
  Case 3: $T_1$ has centroids $c_1, c'_1$, $T_2$ has centroids $c_2, c'_2$ \
  $->$ $r o o t e d \_ i s o m o r p h i c(c_1, c_2)$ `||` $r o o t e d \_ i s o m o r p h i c(c'_1, c_2)$
  #sub("Heavy Light Decomposition", "code/tree/HLD.cpp")
  #sub("Virtual Tree", "code/tree/VirtualTree.cpp")

= Matching
  #sub("Bipartite Matching", "code/matching/BipartiteMatching.cpp")
  #sub("Bipartite Weighted Matching", "code/matching/BipartiteWeightedMatching.cpp")
  #sub("General Matching", "code/matching/GeneralMatching.cpp")
  #sub("General Weighted Matching", "code/matching/GeneralWeightedMatching.cpp")

= Flow
  #sub("Flow Methods", "code/flow/FlowMethod.txt")
  #sub("Dinic (Flow Decomposition)", "code/flow/Dinic.cpp")
  #sub("ISAP", "code/flow/ISAP.cpp")
  #sub("Bounded Max Flow", "code/flow/BoundedMaxFlow.cpp")
  #sub("MCMF", "code/flow/MCMF.cpp")
  #sub("Push-Relabel", "code/flow/PushRelabel.cpp")
  #sub("Gomory-Hu Tree", "code/flow/GomoryHuTree.cpp")
  #sub("Global Min Cut", "code/flow/StoerWagner.cpp")
  //== Cover / Independent Set
  //#txt("code/flow/CoverIndepend.txt")


= String
  #sub("Rolling Hash", "code/string/RollingHash.cpp")
  #sub("KMP", "code/string/KMP.cpp")
  #sub("Z Value", "code/string/Z.cpp")
  #sub("Manacher", "code/string/Manacher.cpp")
  #sub("Suffix Array + LCP", "code/string/SA.cpp")
  #sub("Suffix Automaton", "code/string/SAM.cpp")
  #sub("Minimum Rotation", "code/string/MinRotation.cpp")
  #sub("AC Automaton", "code/string/AC.cpp")
  #sub("AC Automaton - Dict Links", "code/string/AC-DictLink.cpp")
  #sub("AC Automaton - Counting Patterns", "code/string/AC-CountPatterns.cpp")
  == AC Automaton - Pattern Position
  輸出每個 pattern 在 text 中第一次出現的位置，若不存在則輸出 -1。\
  走 AC 自動機時 `if (val[ptr] == -1) val[ptr] = i;` 接著 pull DP\
  `if (val[x] == -1) continue;`\
  `if (val[fail[x]] == -1) val[fail[x]] = val[x];`\
  `else val[fail[x]] = min(val[fail[x]], val[x]);`\



= Geometry
  #sub("Template", "code/geometry/GeometryDefault.cpp")
  == Basic Operations
  #listing("code/geometry/InPoly.cpp")
  #listing("code/geometry/SortByAngle.cpp")
  #listing("code/geometry/LineIntersectCheck.cpp")
  #listing("code/geometry/LineIntersection.cpp")
  #listing("code/geometry/ConvexHull.cpp")
  #listing("code/geometry/PolygonArea.cpp")
  #sub("Lower Concave Hull", "code/geometry/LowerConcaveHull.cpp")
  == Pick's Theorem
  Consider a polygon which vertices are all lattice points.\
  Let $i$ = number of points inside the polygon.\
  Let $b$ = number of points on the boundary of the polygon.\
  Then we have the following formula:\
  $ "Area" = i + b \/ 2 - 1 $
  #sub("Minimum Enclosing Circle", "code/geometry/MinEnclosingCircle.cpp")
  #sub("PolyUnion", "code/geometry/PolyUnion.cpp")
  #sub("Minkowski Sum", "code/geometry/MinkowskiSum.cpp")


= Number Theory
  #sub("Mod Sum", "code/new-number-theory/modSum.cpp")
  #sub("Extended Lucas Theorem", "code/new-number-theory/ex-lucas.cpp")
  #sub("Prime Sieve and Defactor", "code/number-theory/PrimeSeive+Defactor.cpp")
  #sub("Harmonic Series", "code/number-theory/Harmonic_Series.cpp")
  #sub("Count Number of Divisors", "code/number-theory/Number_of_Divisors.cpp")
  #sub("數論分塊", "code/number-theory/數論分塊.cpp")
  == Pollard's rho
  #listing("code/number-theory/PollardRho.cpp")
  #py("code/number-theory/PollardRho.py")
  #sub("Miller Rabin", "code/number-theory/MillerRabin.cpp")
  #sub("Discrete Log", "code/number-theory/DiscreteLog.cpp")
  #sub("Discrete Sqrt", "code/number-theory/DiscreteSqrt.cpp")
  == Fast Power
  Note: $a^n equiv a^((n mod (p-1))) (mod p)$
  #sub("Extend GCD", "code/number-theory/ExtGCD.cpp")
  #sub("Mu + Phi", "code/number-theory/Mu + Phi.cpp")

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

    #sub("Polynomial", "code/number-theory/Polynomial.cpp")
    #sub("Counting Primes", "code/new-number-theory/counting_primes.cpp")
    #sub("Linear Sieve for Other Number Theoretic Functions", "code/new-number-theory/linear_sieve.cpp")

// = Linear Algebra

// == Gaussian-Jordan Elimination
// #listing("code/linear-algebra/GaussElimination.cpp")

// == Determinant
// + Use GJ Elimination, if there's any row consists of only 0, then det = 0, otherwise det = product of diagonal elements.
// + Properties of det:
//   - Transpose: Unchanged
//   - Row Operation 1 - Swap 2 rows: $-det$
//   - Row Operation 2 - $k accent(r_i, arrow)$: $k times det$
//   - Row Operation 3 - $k accent(r_i, arrow)$ add to $accent(r_j, arrow)$: Unchanged

= Numerical
  == Polynomials and recurrences
  #listing("code/numerical/Polynomial.h")
  #listing("code/numerical/PolyRoots.h")
  #listing("code/numerical/PolyInterpolate.h")
  #listing("code/numerical/Lagrange-iota.h")
  #listing("code/numerical/BerlekampMassey.h")
  #listing("code/numerical/LinearRecurrence.h")
  == Optimization
  #listing("code/numerical/GoldenSectionSearch.h")
  #listing("code/numerical/HillClimbing.h")
  #listing("code/numerical/Integrate.h")
  #listing("code/numerical/IntegrateAdaptive.h")
  #listing("code/numerical/Simplex.h")
  == Matrices
  #listing("code/numerical/Determinant.h")
  #listing("code/numerical/IntDeterminant.h")
  #listing("code/numerical/SolveLinear.h")
  #listing("code/numerical/SolveLinear2.h")
  #listing("code/numerical/SolveLinearBinary.h")
  #listing("code/numerical/MatrixInverse.h")
  #listing("code/numerical/MatrixInverse-mod.h")
  #listing("code/numerical/Tridiagonal.h")
  == Fourier transforms
  // #listing("code/numerical/FastFourierTransform.h")
  #listing("code/numerical/FastFourierTransformMod.h")
  // #listing("code/numerical/NumberTheoreticTransform.h")
  #listing("code/numerical/FastSubsetTransform.h")



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
  Let $X$ be the original set.\
  Let $G$ be the group of operations acting on $X$.\
  Let $X^g$ be the set of $x$ not affected by $g$.\
  Let $X"/"G$ be the set of orbits.  Then the following equation holds:\
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
  
  == Number of Divisors
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

  == Distinct Prime Factors
  - Let $omega(n) =$ number of distinct prime factors.
  - Minimum number with $k$ distinct prime factors is the product
    of the first $k$ primes.
    - $2 dot 3 dot 5 dot 7 dot 11 dot 13 dot 17 dot 19 = 9699690$
    - $2 dot 3 dot ... dot 23 = 223092870$
    - $2 dot 3 dot ... dot 29 = 6469693230$
    - $n <= 10^9 => omega(n) <= 9$, $n <= 10^18 => omega(n) <= 15$
  - Number of square-free divisors $= 2^omega(n)$
    - $n <= 10^9 => <= 512$, $n <= 10^18 => <= 32768$

#gridbox(16cm)

]
