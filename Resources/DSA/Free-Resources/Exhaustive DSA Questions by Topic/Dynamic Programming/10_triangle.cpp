#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, vector<vector<int>>& triangle, int n, vector<vector<int>>& dp){
    if(i==n-1) {
        return triangle[i][j];
    }
    if(dp[i][j] != -1) {
        return dp[i][j];
    }
    int down = memoize(i+1, j, triangle, n, dp);
    int diagonal = memoize(i+1, j+1, triangle, n, dp);
    return dp[i][j] = triangle[i][j] + min(down, diagonal);
}

int tabulate(vector<vector<int>>& triangle){
    vector<vector<int>> dp(triangle.size(), vector<int>(triangle.size(), -1e5));
    for(int i = 0; i<triangle.size(); i++){
        for(int j = 0; j<triangle[i].size(); j++){
            if(i==0 && j==0){
                dp[0][0] = triangle[0][0];
            }
            else{
                int up = INT_MAX, diagonal = INT_MAX;
                if(i>0){
                    if(dp[i-1][j] != -1e5) {
                        up = dp[i-1][j];
                    }
                    if(j>0){
                        diagonal = dp[i-1][j-1];
                    }
                }
                dp[i][j] = triangle[i][j] + min(up, diagonal);
            }
        }
    }
    int ans = INT_MAX;
    for(int i = 0; i<dp[dp.size()-1].size(); i++){
        ans = min(ans, dp[dp.size()-1][i]);
    }
    return ans;
}

int spaceOptimal(vector<vector<int>>& triangle){
    vector<int> prev(triangle.size(), -1e5);
    for(int i = 0; i<triangle.size(); i++){
        vector<int> cur(triangle.size(), -1e5);
        for(int j = 0; j<triangle[i].size(); j++){
            if(i==0 && j==0){
                cur[j] = triangle[0][0];
            }
            else{
                int up = INT_MAX, diagonal = INT_MAX;
                if(i>0){
                    if(prev[j] != -1e5) {
                        up = prev[j];
                    }
                    if(j>0){
                        diagonal = prev[j-1];
                    }
                }
                cur[j] = triangle[i][j] + min(up, diagonal);
            }
        }
        prev = cur;
    }
    int ans = INT_MAX;
    for(int i = 0; i<prev.size(); i++){
        ans = min(ans, prev[i]);
        }
    return ans;
}

int main(){
    vector<vector<int>> triangle{{1}, {2, 3}, {3, 6, 7}, {8, 9, 6, 10}};
    vector<vector<int>> dp(triangle.size(), vector<int>(triangle.size(), -1));
    cout << "Memoization: " << memoize(0, 0, triangle, triangle.size(), dp) << endl;
    cout << "Tabulation: " << tabulate(triangle) << endl;
    cout << "Space Optimization: " << spaceOptimal(triangle) << endl;
    return 0;
}