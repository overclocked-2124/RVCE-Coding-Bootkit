#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int last, vector<vector<int>>& dp, vector<vector<int>>& points){
    if(i == 0){
        int maxi = -1;
        for(int j = 0; j<3; j++){
            if(last != j){
                maxi = max(maxi, points[0][j]);
            }
        }
        return maxi;
    }
    if(dp[i][last] != -1) return dp[i][last];
    int maxi = -1;
    for(int j = 0; j<3; j++){
        if(last != j){
            int temp = points[i][j] + memoize(i-1, j, dp, points);
            maxi = max(maxi, temp);
        }
    }
    return dp[i][last] = maxi;
}

int tabulate(vector<vector<int>> points){
    vector<vector<int>> dp(points.size(), vector<int>(4, -1));
    // Base Cases
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));
    // Bottom Up Approach
    cout << "DP ARRAY: " << endl;
    for(int day = 1; day <points.size(); day++){
        for(int last = 0; last<4; last++){
            for(int i = 0; i<3; i++){
                if(last != i){
                    dp[day][last] = max(dp[day][last], points[day][i] + dp[day-1][i]);
                }
            }
            cout << dp[day][last] << " ";
        }
        cout << endl;
    }
    return dp[points.size()-1][3];
}

int spaceOptimal(vector<vector<int>> points){
    vector<int> prev(4, 0);
    // Base Cases
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max(points[0][0], max(points[0][1], points[0][2]));
    for(int day = 1; day <points.size(); day++){
        vector<int> temp(4, 0); 
        for(int last = 0; last<4; last++){
            for(int i = 0; i<3; i++){
                if(last != i){
                    // Compute the points earned on current day when task done on next day will be last
                    // it is equal to points earned by doing some other task on current day + calculation of
                    temp[last] = max(temp[last], points[day][i] + prev[i]);
                }
            }
        }
        prev = temp;
    }
    return prev[3];
}

int main(){
    vector<vector<int>> points = {
        {10, 40, 70},
        {20, 50, 80},
        {30, 60, 90}
    };
    int n = points.size();
    vector<vector<int>> dp(n, vector<int>(4, -1));
    cout << "Maximum points the Ninja can earn: " << memoize(n-1, 3, dp, points) << endl;
    cout << "Maximum points the Ninja can earn: " << tabulate(points) << endl;
    cout << "Maximum points the Ninja can earn: " << spaceOptimal(points) << endl;
}