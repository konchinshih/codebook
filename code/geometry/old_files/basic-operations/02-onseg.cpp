bool onseg(Pt p, Pt a, Pt b) {
  return !ori(p, a, b) && sgn((a-p) * (b-p)) <= 0;
}
