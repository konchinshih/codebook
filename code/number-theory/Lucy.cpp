template<class T, class F>
pair<vector<T>, vector<T>> Lucy(const i64 N, const F f) {
  const i64 sqrtN = sqrtl(N);
  vector<T> Sl(sqrtN + 1);
  vector<T> Sh(sqrtN + 1);
  for (int i = 1; i <= sqrtN; i++) {
    Sl[i] = f(i) - 1;
    Sh[i] = f(f64(N) / i) - 1;
  }
  for (const int &p : primes) {
    const i64 pp = i64(p) * p;
    if (pp > N) break;
    const int R = min(sqrtN, N / pp);
    const int M = sqrtN / p;
    const auto pi = Sl[p - 1];
    const auto fp = Sl[p] - Sl[p - 1]; 
    for (int i = 1; i <= M; i++) Sh[i] -= fp * (Sh[i * p] - pi);
    for (int i = M + 1; i <= R; i++) Sh[i] -= fp * (Sl[N / (f64(i) * p)] - pi);
    for (int i = sqrtN; i >= pp; i--) Sl[i] -= fp * (Sl[i / p] - pi);
  } 
  return {Sl, Sh};
}
