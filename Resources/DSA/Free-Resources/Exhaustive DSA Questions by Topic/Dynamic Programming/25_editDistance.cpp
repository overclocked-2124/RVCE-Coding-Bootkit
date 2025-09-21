#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, string s, string t, vector<vector<int>>& dp){
    if(i<0) return j+1;
    if(j<0) return i+1;
    if(dp[i][j] != -1) return dp[i][j];
    if(s[i] == t[j]) return dp[i][j] = memoize(i-1, j-1, s, t, dp);
    return dp[i][j] = 1 + min(memoize(i-1, j-1, s, t, dp), min(memoize(i-1, j, s, t, dp), memoize(i, j-1, s, t, dp)));
}

int tabulate(string s, string t){
    int n = s.length();
    int m  = t.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i = 0; i<=m; i++){
        dp[i][0] = i;
    }
    for(int j = 0; j<=m; j++){
        dp[0][j] = j;
    }
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(s[i-1] == t[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
            }
        }
    }
    return dp[n][m];
}

int spaceOptimal(string s, string t){
    int n = s.length();
    int m  = t.length();
    vector<int> prev(m+1, 0);
    vector<int> cur(m+1, 0);
    for(int j = 0; j<=m; j++){
        prev[j] = j;
    }
    for(int i = 1; i<=n; i++){
        cur[0] = i;
        for(int j = 1; j<=m; j++){
            if(s[i-1] == t[j-1]){
                cur[j] = prev[j-1];
            }
            else{
                cur[j] = 1 + min(prev[j-1], min(prev[j], cur[j-1]));
            }
        }
        prev = cur;
    }
    return prev[m];
}

int main(){
    string s = "horse";
    string t = "ros";
    int n = s.length();
    int m  = t.length();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << "Steps by memoization: " << memoize(n-1, m-1, s, t, dp) << endl;
    cout << "Steps by tabulation: " << tabulate(s, t) << endl;
    cout << "Steps by space optimization: " << spaceOptimal(s, t) << endl;
    return 0;
}