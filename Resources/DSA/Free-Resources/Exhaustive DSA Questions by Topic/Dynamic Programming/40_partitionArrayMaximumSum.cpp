#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int k, vector<int>& a, vector<int>& dp){
    if(i == a.size()) return 0;
    if(dp[i] != -1) return dp[i];
    int maxSum = INT_MIN;
    int maxi = INT_MIN;
    int len = 0;
    int n = a.size();
    for(int j = i; j<min(i+k, n); j++){
        len++;
        maxi = max(maxi, a[j]);
        int sum = len*maxi + memoize(j+1, k, a, dp);
        maxSum = max(maxSum, sum);
    }
    return dp[i] = maxSum;
}

int tabulation(int k, vector<int>& a){
    int n = a.size();
    vector<int> dp(n+1, 0);
    dp[n] = 0;
    for(int i = n-1; i>=0; i--){
        int maxSum = INT_MIN;
        int maxi = INT_MIN;
        int len = 0;
        for(int j = i; j<min(i+k, n); j++){
            len++;
            maxi = max(maxi, a[j]);
            int sum = len*maxi + dp[j+1];
            maxSum = max(maxSum, sum);
        }
        dp[i] = maxSum;
    }
    return dp[0];
}

int main(){
    vector<int> a = {1, 2, 3, 7, 8, 7};
    int k = 3;
    // expect 1 + 21 + 16
    int n = a.size();
    vector<int> dp(n, -1);
    cout << "Maximum sum using memoization: " << memoize(0, k, a, dp) << endl;
    cout << "Maximum sum using tabulation: " << tabulation(k, a) << endl;
    return 0;
}