// ---- small numeric table helper (Catalan / Fibonacci style) ----
#let numtable(rows) = table(
  columns: 5,
  stroke: none,
  align: (right, left, left, left, left),
  inset: (x: 6pt, y: 2pt),
  table.vline(x: 1, stroke: 0.4pt),
  ..rows.map(r => r.map(v => [#v])).flatten()
)
