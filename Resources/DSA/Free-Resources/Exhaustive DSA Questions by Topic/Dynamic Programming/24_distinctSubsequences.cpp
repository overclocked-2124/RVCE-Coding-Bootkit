#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, string s, string t, vector<vector<int>>& dp){
    if(j<0) return 1;
    if(i<0) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(s[i] == t[j]) return dp[i][j] = memoize(i-1, j-1, s, t, dp) + memoize(i-1, j, s, t, dp);
    return dp[i][j] = memoize(i-1, j, s, t, dp);
}

int tabulate(string s, string t){
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i = 0; i<=n; i++){
        dp[i][0] = 1;
    }
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(s[i-1] == t[j-1]){
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][m];
}

int spaceOptimal(string s, string t){
    int n = s.length();
    int m = t.length();
    vector<int> prev(m+1, 0);
    vector<int> cur(m+1, 0);
    prev[0] = 1;
    cur[0] = 1;
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(s[i-1] == t[j-1]){
                cur[j] = prev[j-1] + prev[j];
            }
            else{
                cur[j] = prev[j];
            }
        }
        prev = cur;
    }
    return prev[m];
}

int spaceOptimalSingleArray(string s, string t){
    int n = s.length();
    int m = t.length();
    vector<int> dp(m+1, 0);
    dp[0] = 1;
    for(int i = 1; i<=n; i++){
        for(int j = m; j>=0; j--){
            if(s[i-1] == t[j-1]){
                dp[j] = dp[j-1] + dp[j];
            }
            else{
                dp[j] = dp[j];
            }
        }
    }
    return dp[m];
}

int main(){
    string s = "babgbag";
    string t = "bag";
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << "No. of distinct subsequences using memoization: " << memoize(n-1, m-1, s, t, dp) << endl;
    cout << "No. of distinct subsequences using tabulation: " << tabulate(s, t) << endl;
    cout << "No. of distinct subsequences using space optimization: " << spaceOptimal(s, t) << endl;
    cout << "No. of distinct subsequences using space optimization single array: " << spaceOptimalSingleArray(s, t) << endl;
    return 0;
}