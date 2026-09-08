// ori(a, b, c) >= 0, valid: "strict" angle from a-b to a-c
bool btwAngle(Pt a, Pt b, Pt c, Pt p, int strict) {
  return ori(a, b, p) >= strict &&
    ori(a, p, c) >= strict;
}
// whether vector{cur, p} is in order prv, cur, nxt
bool inside(Pt prv, Pt cur, Pt nxt, Pt p, int strict) {
  if (ori(cur, nxt, prv) >= 0)
    return btwAngle(cur, nxt, prv, p, strict);
  return !btwAngle(cur, prv, nxt, p, !strict);
}