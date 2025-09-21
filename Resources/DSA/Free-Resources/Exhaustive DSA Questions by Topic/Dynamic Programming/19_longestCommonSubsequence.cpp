#include <bits/stdc++.h>
using namespace std;

int memoize(int i1, int i2, string s1, string s2, vector<vector<int>>& dp){
    if(i1 < 0 || i2 < 0){
        return 0;
    }
    if(s1[i1] == s2[i2]){
        return dp[i1][i2] = 1 + memoize(i1-1, i2-1, s1, s2, dp);
    }
    return dp[i1][i2] = max(memoize(i1-1, i2, s1, s2, dp), memoize(i1, i2-1, s1, s2, dp));
}

int tabulate(string s1, string s2){
    int n = s1.length(), m = s2.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[n][m];
}

int spaceOptimal(string s1, string s2){
    // Optimize into two arrays using previous and current states
    int n = s1.length(), m = s2.length();
    vector<int> prev(m+1, 0);
    vector<int> cur(m+1, 0);
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(s1[i-1] == s2[j-1]){
                cur[j] = 1 + prev[j-1];
            }
            else{
                cur[j] = max(prev[j], cur[j-1]);
            }
        }
        prev = cur;
    }
    return prev[m];
}

int spaceOptimalSingleArray(string s1, string s2){
    // Optimize into single array using current dp array and storing prev[j-1] in variable diag
    int n = s1.length(), m = s2.length();
    vector<int> dp(m+1, 0);
    for(int i = 1; i<=n; i++){
        int diag = 0;
        for(int j = 1; j<=m; j++){
            int temp = dp[j];
            if(s1[i-1] == s2[j-1]){
                dp[j] = 1 + diag;
            }
            else{
                dp[j] = max(dp[j], dp[j-1]);
            }
            diag = temp;
        }
    }
    return dp[m];
}

int main(){
    string s1 = "plasma";
    string s2 = "altruism";
    int n = s1.length(), m = s2.length();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << "LCS via memoization: " << memoize(n-1, m-1, s1, s2, dp) << endl;
    cout << "LCS via tabulation: " << tabulate(s1, s2) << endl;
    cout << "LCS via space optimization: " << spaceOptimal(s1, s2) << endl;
    cout << "LCS via space optimization single array: " << spaceOptimalSingleArray(s1, s2) << endl;
    return 0;
}