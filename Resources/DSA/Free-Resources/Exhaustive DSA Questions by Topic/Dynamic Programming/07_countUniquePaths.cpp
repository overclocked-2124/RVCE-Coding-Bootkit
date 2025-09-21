#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, vector<vector<int>>& dp){
    if(i == 0 && j == 0){
        return 1;
    }
    if(i<0 || j<0){
        return 0;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    int up = memoize(i-1, j, dp);
    int left = memoize(i, j-1, dp);
    return dp[i][j] = up+left;
}

int tabulate(int n, int m){
    vector<vector<int>> dp(n, vector<int>(m, 0));
    dp[0][0] = 1;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(i == 0 && j == 0){
                dp[i][j] = 1;
            }
            else{
                int up = 0, left = 0;
                if(i>0){
                    up = dp[i-1][j];
                }
                if(j>0){
                    left = dp[i][j-1];
                }
                dp[i][j] = up + left;
            }
        }
    }
    return dp[n-1][m-1];
}

int spaceOptimal(int n, int m){
    vector<int> prev(m, 0);
    for(int i = 0; i<n; i++){
        vector<int> cur(m);
        for(int j = 0; j<m; j++){
            if(i == 0 && j == 0){
                cur[j] = 1;
            }
            else{
                int up = 0, left = 0;
                if(i>0){
                    up = prev[j];
                }
                if(j>0){
                    left = cur[j-1];
                }
                cur[j] = up + left;
            }
        }
        prev = cur;
    }
    return prev[m-1];
}


int main(){
    int n = 3, m = 3;
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << "Number of unique paths is: " << memoize(n-1, m-1, dp) << endl;
    cout << "Number of unique paths is: " << tabulate(n, m) << endl;
    cout << "Number of unique paths is: " << spaceOptimal(n, m) << endl;
    return 0;
}