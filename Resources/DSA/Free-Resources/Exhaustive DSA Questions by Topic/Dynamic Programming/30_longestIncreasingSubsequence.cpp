#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int prev, vector<int>& a, vector<vector<int>>& dp){
    if(i == a.size()) return 0;
    if(dp[i][prev+1] != -1) return dp[i][prev+1];
    int nt = 0 + memoize(i+1, prev, a, dp);
    int t = 0;
    if(prev == -1 || a[i] > a[prev]){
        t = 1 + memoize(i+1, i, a, dp);
    }
    return dp[i][prev+1] = max(t, nt);
}

int tabulate(vector<int>& a){
    int n = a.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    for(int i = n-1; i >= 0; i--){
        for(int prev = n-1; prev >= -1; prev--){
            int nt = dp[i+1][prev+1];
            int t = 0;
            if(prev == -1 || a[i] > a[prev]){
                t = 1 + dp[i+1][i+1];
            }
            dp[i][prev+1] = max(t, nt);
        }
    }
    return dp[0][0];
}

int spaceOptimal(vector<int>& a){
    int n = a.size();
    vector<int> next(n+1, 0);
    vector<int> cur(n+1, 0);
    for(int i = n-1; i >= 0; i--){
        for(int prev = n-1; prev >= -1; prev--){
            int nt = next[prev+1];
            int t = 0;
            if(prev == -1 || a[i] > a[prev]){
                t = 1 + next[i+1];
            }
            cur[prev+1] = max(t, nt);
        }
        next = cur;
    }
    return next[0];
}

int betterTabulation(vector<int>& a){
    vector<int> dp(a.size(), 1);
    int ans = 1;
    for(int i = 0; i<a.size(); i++){
        for(int j = 0; j<i; j++){
            if(a[i] > a[j]){
                dp[i] = max(dp[i], 1 + dp[j]);
                ans = max(ans, dp[i]);
            }
        }
    }
    return ans;
}

int main(){
    vector<int> a = {10, 9, 2, 3, 5, 4, 101, 18};
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n+1, -1));
    cout << "Length of longest increasing subsequence using memoization: " << memoize(0, -1, a, dp) << endl;
    cout << "Length of longest increasing subsequence using tabulation: " << tabulate(a) << endl;
    cout << "Length of longest increasing subsequence using space optimization: " << spaceOptimal(a) << endl;
    cout << "Length of longest increasing subsequence using better tabulation: " << betterTabulation(a) << endl;
    return 0;
}