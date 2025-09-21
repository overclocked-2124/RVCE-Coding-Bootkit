#include <bits/stdc++.h>
using namespace std;

// Memoization
int fibonacciMemoization(int n, vector<int>& dp){
    if(n<=1){
        return n;
    }
    if(dp[n] != -1){
        return dp[n];
    }
    return dp[n] = fibonacciMemoization(n-1, dp) + fibonacciMemoization(n-2, dp);
}

// Tabulation
int fibonacciTabulation(int n){
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 2; i<=n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// Space Optimization
int fibonacciSpaceOptimal(int n){
    int prev1 = 1;
    int prev2 = 0;
    int sol;
    for(int i = 2; i<=n; i++){
        sol = prev1 + prev2;
        prev2 = prev1;
        prev1 = sol;
    }
    return prev1;
}

int main(){
    int n = 1;
    vector<int> dp(n+1, -1);
    cout << "From Memoization: " << fibonacciMemoization(n, dp) << endl;
    cout << "From Tabulation: " << fibonacciTabulation(n) << endl;
    cout << "From Space Optimization: " << fibonacciSpaceOptimal(n) << endl;
    return 0;
}