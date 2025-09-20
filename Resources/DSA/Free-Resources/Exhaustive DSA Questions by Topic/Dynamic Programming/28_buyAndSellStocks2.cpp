#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int buy, vector<int>& a, vector<vector<int>>& dp){
    if(i == a.size()) return 0;
    if(dp[i][buy] != -1) return dp[i][buy];
    long profit = 0;
    if(buy){
        profit = max(-a[i] + memoize(i+1, 0, a, dp), memoize(i+1, 1, a, dp));
    }
    else{
        profit = max(a[i] + memoize(i+1, 1, a, dp), memoize(i+1, 0, a, dp));
    }
    return dp[i][buy] = profit;
}

int tabulate(vector<int>& a){
    int n = a.size();
    vector<vector<int>> dp(n+1, vector<int>(2, 0));
    dp[n][0] = 0;
    dp[n][1] = 0;
    for(int i = n-1; i>=0; i--){
        dp[i][1] = max(-a[i]+dp[i+1][0], dp[i+1][1]);
        dp[i][0] = max(a[i]+dp[i+1][1], dp[i+1][0]);
    }
    return dp[0][1];
}

int spaceOptimal(vector<int>& a){
    int n = a.size();
    int nextSell = 0;
    int nextBuy = 0;
    int currentBuy, currentSell;
    for(int i = n-1; i>=0; i--){
        currentBuy = max(-a[i]+nextSell, nextBuy);
        currentSell = max(a[i]+nextBuy, nextSell);
        nextBuy = currentBuy;
        nextSell = currentSell;
    }
    return nextBuy;
}

int main(){
    vector<int> a = {7, 1, 5, 3, 6, 4};
    vector<vector<int>> dp(a.size(), vector<int>(2, -1));
    cout << "Maximum profit using memoization: " << memoize(0, 1, a, dp) << endl;
    cout << "Maximum profit using tabulation: " << tabulate(a) << endl;
    cout << "Maximum profit using space optimization: " << spaceOptimal(a) << endl;
    return 0;
}