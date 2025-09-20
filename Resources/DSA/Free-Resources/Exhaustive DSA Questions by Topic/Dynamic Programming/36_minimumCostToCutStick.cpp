#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, vector<int>& cut, vector<vector<int>>& dp){
    if(i>j) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    int mini = INT_MAX;
    for(int k = i; k<=j; k++){
        int cost = cut[j+1]-cut[i-1] + memoize(i, k-1, cut, dp) + memoize(k+1, j, cut, dp);
        mini = min(mini, cost);
    }
    return dp[i][j] = mini;
}

int tabulate(vector<int>& cut, int n){
    vector<vector<int>> dp(cut.size(), vector<int>(cut.size(), 0));
    for(int i = cut.size()-2; i>=1; i--){
        for(int j = 1; j<=cut.size()-2; j++){
            if(i>j) continue;
            int mini = INT_MAX;
            for(int k = i; k<=j; k++){
                int cost = cut[j+1] - cut[i-1] + dp[i][k-1] + dp[k+1][j];
                mini = min(cost, mini);
            }
            dp[i][j] = mini;
        }
    }
    return dp[1][cut.size()-2];
}

int main(){
    vector<int> cut = {0, 1, 3, 5, 4};
    int n = 7;
    sort(cut.begin(), cut.end());
    cut.push_back(n);
    vector<vector<int>> dp(n, vector<int>(n, -1));
    cout << "Minimum Cost using memoization: " << memoize(1, cut.size()-2, cut, dp) << endl;
    cout << "Minimum Cost using tabulation: " << tabulate(cut, n) << endl;
    return 0;
}