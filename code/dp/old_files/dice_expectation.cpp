int main(){
    int n; 
    cin >> n; // 終點位置

    // E[i] = 從位置 i 走到終點的期望步數
    // 因為每次最多走 6，所以要開 n+6 以避免越界
    vector<double> E(n+7, 0.0);

    // 從終點往前推 (backward DP)
    for(int i=n-1; i>=0; i--){
        double sum=0;
        // 期望公式: E[i] = 1 + (E[i+1]+...+E[i+6]) / 6
        for(int d=1; d<=6; d++) sum += E[i+d];
        E[i] = 1 + sum/6.0;
    }

    // 輸出 E[0]，即從起點到終點的期望擲骰次數
    cout << fixed << setprecision(10) << E[0] << "\n";
}
