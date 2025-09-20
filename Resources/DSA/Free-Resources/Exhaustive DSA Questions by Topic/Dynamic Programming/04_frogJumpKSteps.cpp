#include <bits/stdc++.h>
using namespace std;

// Frog can jump one or two steps, energy required is absoluted difference of h(i) and h(j), minimize it

// Memoization
int memoize(int n, vector<int>& dp, vector<int> h, int k){
    if(n == 0){
        return 0;
    }
    if(dp[n] != -1){
        return dp[n];
    }
    int mini = INT_MAX;
    for(int j = 1; j<=k; j++){
        if(n-j>=0){
            int jumpEnergy = memoize(n-j, dp, h, k) + abs(h[n]-h[n-j]);
            mini = min(mini, jumpEnergy);
        }
    }

    return dp[n] = mini;
}

// Tabulation
int tabulate(int n, vector<int> h, int k){
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    dp[1] = abs(h[1]-h[0]);
    for(int i = 2; i<=n; i++){
        int mini = INT_MAX;
        for(int j = 1; j<=k; j++){
            if(i-j>=0){
                int jumpEnergy = dp[i-j] + abs(h[i]-h[i-j]);
                mini = min(mini,  jumpEnergy);
            }
        }
        dp[i] = mini;
        // cout << i << " " << dp[i] << endl;
    }
    return dp[n];
}

int main(){
    vector<int> h = {30, 10, 60, 10, 60 , 50};
    vector<int> dp(h.size(), -1);
    // cout << "Minimum Energy Required: " << memoize(h.size()-1, dp, h, 5)<< endl;
    cout << "Minimum Energy Required: " << tabulate(h.size()-1, h, 5) << endl;
    return 0;
}