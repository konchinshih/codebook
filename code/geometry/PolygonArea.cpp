// Author: Gino
// Function: Return doubled area of a polygon
T dbarea(vector<Pt>& e) {
ll res = 0;
for (int i = 0; i < (int)e.size(); i++)
    res += e[i]^e[(i+1)%SZ(e)];
return abs(res);
}
