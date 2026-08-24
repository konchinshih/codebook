string s; // N 轉成字串，方便逐位處理
int k;    // 除數

// dp[pos][tight][sum_mod]
// pos   = 當前處理到哪一位 (0 = 最高位)
// tight = 是否仍受限於 N 的數字 (1 = 是, 0 = 否)
// sum_mod = 當前數位和 mod k 的值
long long dp[20][2][105]; 

// 計算: 從 pos 開始，tight 狀態下，數位和 mod k = sum_mod 的方案數
long long dfs(int pos, int tight, int sum_mod){
    // 終止條件：所有位數都處理完
    if(pos == (int)s.size())
        // 若數位和 mod k == 0，算作一個合法數字
        return (sum_mod % k == 0);

    // 記憶化查詢
    if(dp[pos][tight][sum_mod] != -1) 
        return dp[pos][tight][sum_mod];

    long long res = 0;
    // 如果 tight = 1，本位數字上限 = N 的該位數字
    // 如果 tight = 0，本位數字上限 = 9
    int limit = tight ? (s[pos]-'0') : 9;

    // 枚舉當前位可以填的數字
    for(int d=0; d<=limit; d++){
        // 下一位是否仍然 tight？
        int next_tight = (tight && d==limit);
        // 更新數位和 mod k
        int next_mod = (sum_mod + d) % k;
        res += dfs(pos+1, next_tight, next_mod);
    }

    // 存結果
    return dp[pos][tight][sum_mod] = res;
}

int main(){
    long long N; 
    cin >> N >> k;
    s = to_string(N); // 把 N 轉成字串，方便取每一位
    memset(dp,-1,sizeof(dp));
    cout << dfs(0,1,0) << "\n"; // 從最高位開始，初始 tight=1，sum=0
}
