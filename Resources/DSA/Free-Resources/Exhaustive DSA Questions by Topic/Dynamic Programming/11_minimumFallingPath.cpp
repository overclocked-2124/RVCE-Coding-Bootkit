#include <bits/stdc++.h>
using namespace std;

int f(int i, int j, vector<vector<int>>& a, vector<vector<int>>& dp){
    if(j<0 || j>a[0].size()-1){
        return INT_MAX;
    }
    if(i == 0){
        return a[i][j];
    }
    if(dp[i][j] != -1) return dp[i][j];
    int u = f(i-1, j, a, dp);
    int l = f(i-1, j-1, a, dp);
    int r = f(i-1, j+1, a, dp);
    return dp[i][j] = a[i][j] + min({u, l, r});
}

int memoize(vector<vector<int>>& a){
    int mini = INT_MAX;
    for(int i = 0; i<a[0].size(); i++){
        vector<vector<int>> dp(a.size(), vector<int>(a[0].size(), -1));
        mini = min(mini, f(a.size()-1, i, a, dp));
    }
    return mini;
}

int tabulate(vector<vector<int>>& a){
    int mini = INT_MAX;
    vector<vector<int>> dp(a.size(), vector<int>(a[0].size(), 0));
    for(int j = 0; j<a[0].size(); j++){
        dp[0][j] = a[0][j];
    }
    for(int i = 1; i<a.size(); i++){
        for(int j = 0; j<a[0].size(); j++){
            int l = INT_MAX, r = INT_MAX;
            int u = dp[i-1][j];
            if(j>0) l = dp[i-1][j-1];
            if(j<a[0].size()-1) r = dp[i-1][j+1];
            dp[i][j] = a[i][j] + min({u, l, r});
        }
    }
    for(int i = 0; i<a[0].size(); i++){
        mini  = min(mini, dp[a.size()-1][i]);
    }
    return mini;
}

int spaceOptimal(vector<vector<int>>& a){
    int mini = INT_MAX;
    vector<int> prev(a[0].size(), 0);
    for(int j = 0; j<a[0].size(); j++){
        prev[j] = a[0][j];
    }
    for(int i = 1; i<a.size(); i++){
        vector<int> cur(a[0].size(), 0);
        for(int j = 0; j<a[0].size(); j++){
            int l = INT_MAX, r = INT_MAX;
            int u = prev[j];
            if(j>0) l = prev[j-1];
            if(j<a[0].size()-1) r = prev[j+1];
            cur[j] = a[i][j] + min({u, l, r});
        }
        prev = cur;
    }
    for(int i = 0; i<a[0].size(); i++){
        mini  = min(mini, prev[i]);
    }
    return mini;
}

int main(){
    vector<vector<int>> a = {
        {2, 1, 3},
        {6, 5, 4},
        {7, 8, 9}
    };
    cout << "Memoization results in minimum sum of: " << memoize(a) << endl;
    cout << "Tabulation results in minimum sum of: " << tabulate(a) << endl;
    cout << "Space Optimization results in minimum sum of: " << spaceOptimal(a) << endl;
    return 0;
}