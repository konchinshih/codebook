Pt bisector(Pt a, Pt b, Pt c) { Pt s = b-a, t = c-a;
  t = t * abs(s) / abs(t); return s + t; }