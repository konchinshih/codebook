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
    #let gutter = 2pt
    #layout(size => context {
      let title = text(size: heading2-size, weight: "bold")[#counter(heading).display() #h(0.4em) #it.body]
      let hash = heading-hash.get()
      if hash != none {
        let hash-content = text(size: hash-size, weight: "bold", fill: hash-color, font: "CodeNewRoman Nerd Font Propo")[#hash]
        let hash-w = measure(hash-content).width
        let title-w = size.width - hash-w - gutter
        let title-h = measure(box(width: title-w, title)).height
        let line-h = measure(text(size: heading2-size, weight: "bold")[X]).height
        let wrapped = title-h > line-h * 1.5
        grid(
          columns: (1fr, auto),
          column-gutter: gutter,
          align: (left + top, right + (if wrapped { bottom } else { horizon })),
          title, hash-content,
        )
      } else {
        title
      }
    })
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

#import "lib.typ": numtable

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

#let toc-content = outline(title: none, indent: 1.2em, depth: 2)
#let toc-gutter = 8pt
#layout(size => context {
  let col-width = (size.width - toc-gutter) / 2
  let h = measure(toc-content, width: col-width).height
  block(height: h / 2 + 2pt, columns(2, gutter: toc-gutter, toc-content))
})

= Reminder
  == Observations and Tricks
  #include "code/reminder/observations-and-tricks.typ"
  == Bug List
  #include "code/reminder/bug-list.typ"

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
  #sub("Time Segment Tree", "code/data-structure/time-segtree.cpp")
  #sub("Segment Tree Beats", "code/data-structure/segment-tree-beats.cpp")
  #sub("Range Affine SegT: Metadata", "code/data-structure/range-affine-metadata.cpp")
  #sub("Range Affine SegT", "code/data-structure/range-affine-segtree.cpp")
  #sub("Range Affine SegT: Binary Search", "code/data-structure/range-affine-binary-search.cpp")

= DP
  #sub("SOS DP", "code/dp/SOS_DP.cpp")
  #sub("Divide and Conquer DP", "code/dp/DivideAndConquerDP.cpp")
  == Dynamic DP
  #include "code/dp/dynamic-dp.typ"
  #sub("Convex Hull Trick", "code/dp/LineContainer.cpp")

  

= Graph
  #sub("Max Clique", "code/graph/MaxClique.cpp")
  #sub("Bellman-Ford", "code/graph/BellmanFord.cpp")
  == System of Difference Constraints
  #include "code/graph/difference-constraints.typ"
  == Graph Girth
  #include "code/graph/graph-girth.typ"
  #sub("Euler Trail", "code/graph/Eulerian.cpp")
  #sub("Vertex BCC (Round Square Tree)", "code/graph/VBCC.cpp")
  #sub("Edge BCC", "code/graph/EBCC.cpp")
  #sub("Kth Shortest Path", "code/graph/KSP.cpp")
  #sub("SCC - Tarjan", "code/graph/SCC.cpp")
  #sub("2SAT", "code/graph/2SAT.cpp")

= Tree
  #sub("Tree Isomorphism (Rooted Trees)", "code/tree/RootedTreeIsomorphism.cpp")
  == Tree Isomorphism (Unrooted Trees)
  #include "code/tree/tree-isomorphism.typ"
  #sub("Heavy Light Decomposition", "code/tree/HLD.cpp")
  #sub("Virtual Tree", "code/tree/VirtualTree.cpp")

= Matching
  #sub("Bipartite Matching", "code/matching/BipartiteMatching.cpp")
  #sub("Bipartite Weighted Matching", "code/matching/BipartiteWeightedMatching.cpp")
  #sub("General Matching", "code/matching/GeneralMatching.cpp")
  //#sub("General Weighted Matching", "code/matching/GeneralWeightedMatching.cpp")

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
  #include "code/string/ac-automaton-pattern-position.typ"

= Geometry
  #sub("Template", "code/geometry/default.cpp")
  #sub("Basic", "code/geometry/basic.cpp")
  #sub("Line / Segment Intersections", "code/geometry/Intersections.cpp")
  #sub("Point-Line / Segment Distance", "code/geometry/PointLineSegDist.cpp")
  #sub("Sort", "code/geometry/Sort.cpp")
  #sub("Convex Hull", "code/geometry/ConvexHull.cpp")
  #sub("Triangle Centers", "code/geometry/Heart.cpp")
  #sub("Point Inside", "code/geometry/PointInside.cpp")
  #sub("Point In Triangle", "code/geometry/PointInTriangle.cpp")
  #sub("Vector In Polygon", "code/geometry/VectorInPoly.cpp")
  #sub("Polygon Cut", "code/geometry/PolyCut.cpp")
  #sub("Half-Plane Intersection", "code/geometry/HalfPlaneIntersection.cpp")
  #sub("Cyclic Ternary Search", "code/geometry/CycTsearch.cpp")
  #sub("Circle Intersections", "code/geometry/CircleIntersections.cpp")
  #sub("Tangents", "code/geometry/Tangents.cpp")
  #sub("Bisector", "code/geometry/Bisector.cpp")
  #sub("Minimum Enclosing Circle", "code/geometry/Minimum_Enclosing_Circle.cpp")
  #sub("Minkowski Sum", "code/geometry/MinkowskiSum.cpp")
  #sub("Convex Hull Distance", "code/geometry/ConvexHullDist.cpp")
  #sub("Closest Point Pair", "code/geometry/ClosestPointPair.cpp")
  #sub("Polygon-Circle Intersection", "code/geometry/Intersection_of_Polygon_and_Circle.cpp")
  //#sub("Union of Circles", "code/geometry/Union_of_Circles.cpp")
  #sub("Union of Polygons", "code/geometry/Union_of_Polygons.cpp")
  #sub("Rotating Sweep Line", "code/geometry/RotatingSweepLine.cpp")
  //#sub("Delaunay Triangulation", "code/geometry/DelaunayTriangulation.cpp")
  //#sub("Voronoi", "code/geometry/Triangulation_Voronoi.cpp")
  //#sub("3D Point", "code/geometry/3DPoint.cpp")
  //#sub("3D Convex Hull", "code/geometry/3DConvexHull.cpp")
  == Pick's Theorem
  #include "code/geometry/picks-theorem.typ"

