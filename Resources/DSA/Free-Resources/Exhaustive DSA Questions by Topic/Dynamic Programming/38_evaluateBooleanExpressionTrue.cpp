#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int j, int isTrue, string& s, vector<vector<vector<int>>>& dp){
    if(i>j){
        return 0;
    }
    if(i==j){
        if(isTrue){
            return s[i] == 'T';
        }
        else{
            return s[i] == 'F';
        }
    }
    if(dp[i][j][isTrue] != -1) return dp[i][j][isTrue];
    int ways = 0;
    for(int k = i+1; k<=j-1; k++){
        int lt = memoize(i, k-1, 1, s, dp);
        int lf = memoize(i, k-1, 0, s, dp);
        int rt = memoize(k+1, j, 1, s, dp);
        int rf = memoize(k+1, j, 0, s, dp);
        if(s[k] == '&'){
            if(isTrue){
                ways+=(lt*rt);
            }
            else{
                ways+=(lt*rf + lf*rt + lf*rf);
            }
        }
        else if(s[k] == '|'){
            if(isTrue){
                ways+=(lt*rt + lt*rf + lf*rt);
            }
            else{
                ways+=(lf*rf);
            }
        }
        else{
            if(isTrue){
                ways+=(lt*rf + lf*rt);
            }
            else{
                ways+=(lt*rt + lf*rf);
            }
        }
    }
    return dp[i][j][isTrue] = ways;
}

int tabulate(string s){
    int n = s.length();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
    for(int i = n-1; i>=0; i--){
        for(int j = 0; j<n; j++){
            if(i>j) continue;
            for(int isTrue = 0; isTrue<=1; isTrue++){
                if(i==j){
                    if(isTrue) dp[i][j][isTrue] = (s[i] == 'T');
                    else dp[i][j][isTrue] = (s[i] == 'F');
                }
                else{
                    int ways = 0;
                    for(int k = i+1; k<=j-1; k+=2){
                        int lt = dp[i][k-1][1];
                        int lf = dp[i][k-1][0];
                        int rt = dp[k+1][j][1];
                        int rf = dp[k+1][j][0];
                        if(s[k] == '&'){
                            if(isTrue){
                                ways+=(lt*rt);
                            }
                            else{
                                ways+=(lt*rf + lf*rt + lf*rf);
                            }
                        }
                        else if(s[k] == '|'){
                            if(isTrue){
                                ways+=(lt*rt + lt*rf + lf*rt);
                            }
                            else{
                                ways+=(lf*rf);
                            }
                        }
                        else{
                            if(isTrue){
                                ways+=(lt*rf + lf*rt);
                            }
                            else{
                                ways+=(lt*rt + lf*rf);
                            }
                        }
                    }
                    dp[i][j][isTrue] = ways;
                }
            }
        }
    }
    return dp[0][n-1][1];
}

int main(){
    string s = "T^F|T&F^T|F";
    int n = s.length();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
    cout << "No. of ways using memoization: " << memoize(0, n-1, 1, s, dp) << endl;
    cout << "No. of ways using tabulation: " << tabulate(s) << endl;
    return 0;
}