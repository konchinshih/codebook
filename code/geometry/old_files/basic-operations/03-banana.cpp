// Dependency: 02, check if (a--b) (c--d) banana
bool banana(Pt a, Pt b, Pt c, Pt d) {
  if (onseg(a, c, d) || onseg(b, c, d) ||
      onseg(c, a, b) || onseg(d, a, b)) return true;
  return ori(a, b, c) * ori(a, b, d) < 0 &&
         ori(c, d, a) * ori(c, d, b) < 0;
}
