void count_sort(int pos[], int n, vector<int> &rank){
	int cnt[n] = {};
	for(int i = 0;i < n;i++) cnt[rank[pos[i]]]++;
	for(int i = 1;i < n;i++) cnt[i] += cnt[i-1];
	int ans[n];
	for(int i = n-1;~i;i--){
		ans[cnt[rank[pos[i]]]-1] = pos[i];
		--cnt[rank[pos[i]]];
	}
	for(int i = 0;i < n;i++) pos[i] = ans[i];
}
// 只需要在求完Suffix Array之後順便求LCP就好了
void get_suffix(string &s, int pos[], vector<int> &lcp){
	s += '$';
	int n = s.size();
	vector<int> rank(n);
	//k = 0
	iota(pos,pos+n,0);
	sort(pos,pos+n,[&](int a, int b){ return s[a] < s[b]; });
	for(int i = 0;i < n;i++){
		if(i==0){ 
			rank[pos[i]] = 0;
		}else{
			rank[pos[i]] = rank[pos[i-1]] + (s[pos[i]]!=s[pos[i-1]]);
		}
	}
	//k > 0
	vector<int> new_rank(n);
	for(int k = 0;(1<<k) < n;k++){
		for(int i = 0;i < n;i++)
			pos[i] = (pos[i] - (1<<k)%n + n ) % n;
		count_sort(pos,n,rank);
		new_rank[pos[0]] = 0;
		for(int i = 1;i < n;i++){
			pair<int,int> prev = {rank[pos[i-1]], rank[(pos[i-1]+(1<<k))%n]};
			pair<int,int> now = {rank[pos[i]], rank[(pos[i]+(1<<k))%n]};
			new_rank[pos[i]] = new_rank[pos[i-1]] + (prev!=now);
		}
		rank = new_rank;
	}
	//求LCP Array
	int k = 0;
	for(int i = 0;i < n;i++){
		int pi = rank[i];
		if (pi == 0) continue;
		int j = pos[pi-1];
		while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
		lcp[pi] = k;
		k = max(0,k-1);
	}
}
