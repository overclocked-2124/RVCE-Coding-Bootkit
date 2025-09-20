#include <bits/stdc++.h>
using namespace std;

int memoize(int ind, int T, vector<int>& a, vector<vector<int>>& dp){
    if(ind == 0){
        if(T%a[ind] == 0){
            return T/a[ind];
        }
        else return 1e8;
    }
    if(dp[ind][T] != -1) return dp[ind][T];
    int nt = 0 + memoize(ind-1, T, a, dp);
    int t = 1e8;
    if(a[ind] <= T) t = 1 + memoize(ind, T-a[ind], a, dp);
    return dp[ind][T] = min(t, nt);
}

int tabulate(int n, int T, vector<int>& a){
    vector<vector<int>> dp(n, vector<int>(T+1, 1e8));
    for(int i = 0; i<=T; i++){
        if(i%a[0] == 0) dp[0][i] = i/a[0];
    }
    for(int i = 1; i<n; i++){
        for(int j = 0; j<=T; j++){
            int nt = dp[i-1][j];
            int t = 1e8;
            if(a[i]<=j) t = 1 + dp[i][j-a[i]];
            dp[i][j] = min(t, nt);
        }
    }
    return dp[n-1][T];
}

int spaceOptimal(int n, int T, vector<int>& a){
    vector<int> dp(T+1, 1e8);
    vector<int> cur(T+1, 1e8);
    for(int i = 0; i<T; i++){
        if(i%a[0] == 0) dp[i] = i/a[0];
    }
    for(int i = 1; i<n; i++){
        for(int j = 0; j<=T; j++){
            int nt = dp[j];
            int t = 1e8;
            if(a[i]<=j) t = 1 + cur[j-a[i]];
            cur[j] = min(t, nt);
        }
        dp = cur;
    }
    return dp[T];
}

int main(){
    vector<int> a = {1, 5, 7};
    int T = 11;
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(T+1, -1));
    cout << "Memoization: " << memoize(n-1, T, a, dp) << endl;
    cout << "Tabulation: " << tabulate(n, T, a) << endl;
    cout << "Space Optimization: " << spaceOptimal(n, T, a) << endl;
    return 0;
}