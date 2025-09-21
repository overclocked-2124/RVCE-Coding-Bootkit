#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int buy, int cap, vector<int>& a, vector<vector<vector<int>>>& dp){
    if(i == a.size()) return 0;
    if(cap == 0) return 0;
    if(dp[i][buy][cap] != -1) return dp[i][buy][cap];
    long profit = 0;
    if(buy){
        profit = max(-a[i] + memoize(i+1, 0, cap, a, dp), memoize(i+1, 1, cap, a, dp));
    }
    else{
        profit = max(a[i] + memoize(i+1, 1, cap-1, a, dp), memoize(i+1, 0, cap, a, dp));
    }
    return dp[i][buy][cap] = profit;
}

int tabulate(vector<int>& a){
    int n = a.size();
    vector<vector<vector<int>>> dp(a.size()+1, vector<vector<int>>(2, vector<int>(3, 0)));
    for(int i = n-1; i>=0; i--){
        for(int j = 0; j<=1; j++){
            for(int k = 1; k<=2; k++){
                if(j){
                    dp[i][j][k] = max(-a[i] + dp[i+1][0][k], dp[i+1][1][k]);
                }
                else{
                    dp[i][j][k] = max(a[i] + dp[i+1][1][k-1], dp[i+1][0][k]);
                }
            }
        }
    }
    return dp[0][1][2];
}

int spaceOptimal(vector<int>& a){
    int n = a.size();
    vector<vector<int>> cur(2, vector<int>(3, 0));
    vector<vector<int>> next(2, vector<int>(3, 0));
    for(int i = n-1; i>=0; i--){
        for(int j = 0; j<=1; j++){
            for(int k = 1; k<=2; k++){
                if(j){
                    cur[j][k] = max(-a[i] + next[0][k], next[1][k]);
                }
                else{
                    cur[j][k] = max(a[i] + next[1][k-1], next[0][k]);
                }
            }
        }
        next = cur;
    }
    return next[1][2];
}

int main(){
    vector<int> a = {3, 3, 5, 0, 0, 3, 1, 4};
    int cap = 2;
    vector<vector<vector<int>>> dp(a.size(), vector<vector<int>>(2, vector<int>(3, -1)));
    cout << "Maximum profit using memoization: " << memoize(0, 1, 2, a, dp) << endl;
    cout << "Maximum profit using tabulation: " << tabulate(a) << endl;
    cout << "Maximum profit using space optimization: " << spaceOptimal(a) << endl;
    return 0;
}