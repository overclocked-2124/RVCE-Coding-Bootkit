#include <bits/stdc++.h>
using namespace std;

int memoize(int ind, int wt, vector<int>& w, vector<int>& val, vector<vector<int>>& dp){
    if(ind == 0){
        if(w[0]<=wt){
            return val[0];
        }
        else{
            return 0;
        }
    }
    if(dp[ind][wt] != -1){
        return dp[ind][wt];
    }
    int nt = memoize(ind-1, wt, w, val, dp);
    int t = -1e9;
    if(w[ind]<=wt){
        t =val[ind] + memoize(ind-1, wt-w[ind], w, val, dp);
    }
    return dp[ind][wt] = max(t, nt);
}

int tabulate(int n, int wt, vector<int>& w, vector<int>& val){
    vector<vector<int>> dp(n, vector<int>(wt+1, 0));
    for(int i = w[0]; i<wt; i++){
        dp[0][i] = val[0];
    }
    for(int i = 1; i<n; i++){
        for(int j = 0; j<=wt; j++){
            int nt = dp[i-1][j];
            int t = INT_MIN;
            if(w[i] <= j) t = val[i] + dp[i-1][j-w[i]];
            dp[i][j] = max(t, nt);
        }
    }
    return dp[n-1][wt];
}

int spaceOptimal(int n, int wt, vector<int>& w, vector<int>& val){
    vector<int> dp(wt+1, 0);
    for(int i = w[0]; i<wt; i++){
        dp[i] = val[0];
    }
    for(int i = 1; i<n; i++){
        for(int j = wt; j>=0; j--){
            int nt = dp[j];
            int t = INT_MIN;
            if(w[i] <= j) t = val[i] + dp[j-w[i]];
            dp[j] = max(t, nt);
        }
    }
    return dp[wt];
}

int main(){
    vector<int> w = {3, 2, 5};
    vector<int> val = {30, 40, 60};
    int n = 3;
    int wt = 5;
    vector<vector<int>> dp(n, vector<int>(wt+1, -1));
    cout << "Value achieved in knapsack using memoization: " << memoize(n-1, wt, w, val, dp) << endl;
    cout << "Value achieved in knapsack using tabulation: " << tabulate(n-1, wt, w, val) << endl;
    cout << "Value achieved in knapsack using space opt: " << spaceOptimal(n-1, wt, w, val) << endl;
    return 0;
}