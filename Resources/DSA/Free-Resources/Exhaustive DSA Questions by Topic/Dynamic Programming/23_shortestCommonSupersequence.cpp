#include <bits/stdc++.h>
using namespace std;

int main(){
    string s1 = "brute";
    string s2 = "groot";
    
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

    string ans = "";
    int i = n, j = m;
    while(i>0 && j>0){
        if(s1[i-1] == s2[j-1]){
            ans+=s1[i-1];
            i--;
            j--;
        }
        else if(dp[i][j-1] > dp[i-1][j]){
            ans+=s2[j-1];
            j--;
        }
        else{
            ans+=s1[i-1];
            i--;
        }
    }
    while(i>0){
        ans+=s1[i-1];
        i--;
    }
    while(j>0){
        ans+=s2[j-1];
        j--;
    }
    reverse(ans.begin(), ans.end());
    cout << "Shortest Common Supersequence is: " << ans << endl;

    return 0;
}