// Author: Gino
// Function: Check if a point P sits in a polygon (doesn't have to be convex hull)
// 0 = Bound, 1 = In, -1 = Out
short inPoly(Pt p) {
for (int i = 0; i < n; i++)
    if (onseg(p, E[i], E[(i+1)%n])) return 0;
int cnt = 0;
for (int i = 0; i < n; i++)
    if (banana(p, Pt(p.x+1, p.y+2e9), E[i], E[(i+1)%n]))
        cnt ^= 1;
return (cnt ? 1 : -1);
}
