#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, vector<vector<int>>& dp, vector<vector<int>>& a){
    if(i == 0 && j == 0){
        return a[i][j];
    }
    if(i<0 || j<0){
        return INT_MAX;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    int u = INT_MAX;
    int l = INT_MAX;
    if(i>0){
        u = memoize(i-1, j, dp, a);
    }
    if(j>0){
        l = memoize(i, j-1, dp, a);
    }
    return dp[i][j] = a[i][j] + min(u, l);
}

int tabulate(vector<vector<int>>& a){
    vector<vector<int>> dp(a.size(), vector<int>(a[0].size(), -1));
    for(int i = 0; i<a.size(); i++){
        for(int j = 0; j<a[0].size(); j++){
            if(i == 0 && j == 0) dp[i][j] = a[0][0];
            else{
                int u = INT_MAX;
                int l = INT_MAX;
                if(i>0) u = dp[i-1][j];
                if(j>0) l = dp[i][j-1];
                dp[i][j] = a[i][j] + min(u, l);
            }
        }
    }
    return dp[a.size()-1][a[0].size()-1];
}

int spaceOptimal(vector<vector<int>>& a){
    vector<int> prev(a[0].size(), 0);
    for(int i = 0; i<a.size(); i++){
        vector<int> cur(a[0].size());
        for(int j = 0; j<a[0].size(); j++){
            if(i == 0 && j == 0) cur[j] = a[0][0];
            else{
                int u = INT_MAX;
                int l = INT_MAX;
                if(i>0) u = prev[j];
                if(j>0) l =cur[j-1];
                cur[j] = a[i][j] + min(u, l);
            }
        }
        prev = cur;
    }
    return prev[a[0].size()-1];
}

int main(){
    vector<vector<int>> a = {
        {5, 9, 6},
        {11, 5, 2}
    };
    vector<vector<int>> dp(a.size(), vector<int>(a[0].size(), -1));
    cout << "Minimum Path Sum: " << memoize(a.size()-1, a[0].size()-1, dp, a) << endl;
    cout << "Minimum Path Sum: " << tabulate(a) << endl;
    cout << "Minimum Path Sum: " << spaceOptimal(a) << endl;
    return 0;
}