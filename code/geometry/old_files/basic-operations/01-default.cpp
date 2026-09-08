// Author: Gino
using T = long long;
const double eps = 1e-8, PI = acos(-1);
int sgn(T x) { return abs(x) < eps ? 0 : x < 0 ? -1 : 1; }
struct Pt {
  T x = 0, y = 0;
  Pt operator+(Pt a) { return {x+a.x, y+a.y}; }
  Pt operator-(Pt a) { return {x-a.x, y-a.y}; }
  T operator*(Pt a) { return x*a.x + y*a.y; }
  T operator^(Pt a) { return x*a.y - y*a.x; }  // 不要打反
  bool operator<(Pt a) { return tie(x, y) < tie(a.x, a.y); }
  bool operator==(Pt a) { return !sgn(x-a.x) && !sgn(y-a.y); }
  friend ostream& operator<<(ostream& o, Pt a) {
    return o << "(" << a.x << ", " << a.y << ")";
  }
};
Pt mv(Pt a, Pt b) { return b-a; }
T len2(Pt a) { return a*a; }
T dis2(Pt a, Pt b) { return (b-a)*(b-a); }
int ori(Pt o, Pt a, Pt b) { return sgn((a-o) ^ (b-o)); }
