#include <bits/stdc++.h>
using namespace std;

int check(vector<int>& h){
    int maxi = INT_MIN;
    for(int i = 0; i<h.size(); i++){
        int curr = h[i];
        int mini = h[i];
        for(int j = i+1; j<h.size(); j++){
            mini = min(mini, h[j]);
            curr = max(curr, mini*(j-i+1));
        }
        maxi = max(maxi, curr);
    }
    return maxi;
}

int main(){
    vector<vector<int>> mat = {
        {1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 0, 0, 1, 0}
    };
    int n = mat.size();
    int m = mat[0].size();
    vector<int> h(m, 0);
    int ans = 0;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(mat[i][j] == 1){
                h[i]+=1;
            }
            else{
                h[i] = 0;
            }
        }
        ans = max(ans, check(h));
    }
    cout << "Max Rectangle has " << ans << " ones!" << endl;
    return 0;
}