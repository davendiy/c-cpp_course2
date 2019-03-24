// Created by David Zashkolny on 08.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
#include <string>
#include <sstream>
using namespace std;


int min(int a, int b){
    if (a > b){
        return b;
    } else {
        return a;
    }
}


int task(int n){

    int *dp = new int[n+1];
    dp[0] = 0;
    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 1;
    int tmp1, tmp2;
    for (int i = 4; i <= n; i++){
        tmp1 = dp[i-1];
        tmp2 = dp[i-1];
        if (i % 2 == 0){
            tmp1 = dp[i / 2];
        }
        if (i % 3 == 0){
            tmp2 = dp[i / 3];
        }
        dp[i] = min(min(tmp1, tmp2), dp[i-1]) + 1;
    }
    return dp[n];
}


int main(){
    string n;
    int param;
    int res;

    while (true){
        getline(cin, n);
        if (n.empty()){
            break;
        }

        istringstream iss(n);
        iss >> param;
        cout << task(param) << endl;
    }
}