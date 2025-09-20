#include <bits/stdc++.h>
using namespace std;

// Frog can jump one or two steps, energy required is absoluted difference of h(i) and h(j), minimize it

// Memoization
int memoize(int n, vector<int>& dp, vector<int> h){
    if(n == 0){
        return 0;
    }
    if(dp[n] != -1){
        return dp[n];
    }
    int one = 0, two = INT_MAX;
    one = memoize(n-1, dp, h) + abs(h[n-1] - h[n]);
    if(n>1){
        two = memoize(n-2, dp, h) + abs(h[n-2] - h[n]);
    }
    return dp[n] = min(one, two);
}

// Tabulation
int tabulate(int n, vector<int> h){
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    dp[1] = abs(h[1]-h[0]);
    for(int i = 2; i<=n; i++){
        dp[i] = min(dp[i-1]+abs(h[i]-h[i-1]), dp[i-2]+abs(h[i-2]-h[i]));
        // cout << i << " " << dp[i] << endl;
    }
    return dp[n];
}

// Space Optimization
int spaceOptimal(int n, vector<int> h){
    int prev2 = 0;
    int prev1 = abs(h[1]-h[0]);
    int sol;
    for(int i = 2; i<=n; i++){
        sol = min(prev1+abs(h[i]-h[i-1]), prev2+abs(h[i-2]-h[i]));
        prev2 = prev1;
        prev1 = sol;
    }
    return prev1;
}

int main(){
    vector<int> h = {30, 10, 60, 10, 60 , 50};
    vector<int> dp(h.size(), -1);
    // cout << "Minimum Energy Required: " << memoize(h.size()-1, dp, h) << endl;
    cout << "Minimum Energy Required: " << tabulate(h.size()-1, h) << endl;
    return 0;
}