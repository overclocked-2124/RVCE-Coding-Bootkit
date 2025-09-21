#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j1, int j2, vector<vector<int>>& a, vector<vector<vector<int>>>& dp){
    if(j1<0 || j2<0 || j1>=a[0].size() || j2>=a[0].size()){
        return -1e8;
    }
    if(i == a.size()-1){
        if(j1 == j2){
            return a[i][j1];
        }
        else{
            return a[i][j1] + a[i][j2];
        }
    }
    if(dp[i][j1][j2] != -1) return dp[i][j1][j2];
    int maxi = -1e8;
    for(int dj1 = -1; dj1 <= 1; dj1++){
        for(int dj2 = -1; dj2 <= 1; dj2++){
            int t = memoize(i+1, j1+dj1, j2+dj2, a, dp);
            if(j1 == j2){
                maxi = max(maxi, a[i][j1]+t);
            }
            else{
                maxi = max(maxi, a[i][j1] + a[i][j2] + t);
            }
        }
    }
    return dp[i][j1][j2] = maxi;
}

int tabulate(vector<vector<int>>& grid){
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
    for(int j1 = 0; j1<m; j1++){
        for(int j2 = 0; j2<m; j2++){
            if(j1 == j2){
                dp[n-1][j1][j2] = grid[n-1][j1];
            }
            else{
                dp[n-1][j1][j2] = grid[n-1][j1] + grid[n-1][j2];
            }
        }
    }
    for(int i = n-2; i>=0; i--){
        for(int j1 = 0; j1<m; j1++){
            for(int j2 = 0; j2<m; j2++){
                int maxi = -1e8;
                for(int dj1 = -1; dj1<=1; dj1++){
                    for(int dj2 = -1; dj2<=1; dj2++){
                        int a = dj1+j1;
                        int b = dj2+j2;
                        int ans = 0;
                        if(a>=0 && b>=0 && a<m && b<m){
                            ans = dp[i+1][a][b];
                        }
                        else{
                            ans = -1e8;
                        }
                        if(j1 == j2){
                            ans = ans + grid[i][j1];
                        }
                        else{
                            ans = ans + grid[i][j1] + grid[i][j2];
                            }
                        maxi = max(ans, maxi);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }
    return dp[0][0][m-1];
}

int spaceOptimal(vector<vector<int>>& grid){
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(m, -1));
    vector<vector<int>> cur(m, vector<int>(m, -1));
    for(int j1 = 0; j1<m; j1++){
        for(int j2 = 0; j2<m; j2++){
            if(j1 == j2){
                dp[j1][j2] = grid[n-1][j1];
            }
            else{
                dp[j1][j2] = grid[n-1][j1] + grid[n-1][j2];
            }
        }
    }
    for(int i = n-2; i>=0; i--){
        for(int j1 = 0; j1<m; j1++){
            for(int j2 = 0; j2<m; j2++){
                int maxi = -1e8;
                for(int dj1 = -1; dj1<=1; dj1++){
                    for(int dj2 = -1; dj2<=1; dj2++){
                        int a = dj1+j1;
                        int b = dj2+j2;
                        int ans = 0;
                        if(a>=0 && b>=0 && a<m && b<m){
                            ans = dp[a][b];
                        }
                        else{
                            ans = -1e8;
                        }
                        if(j1 == j2){
                            ans = ans + grid[i][j1];
                        }
                        else{
                            ans = ans + grid[i][j1] + grid[i][j2];
                        }
                        maxi = max(ans, maxi);
                    }
                    }
            cur[j1][j2] = maxi;
            }
        }
        dp = cur;
    }
    return dp[0][m-1];
}

int main(){
    vector<vector<int>> a = {
        {2, 3, 1, 2},
        {3, 4, 2, 2},
        {5, 6, 3, 5}
    };
    int n = a.size();
    int m = a[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
    cout << "Memoization: " << memoize(0, 0, m-1, a, dp);
    cout << "Tabulation: " << memoize(0, 0, m-1, a, dp);
    return 0;
}