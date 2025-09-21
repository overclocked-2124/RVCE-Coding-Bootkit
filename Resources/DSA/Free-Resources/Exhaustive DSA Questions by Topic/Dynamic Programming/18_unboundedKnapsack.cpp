#include <bits/stdc++.h>
using namespace std;

int memoize(int ind, int wt, vector<int>& w, vector<int>& val, vector<vector<int>>& dp){
    if(ind == 0){
        return (wt/w[0])*val[0];
    }
    if(dp[ind][wt] != -1) return dp[ind][wt];
    int nt = 0 + memoize(ind-1, wt, w, val, dp);
    int t = INT_MIN;
    if(w[ind] <= wt){
        t = val[ind] + memoize(ind, wt-w[ind], w, val, dp);
    }
    return dp[ind][wt] = max(t, nt);
}

int tabulate(int n, int wt, vector<int>& w, vector<int>& val){
    vector<vector<int>> dp(n, vector<int>(wt+1, 0));
    for(int i = 0; i<wt+1; i++){
        dp[0][i] = (i/w[0])*val[0];
    }
    for(int i = 1; i<n; i++){
        for(int j = 0; j<wt+1; j++){
            int nt = dp[i-1][j];
            int t = val[i] + dp[i][j-w[i]];
            dp[i][j] = max(t, nt);
        }
    }
    return dp[n-1][wt];
}

int spaceOptimal(int n, int wt, vector<int>& w, vector<int>& val){
    vector<int> prev(wt+1, 0);
    vector<int> cur(wt+1, 0);
    for(int i = 0; i<wt+1; i++){
        prev[i] = (i/w[0])*val[0];
    }
    for(int i = 1; i<n; i++){
        for(int j = 0; j<wt+1; j++){
            int nt = prev[j];
            int t = val[i] + cur[j-w[i]];
            cur[j] = max(t, nt);
        }
        prev = cur;
    }
    return prev[wt];
}

int spaceOptimalSingleArray(int n, int wt, vector<int>& w, vector<int>& val){
    vector<int> dp(wt+1, 0);
    for(int i = 0; i<wt+1; i++){
        dp[i] = (i/w[0])*val[0];
    }
    for(int i = 1; i<n; i++){
        for(int j = 0; j<wt+1; j++){
            int nt = dp[j];
            int t = val[i] + dp[j-w[i]];
            dp[j] = max(t, nt);
        }
    }
    return dp[wt];
}

int main(){
    vector<int> w = {2, 4, 6};
    vector<int> val = {5, 11, 13};
    int n = 3;
    int wt = 10;
    vector<vector<int>> dp(n, vector<int>(wt+1, -1));
    cout << "Value achieved in knapsack using memoization: " << memoize(n-1, wt, w, val, dp) << endl;
    cout << "Value achieved in knapsack using tabulation: " << tabulate(n-1, wt, w, val) << endl;
    cout << "Value achieved in knapsack using space opt double array: " << spaceOptimal(n-1, wt, w, val) << endl;
    cout << "Value achieved in knapsack using space opt single array: " << spaceOptimalSingleArray(n-1, wt, w, val) << endl;
    return 0;
}