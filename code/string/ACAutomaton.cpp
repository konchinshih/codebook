const int N = 1e3+5, MOD = 1e9+9;
int dp[N][N][15];
map<char,int> m;
int arr[N][4], fail[N], cnt[N], pos;
void insert(string &s){
	int now = 0;
	for(auto c : s){
		int &to = arr[now][m[c]];
		now = to ? to : to = ++pos;
	}
	cnt[now] = s.size(); }
void build(){
	queue<int> q;
	for(int i = 0;i < 4;i++)
		if(arr[0][i]) q.push(arr[0][i]);
	while(!q.empty()){
		int now = q.front(); q.pop();
		for(int i = 0;i < 4;i++){
			int &to = arr[now][i], tmp;
			if(to==0) to = arr[fail[now]][i];
			else{
				q.push(to), tmp = fail[now];
				while(tmp && !arr[tmp][i]) cnt[to] = max(cnt[to], cnt[arr[tmp][i]]),tmp = fail[tmp];
				fail[to] = arr[tmp][i];
				cnt[to] = max(cnt[to],cnt[arr[tmp][i]]);
}}}}
void match(string &s){
	int now = 0;
	for(int i = 0;i < s.size();i++){
		while(now && !arr[now][s[i]-'a']) now = fail[now];
		if(arr[now][s[i]-'a']) now = arr[now][s[i]-'a'];
		if(cnt[now] > 0){
			//FIND!
		}
}}
