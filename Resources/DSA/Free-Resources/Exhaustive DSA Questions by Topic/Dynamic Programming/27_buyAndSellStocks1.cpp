#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> arr = {7, 1, 5, 3, 6, 4};
    
    int mini = arr[0];
    int profit = 0;
    for(int i = 1; i<arr.size(); i++){
        int cost = arr[i] - mini;
        profit = max(profit, cost);
        mini = min(mini, arr[i]);
    }

    cout << "Maximum profit: " << profit << endl;
    
    return 0;
}