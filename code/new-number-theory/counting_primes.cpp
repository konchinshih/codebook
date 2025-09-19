// prime_count — #primes in [1..n] (O(n^{2/3}) time, O(sqrt(n)) memory)

using u64 = unsigned long long;

static inline u64 prime_count(u64 n){
  if(n<=1) return 0;
  int v = (int)floor(sqrt((long double)n));
  int s = (v+1)>>1, pc = 0;
  vector<int> smalls(s), roughs(s), skip(v+1);
  vector<long long> larges(s);

  for(int i=0;i<s;++i){
    smalls[i]=i;
    roughs[i]=2*i+1;
    larges[i]=(long long)((n/roughs[i]-1)>>1);
  }

  for(int p=3;p<=v;p+=2) if(!skip[p]){
    int q = p*p;
    if(1LL*q*q > (long long)n) break;
    skip[p]=1;
    for(int i=q;i<=v;i+=2*p) skip[i]=1;

    int ns=0;
    for(int k=0;k<s;++k){
      int i = roughs[k];
      if(skip[i]) continue;
      u64 d = (u64)i * (u64)p;
      long long sub = (d <= (u64)v)
        ? larges[smalls[(int)(d>>1)] - pc]
        : smalls[(int)((n/d - 1) >> 1)];
      larges[ns] = larges[k] - sub + pc;
      roughs[ns++] = i;
    }
    s = ns;
    for(int i=(v-1)>>1, j=((v/p)-1)|1; j>=p; j-=2){
      int c = smalls[j>>1] - pc;
      for(int e=(j*p)>>1; i>=e; --i) smalls[i] -= c;
    }
    ++pc;
  }

  larges[0] += 1LL*(s + 2*(pc-1))*(s-1) >> 1;
  for(int k=1;k<s;++k) larges[0] -= larges[k];

  for(int l=1;l<s;++l){
    int q = roughs[l];
    u64 m = n / (u64)q;
    long long t = 0;
    int e = smalls[(int)((m/q - 1) >> 1)] - pc;
    if(e < l+1) break;
    for(int k=l+1;k<=e;++k) t += smalls[(int)((m/ (u64)roughs[k] - 1) >> 1)];
    larges[0] += t - 1LL*(e - l)*(pc + l - 1);
  }
  return (u64)(larges[0] + 1);
}
