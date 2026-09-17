// Simpson integration has fourth-order error
// in the step size.
template<class F>
double simpsonPart(double a, double b, F& f) {
  double c = (a + b) / 2;
  return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
}

template<class F>
double simpson(double a, double b, F f, int n = 1000) {
  double h = (b - a) / (2 * n);
  double v = f(a) + f(b);
  for (int i = 1; i < 2 * n; i++)
    v += f(a + i*h) * (i&1 ? 4 : 2);
  return v * h / 3;
}

// Adaptive Simpson integration to absolute error eps.
template<class F>
double adaptiveSimpson(F& f, double a, double b,
                       double eps, double whole) {
  double c = (a + b) / 2;
  double left = simpsonPart(a, c, f);
  double right = simpsonPart(c, b, f);
  double sum = left + right;
  if (abs(sum - whole) <= 15 * eps ||
      b - a < 1e-10)
    return sum + (sum - whole) / 15;
  return adaptiveSimpson(f, a, c, eps / 2, left) +
         adaptiveSimpson(f, c, b, eps / 2, right);
}

template<class F>
double quad(double a, double b, F f, double eps = 1e-8) {
  return adaptiveSimpson(f, a, b, eps, simpsonPart(a, b, f));
}