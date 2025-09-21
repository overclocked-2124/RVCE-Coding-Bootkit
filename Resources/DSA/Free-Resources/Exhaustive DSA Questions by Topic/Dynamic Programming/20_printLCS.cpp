#include <bits/stdc++.h>
using namespace std;

int main(){
    string s1 = "aaaa";
    string s2 = "aaaa";
    
    int n = s1.length(), m = s2.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    string ans;
    int i = n, j = m, k = dp[n][m];
    for(int x = 0; x<k; x++){
        ans = ans + "$";
    }
    k--;
    while(i>0 && j>0){
        if(s1[i-1] == s2[j-1]){
            ans[k] = s1[i-1];
            k--;
            i--;
            j--;
        }
        else if(dp[i][j-1] > dp[i-1][j]){
            j--;
        }
        else{
            i--;
        }
    }
    
    cout << "Longest Common Subsequence is: " << ans << endl;

    return 0;
}