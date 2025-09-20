#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, vector<int>& a, vector<vector<int>>& dp){
    if(i == j){
        return 0;
    }
    if(dp[i][j] != -1) return dp[i][j];
    int mini = 1e9;
    for(int k = i; k<=j-1; k++){
        int steps = a[i-1]*a[k]*a[j] + memoize(i, k, a, dp) + memoize(k+1, j, a, dp);
        mini = min(mini, steps);
    }
    return dp[i][j] = mini;
}

int tabulate(vector<int>& a){
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for(int i = 1; i<n; i++){
        dp[i][i] = 0;
    }
    for(int i = n-1; i>0; i--){
        for(int j = i+1; j<=n-1; j++){
            int mini = 1e9;
            for(int k = i; k<=j-1; k++){
                int steps = a[i-1]*a[k]*a[j] + dp[i][k] + dp[k+1][j];
                mini = min(steps, mini);
            }
            dp[i][j] = mini;
        }
    }
    return dp[1][n-1];
}

int main(){
    vector<int> a = {10, 20, 30, 40, 50};
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    cout << "Minimum Operations (Memoization): " << memoize(1, n-1, a, dp) << endl;
    cout << "Minimum Operations (Tabulation): " << tabulate(a) << endl;
    return 0;
}