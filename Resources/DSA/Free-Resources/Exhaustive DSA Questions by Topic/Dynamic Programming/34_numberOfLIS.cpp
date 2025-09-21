#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> a = {1, 5, 4, 3, 2, 6, 7, 10, 9, 1};
    int n = a.size();
    vector<int> dp(n, 1);
    vector<int> ct(n, 1);
    int count = 0;
    int maxi = 1;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<i; j++){
            if(a[j] < a[i]){
                if(dp[i] < dp[j] + 1){
                    dp[i] = dp[j] + 1;
                    ct[i]=ct[j];
                }
                else if(dp[i] == dp[j] + 1){
                    ct[i]+=ct[j];
                }
            }
        }
        maxi = max(maxi, dp[i]);
    }
    for(int i = 0; i<n; i++){
        if(dp[i] == maxi){
            count+=ct[i];
        }
    }
    cout << "Number of LIS: " << count << endl;
    return 0;
}