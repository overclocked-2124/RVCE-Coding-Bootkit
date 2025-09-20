#include <bits/stdc++.h>
using namespace std;

int memoize(int i, vector<int>& dp, vector<int>& a){
    if(i == 0) return a[i];
    if(i < 0) return 0;
    if(dp[i] != -1) return dp[i];
    int p = a[i] + memoize(i-2, dp, a);
    int np = memoize(i-1, dp, a);
    return dp[i] = max(p, np);
}

int tabulate(int i, vector<int>& a){
    vector<int> dp(a.size(), -1);
    dp[0] = a[0];
    if(a.size()>1) dp[1] = max(a[0], a[1]);
    for(int i = 2; i<a.size(); i++){
        int p = a[i] + dp[i-2];
        int np = dp[i-1];
        dp[i] = max(p, np);
    }
    return dp[a.size()-1];
}


int spaceOptimal(int i, vector<int>& a){
    int prev2 = a[0];
    int prev1 = a[0];
    if(a.size()>1) prev1 = max(a[0], a[1]);
    int sol;
    for(int i = 2; i<a.size(); i++){
        int p = a[i] + prev2;
        int np = prev1;
        sol = max(p, np);
        prev2 = prev1;
        prev1 = sol;
    }
    return prev1;
}

int main(){
    vector<int> a = {2, 1, 4, 9};
    vector<int> dp(a.size(), -1);
    cout << "Maximum Sum of Non Adjacent elements: " << memoize(3, dp, a) << endl;
    cout << "Maximum Sum of Non Adjacent elements: " << tabulate(3, a) << endl;
    cout << "Maximum Sum of Non Adjacent elements: " << spaceOptimal(3, a) << endl;
    return 0;
}