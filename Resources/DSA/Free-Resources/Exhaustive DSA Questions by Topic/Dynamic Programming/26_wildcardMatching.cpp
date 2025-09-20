#include <bits/stdc++.h>
using namespace std;

bool memoize(int i, int j, string s, string p, vector<vector<int>>& dp){
    if(j<0 && i<0) return true;
    if(j<0 && i>=0) return false;
    if(i<0 && j>=0){
        for(int x = 0; x<=j; x++){
            if(p[x] != '*'){
                return false;
            }
        }
        return true;
    }
    if(dp[i][j] != -1) return dp[i][j];
    if(s[i] == p[j] || p[j] == '?'){
        return dp[i][j] = memoize(i-1, j-1, s, p, dp);
    }
    else if(p[j] == '*'){
        return dp[i][j] = (memoize(i-1, j, s, p, dp))|(memoize(i, j-1, s, p, dp));
    }
    else return dp[i][j] = false;
}

bool tabulate(string s, string p){
    int n = s.length();
    int m = p.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    dp[0][0] = 1;
    for(int i = 1; i<=n; i++){
        dp[i][0] = 0;
    }
    for(int j = 1; j<=m; j++){
        dp[0][j] = 1;
        for(int x = 0; x<=j; x++){
            if(p[x] != '*'){
                dp[0][j] = 0;
            }
        }
    }
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(s[i-1] == p[j-1] || p[j-1] == '?'){
                dp[i][j] = dp[i-1][j-1];
            }
            else if(p[j-1] == '*'){
                dp[i][j] = dp[i-1][j] | dp[i][j-1];
            }
            else dp[i][j] = 0;
        }
    }
    return dp[n][m];
}

bool spaceOptimal(string s, string p){
    int n = s.length();
    int m = p.length();
    vector<int> prev(m+1, 0);
    vector<int> cur(m+1, 0);
    prev[0] = 1;
    for(int j = 1; j<=m; j++){
        prev[j] = 1;
        for(int x = 0; x<=j; x++){
            if(p[x] != '*'){
                prev[j] = 0;
            }
        }
    }
    for(int i = 1; i<=n; i++){
        cur[0] = 0;
        for(int j = 1; j<=m; j++){
            if(s[i-1] == p[j-1] || p[j-1] == '?'){
                cur[j] = prev[j-1];
            }
            else if(p[j-1] == '*'){
                cur[j] = prev[j] | cur[j-1];
            }
            else cur[j] = 0;
        }
        prev = cur;
    }
    return prev[m];
}

int main(){
    string s = "abcdef";
    string p = "ab*f";
    int n = s.length();
    int m = p.length();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << memoize(n-1, m-1, s, p, dp) << endl;
    cout << tabulate(s, p) << endl;
    cout << spaceOptimal(s, p) << endl;
    return 0;
}