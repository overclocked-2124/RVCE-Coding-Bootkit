#include <bits/stdc++.h>
using namespace std;

// Take either 1 or 2 steps, count all possible ways to reach nth step

// Memoization
int climbMemoization(int n, vector<int>& dp){
    if(n<=1){
        return 1;
    }
    if(dp[n] != -1){
        return dp[n];
    }
    return dp[n] = climbMemoization(n-1, dp) + climbMemoization(n-2, dp);
}

// Tabulation
int climbTabulation(int n){
    vector<int> dp(n+1, -1);
    dp[0] = 1;
    dp[1] = 1;
    for(int i = 2; i<=n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// Space Optimization
int climbSpaceOptimal(int n){
    int prev1 = 1;
    int prev2 = 1;
    int sol;
    for(int i = 2; i<=n; i++){
        sol = prev1 + prev2;
        prev2 = prev1;
        prev1 = sol;
    }
    return prev1;
}

int main(){
    int n = 10;
    vector<int> dp(n+1, -1);
    cout << "From Memoization: " << climbMemoization(n, dp) << endl;
    cout << "From Tabulation: " << climbTabulation(n) << endl;
    cout << "From Space Optimization: " << climbSpaceOptimal(n) << endl;
    return 0;
}