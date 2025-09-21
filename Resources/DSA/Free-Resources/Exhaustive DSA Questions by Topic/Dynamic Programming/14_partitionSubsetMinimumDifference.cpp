#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> a = {1, 2, 3, 4, 5};
    int n = a.size();
    int target = 0;
    for(int x:a) target+=x;
    vector<vector<bool>> dp(n, vector<bool>(target+1, false));
    for(int i = 0; i<n; i++){
        dp[i][0] = true;
    }
    dp[0][a[0]] = true;
    for(int i = 1; i<n; i++){
        for(int j = 0; j<=target; j++){
            bool nt = dp[i-1][j];
            bool t = false;
            if(j>=a[i]) t = dp[i-1][j-a[i]];
            dp[i][j] = (nt | t);
        }
    }
    int mini = 1e8;
    for(int i = 0; i<target/2 + 1; i++){
        if(dp[n-1][i]){
            int s1 = i;
            int s2 = target - i;
            mini = min(mini, abs(s1-s2));
        }
    }
    cout << "Minimum absolute difference of sum of two subsets is " << mini << endl;
    return 0;
}