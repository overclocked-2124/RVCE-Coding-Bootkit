#include <bits/stdc++.h>
using namespace std;

bool memoize(int ind, int target, vector<int>& a, vector<vector<int>>& dp){
    if(target == 0){
        return true;
    }
    if(ind == 0){
        return target == a[0];
    }
    if(dp[ind][target] != -1){
        return dp[ind][target];
    }
    bool nt = memoize(ind-1, target, a, dp);
    if(target>=a[ind]){
        bool t = memoize(ind-1, target-a[ind], a, dp);
    }
    return dp[ind][target] = t | nt;
}

bool tabulate(vector<int>& a, int target){
    int n = a.size();
    vector<vector<bool>> dp(n, vector<bool>(target+1, false));
    for(int i = 0; i<n; i++){
        dp[i][0] = true;
    }
    dp[0][a[0]] = true;
    for(int i = 1; i<n; i++){
        for(int j = 0; j<=target; j++){
            bool nt = dp[i-1][j];
            bool t = false;
            if(j>=a[i]) t = dp[i-1][j-a[i]];
            dp[i][j] = (nt | t);
        }
    }
    return dp[n-1][target];
}

bool spaceOptimal(vector<int>& a, int target){
    int n = a.size();
    vector<bool> dp(target+1, false);
    vector<bool> cur(target+1, false);
    for(int i = 0; i<n; i++){
        dp[0] = true;
    }
    dp[a[0]] = true;
    for(int i = 1; i<n; i++){
        for(int j = 0; j<=target; j++){
            bool nt = dp[j];
            bool t = false;
            if(j>=a[i]) t = dp[j-a[i]];
            cur[j] = (nt | t);
        }
        dp = cur;
    }
    return dp[target];
}

int main(){
    vector<int> a = {1, 2, 3, 4};
    int target = 4;
    vector<vector<int>> dp(a.size(), vector<int>(target+1, -1));
    if(memoize(a.size()-1, target, a, dp)){
        cout << "Possible using memoization" << endl;
    }
    else{
        cout << "Not possible using memoization" << endl;
    }
    if(tabulate(a, target)){
        cout << "Possible using tabulation" << endl;
    }
    else{
        cout << "Not possible using tabulation" << endl;
    }
    if(spaceOptimal(a, target)){
        cout << "Possible using space optimization" << endl;
    }
    else{
        cout << "Not possible using space optimization" << endl;
    }
    return 0;
}