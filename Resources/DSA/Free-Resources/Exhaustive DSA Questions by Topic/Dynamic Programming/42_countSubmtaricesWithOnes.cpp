#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> mat = {
        {1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 0, 0, 1, 0}
    };
    int n = mat.size();
    int m = mat[0].size();
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for(int i = 0; i<n; i++){
        dp[i][0] = mat[i][0];
        ans+=mat[i][0];
    }
    for(int j = 1; j<m; j++){
        dp[0][j] = mat[0][j];
        ans+=mat[0][j];
    }
    for(int i = 1; i<n; i++){
        for(int j = 1; j<m; j++){
            if(mat[i][j] == 1){
                dp[i][j] = 1 + min(dp[i][j-1], min(dp[i-1][j], dp[i-1][j-1]));
            }
            ans+=dp[i][j];
        }
    }
    cout << "Total squares submatrices with all ones are " << ans << endl;
    return 0;
}