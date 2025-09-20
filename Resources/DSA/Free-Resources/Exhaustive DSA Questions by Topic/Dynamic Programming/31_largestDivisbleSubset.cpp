#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int>& a){
    int n = a.size();
    if(n <= 1) return a;
    sort(a.begin(), a.end());
    vector<int> dp(n, 1);
    vector<int> hash(n, 0);
    int last = -1;
    int maxi = -1;
    for(int i = 0; i<n; i++){
        hash[i] = i;
    }
    for(int i = 1; i<n; i++){
        for(int j = 0; j<i; j++){
            if(a[i] % a[j] == 0 && dp[i] < dp[j] + 1){
                dp[i] = 1 + dp[j];
                hash[i] = j;
            }
            if(dp[i] > maxi){
                maxi = dp[i];
                last = i;
            }
        }
    }
    vector<int> temp;
    temp.push_back(a[last]);
    while(hash[last] != last){
        last = hash[last];
        temp.push_back(a[last]);
    }
    reverse(temp.begin(), temp.end());
    return temp;
}

int main(){
    vector<int> a = {1, 16, 4, 7, 8};
    vector<int> ans = solve(a);
    for(int i = 0; i<ans.size(); i++){
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}