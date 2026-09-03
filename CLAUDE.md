# Codebook

ICPC team codebook for NYCU_LLLemonade_Jam. The document is a printed reference
(A4, 2-column, tiny font) assembled from small standalone snippet files under
`code/`. Being pulled straight from `main.tex` in the past, it is now being
migrated to Typst (`main.typ`) — `main.typ` is the source of truth going
forward; `main.tex` is kept only for reference/fallback.

## Repo structure

- `main.typ` — Typst source for the codebook. Defines page/heading styling,
  the `listing`/`sh`/`py`/`txt` helpers that pull in a `code/` file as a
  syntax-highlighted block, and the `sub(title, path)` helper that collapses a
  `== Title` heading + single-file listing into one call (auto-detects
  language from the file extension, and stamps the first 6 hex digits of the
  file's SHA-256 — from `hash.sha256` — into the heading's title row).
  Sections with prose, tables, math, or more than one listing under one
  heading stay hand-written with `==` + `#listing(...)`/`#sh(...)`/etc.
- `main.tex` — legacy LaTeX source (pre-Typst). Not actively maintained;
  `main.typ` is authoritative.
- `code/<topic>/` — one file per algorithm/snippet, grouped by topic
  (`basic`, `data-structure`, `dp`, `flow`, `geometry`, `graph`,
  `linear-algebra`, `matching`, `number-theory`, `new-number-theory`,
  `numerical`, `stress-test`, `string`, `tree`). `.cpp`/`.h` files are C++,
  `.py` Python, `.sh` shell, `.txt` plain/pseudocode. Each topic dir may have
  an `old_files/` subdir of retired snippets not referenced from `main.typ`.
- `hash.sha256` — generated lookup table (`path` → sha256sum) for every file
  under `code/`, produced by `hash.sh`. Regenerate it (`bash hash.sh`) after
  adding/renaming/editing files under `code/` — `main.typ` reads this file at
  compile time to render the hash badges, and a stale file just means some
  headings silently show no hash badge (not a compile error).
- `themes/` — `codeblock-theme.tmTheme` (raw/code syntax theme for Typst) and
  its palette JSON.
- `fonts/` — embedded fonts (serif body font, CodeNewRoman Nerd Font for
  code, Hiragino Mincho / Noto Serif TC for CJK) used via
  `--font-path fonts` at compile time.
- `Makefile` — see Testing below.
- `legacy/` — old, unrelated LaTeX drafts from previous team names/years.
  Not part of the current build.

## Adding a new snippet

1. Drop the file under the right `code/<topic>/` directory.
2. Reference it from `main.typ`: use `#sub("Title", "code/<topic>/File.ext")`
   for a plain single-listing section (preferred — gives numbering, TOC
   entry, and the hash badge for free), or fall back to a manual
   `== Title` + `#listing("...")` (or `#sh`/`#py`/`#txt`) if the section has
   prose, multiple listings, or non-code content alongside it.
3. Regenerate hashes: `bash hash.sh`.
4. Build and check the page count (see Testing below).

## Testing

Build the Typst document:

```
make typst
```

This runs `python3 make-palette.py && typst compile main.typ main.pdf --font-path fonts`.
Confirm it compiles with no errors (font-not-found warnings for the
CJK/serif/code fonts are expected in environments without those fonts
installed and can be ignored).

**Page budget: the printed codebook is capped at 25 pages** (ICPC page-limit
rule). After every build, check the resulting page count, e.g.:

```
pdfinfo main.pdf | grep Pages
```

**If the page count exceeds 25, warn the user explicitly** — do not silently
let it grow past the limit or trim content on your own to force it back
under 25 without asking.
