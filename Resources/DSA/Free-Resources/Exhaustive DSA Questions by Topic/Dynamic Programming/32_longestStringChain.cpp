#include <bits/stdc++.h>
using namespace std;

bool compare(string a, string b){
    if(a.size() != b.size()+1) return false;
    int f = 0, s = 0;
    while(f<a.size()){
        if(a[f] == b[s]){
            f++;
            s++;
        }
        else f++;
    }
    if(f == a.size() && s == b.size()) return true;
    return false;
}

bool sortcomp(string a, string b){
    return a.size() < b.size();
}

int solve(vector<string>& w){
    if(w.size() <= 1){
        return w.size();
    }
    sort(w.begin(), w.end(), sortcomp);
    vector<int> dp(w.size(), 1);
    int maxi = -1;
    for(int i = 1; i<w.size(); i++){
        for(int j = 0; j<i; j++){
            if(compare(w[i], w[j]) && dp[i] < dp[j] + 1){
                dp[i] = dp[j] + 1;
            }
            maxi = max(maxi, dp[i]);
        }
    }
    return maxi;
}

int main(){
    vector<string> w = {"a", "b", "ab", "abc", "bca", "bcda"};
    int ans = solve(w);
    cout << ans << endl;
    return 0;
}