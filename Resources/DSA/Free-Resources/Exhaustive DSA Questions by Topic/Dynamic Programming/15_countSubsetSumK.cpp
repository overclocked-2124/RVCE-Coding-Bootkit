#include <bits/stdc++.h>
using namespace std;

int memoize(int ind, int target, vector<int>& a, vector<vector<int>>& dp){
    if(target == 0){
        return 1;
    }
    if(ind == 0){
        return target == a[0];
    }
    if(dp[ind][target] != -1){
        return dp[ind][target];
    }
    int nt = memoize(ind-1, target, a, dp);
    int t = 0;
    if(target>=a[ind]){
        t = memoize(ind-1, target-a[ind], a, dp);
    }
    return dp[ind][target] = t + nt;
}

int tabulate(vector<int>& a, int target){
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(target+1, 0));
    for(int i = 0; i<n; i++){
        dp[i][0] = 1;
    }
    dp[0][a[0]] = 1;
    for(int i = 1; i<n; i++){
        for(int j = 0; j<=target; j++){
            int nt = dp[i-1][j];
            int t = 0;
            if(j>=a[i]) t = dp[i-1][j-a[i]];
            dp[i][j] = (nt + t);
        }
    }
    return dp[n-1][target];
}

int spaceOptimal(vector<int>& a, int target){
    int n = a.size();
    vector<int> dp(target+1, 0);
    vector<int> cur(target+1, 0);
    for(int i = 0; i<n; i++){
        dp[0] = 1;
    }
    dp[a[0]] = true;
    for(int i = 1; i<n; i++){
        for(int j = 0; j<=target; j++){
            int nt = dp[j];
            int t = 0;
            if(j>=a[i]) t = dp[j-a[i]];
            cur[j] = (nt + t);
        }
        dp = cur;
    }
    return dp[target];
}

int main(){
    vector<int> a = {1, 2, 3, 4, 5};
    int target = 5;
    vector<vector<int>> dp(a.size(), vector<int>(target+1, -1));
    if(memoize(a.size()-1, target, a, dp)){
        cout << "Possible using memoization: " << memoize(a.size()-1, target, a, dp) << endl;
    }
    else{
        cout << "Not possible using memoization" << endl;
    }
    if(tabulate(a, target)){
        cout << "Possible using tabulation: " << tabulate(a, target) << endl;
    }
    else{
        cout << "Not possible using tabulation" << endl;
    }
    if(spaceOptimal(a, target)){
        cout << "Possible using space optimization: " << spaceOptimal(a, target) << endl;
    }
    else{
        cout << "Not possible using space optimization" << endl;
    }
    return 0;
}