= Math Basic
  #sub("Basic", "code/math-basic/ModBasic.cpp")

= Number Theory
  #sub("Mod Sum / Floor Sum", "code/number-theory/ModSum.cpp")
  #sub("Mod Sqrt", "code/number-theory/ModSqrt.cpp")
  #sub("Discrete Log (exBSGS)", "code/number-theory/DiscreteLog.cpp")
  #sub("Miller Rabin", "code/number-theory/MillerRabin.cpp")
  #sub("Pollard Rho", "code/number-theory/PollardRho.cpp")
  == Linear Sieve
  #include "code/number-theory/linear-sieve.typ"
  #sub("Lucy (prime counting / prime sum)", "code/number-theory/Lucy.cpp")
  #sub("Black (Min25 sieve)", "code/number-theory/Black.cpp")
  #sub("Fast GCD", "code/number-theory/FastGCD.cpp")
  #sub("CRT", "code/number-theory/CRT.cpp")
  #sub("Extended Lucas", "code/number-theory/ExLucas.cpp")
  #sub("Divisor Block", "code/number-theory/DivisorBlock.cpp")
  == Formulas
  #include "code/number-theory/formulas.typ"

= Polynomial
  == Generating Functions
  #include "code/polynomial/generating-functions.typ"
  #sub("NTT", "code/polynomial/NTT.cpp")
  #sub("FFT", "code/polynomial/FFT.cpp")
  #sub("FFT Mod (arbitrary modulus)", "code/polynomial/FFTMod.cpp")
  #sub("FWHT", "code/polynomial/FWHT.cpp")
  #sub("Polynomial Operations", "code/polynomial/PolyOps.cpp")
  #sub("Berlekamp Massey", "code/polynomial/BerlekampMassey.cpp")
  #sub("Linear Recurrence (Kitamasa)", "code/polynomial/LinearRec.cpp")
  #sub("Lagrange Interpolation (iota points)", "code/polynomial/LagrangeIota.cpp")

= Linear Algebra
  #sub("Gauss (mod p)", "code/linear-algebra/Gauss.cpp")
  #sub("Solve Linear Equations", "code/linear-algebra/solveLinearEquations.cpp")
  #sub("Gauss (GF(2) / XOR basis)", "code/linear-algebra/GaussBinary.cpp")
  #sub("Solve Linear Equations (GF(2))", "code/linear-algebra/solveBinary.cpp")
  == Determinant
  #include "code/linear-algebra/determinant.typ"

= Numerical
  #sub("Integrate (Simpson / adaptive)", "code/numerical/Integrate.cpp")
  == Linear Programming
  #include "code/numerical/linear-programming.typ"
  #sub("Simplex", "code/numerical/Simplex.cpp")

= Combinatorics
  == Catalan Number
  #include "code/combinatorics/catalan-number.typ"

  == Bertrand's Ballot Theorem
  #include "code/combinatorics/bertrands-ballot-theorem.typ"

  == Burnside's Lemma
  #include "code/combinatorics/burnsides-lemma.typ"

  == Binomial Identities
  #include "code/combinatorics/binomial-identities.typ"
  == Stirling Numbers
  #include "code/combinatorics/stirling-numbers.typ"
  == Derangement / Inclusion-Exclusion
  #include "code/combinatorics/derangement.typ"
  == Pólya (necklaces)
  #include "code/combinatorics/polya.typ"

= Game Theory
  == Nim
  #include "code/game-theory/nim.typ"
  == Sprague-Grundy
  #include "code/game-theory/sprague-grundy.typ"

= Special Numbers
  == Fibonacci Series
  #include "code/special-numbers/fibonacci-series.typ"

  == Prime Numbers
  #include "code/special-numbers/prime-numbers.typ"

  == Number of Divisors
  #include "code/special-numbers/number-of-divisors.typ"

  == Distinct Prime Factors
  #include "code/special-numbers/distinct-prime-factors.typ"

#gridbox(1fr)

]
