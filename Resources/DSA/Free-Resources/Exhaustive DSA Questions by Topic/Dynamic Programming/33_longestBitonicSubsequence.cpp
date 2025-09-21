#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& a){
    int n = a.size();
    vector<int> dp(n, 1);
    vector<int> rev_dp(n, 1);
    for(int i = 1; i<n; i++){
        for(int j = 0; j<i; j++){
            if(a[j] < a[i] && dp[i] < dp[j]+1){
                dp[i] = dp[j] + 1;
            }
        }
    }
    reverse(a.begin(), a.end());
    for(int i = 1; i<n; i++){
        for(int j = 0; j<i; j++){
            if(a[j] < a[i] && rev_dp[i] < rev_dp[j]+1){
                rev_dp[i] = rev_dp[j] + 1;
            }
        }
    }
    reverse(rev_dp.begin(), rev_dp.end());
    int maxi = -1;
    for(int i = 0; i<n; i++){
        maxi = max(maxi, dp[i]+rev_dp[i]-1);
    }
    return maxi;
}

int main(){
    vector<int> a = {1, 11, 2, 10, 4, 5, 2, 1};
    // Bitonic is inc / dec / inc then dec
    int ans = solve(a);
    cout << "Length of longest bitonic subsequence is " << ans << endl;
    return 0;
}