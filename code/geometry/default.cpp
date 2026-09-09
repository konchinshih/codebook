using T = long long; // or double
const double eps = 1e-8;
int sgn(T x) { return (x > eps) - (x < -eps); }
struct Pt {
  T x = 0, y = 0;
  Pt operator+(Pt a) const { return {x + a.x, y + a.y}; }
  Pt operator-(Pt a) const { return {x - a.x, y - a.y}; }
  Pt operator*(T k) const { return {x * k, y * k}; }
  Pt operator/(T k) const { return {x / k, y / k}; }
  T operator*(Pt a) const { return x * a.x + y * a.y; }
  T operator^(Pt a) const { return x * a.y - y * a.x; }
  bool operator<(Pt a) const
  { return tie(x, y) < tie(a.x, a.y); }
  bool operator==(Pt a) const
  { return !sgn(x - a.x) && !sgn(y - a.y); }
  //friend ostream& operator<<(ostream& o, Pt a)
  //{ return o << "(" << a.x << ", " << a.y << ")"; }
};
struct Line { Pt a, b; }; // a -> b
T abs2(Pt a) { return a * a; }
double abs(Pt a) { return sqrt(abs2(a)); }
int ori(Pt o, Pt a, Pt b) // 1: CCW, -1: CW, 0: collinear
{ return sgn((a - o) ^ (b - o)); }