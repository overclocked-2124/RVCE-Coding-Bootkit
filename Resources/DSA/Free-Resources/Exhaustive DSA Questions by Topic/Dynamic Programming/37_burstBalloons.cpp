#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, vector<int>& nums, vector<vector<int>>& dp){
    if(i>j) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    int maxi = INT_MIN;
    for(int k = i; k<=j; k++){
        int points = nums[i-1] * nums[k] * nums[j+1] + memoize(i, k-1, nums, dp) + memoize(k+1, j, nums, dp);
        maxi = max(maxi, points);
    }
    return dp[i][j] = maxi;
}

int tabulate(vector<int>& nums, int n){
    vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
    for(int i = n; i>=1; i--){
        for(int j = 1; j<=n; j++){
            if(i>j) continue;
            int maxi = INT_MIN;
            for(int k = i; k<=j; k++){
                int points = nums[i-1] * nums[k] * nums[j+1] + dp[i][k-1] + dp[k+1][j];
                maxi = max(maxi, points);
            }
            dp[i][j] = maxi;
        }
    }
    return dp[1][n];
}

int main(){
    vector<int> nums = {3, 1, 5, 8};
    int n = nums.size();
    nums.push_back(1);
    nums.insert(nums.begin(), 1);
    vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
    cout << "Points using memoization: " << memoize(1, n, nums, dp) << endl;
    cout << "Points using memoization: " << tabulate(nums, n) << endl;
    return 0;
}