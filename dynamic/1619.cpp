// Created by David Zashkolny on 08.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
using namespace std;


int main(){

    long long n;
    long long *array;
    long long *dp;
    bool *latest_used;
    cin >> n;
    array = new long long[n];
    dp = new long long[n];
    latest_used = new bool[n];
    for (int i = 0; i < n; i++){
        cin >> array[i];
    }

    dp[0] = array[0];
    latest_used[0] = true;
    if (array[0] > array[1]){
        dp[1] = array[0];
        latest_used[1] = false;
    } else {
        dp[1] = array[1];
        latest_used[1] = true;
    }

    for (long long i = 2; i < n; i++){
        if (latest_used[i-1]){
            dp[i] = dp[i-1];
            latest_used[i] = false;
        } else {
            dp[i] = dp[i-1] + array[i];
            latest_used[i] = true;
        }
        if (array[i] + dp[i-2] > dp[i]) {
            dp[i] = array[i] + dp[i - 2];
            latest_used[i] = true;
        }
        if (!latest_used[i-2] && array[i-1] + dp[i-2] > dp[i]){
            dp[i] = array[i-1] + dp[i-2];
            latest_used[i] = false;
        }
    }
    cout << dp[n-1];
}