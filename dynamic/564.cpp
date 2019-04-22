// Created by David Zashkolny on 15.04.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#define INT long long int

#include <math.h>
#include <iostream>
using namespace std;


INT ***create_array(INT n){

    INT ***dp = new INT**[n];
    for (INT i = 0; i < n; i++) {
        dp[i] = new INT *[4];
        for (int j = 0; j <= 4; j++) {
            dp[i][j] = new INT[2];

            dp[i][j][0] = dp[i][j][1] = -1;
        }
    }
    return dp;
}


INT task(INT ***dp, INT n, INT amount, INT ge){

    if (dp[n][amount][ge] != -1){
        return dp[n][amount][ge];
    }

    if (amount == 1){
        double tmp_n = sqrt(n);
        bool perfect_int = tmp_n - floor(tmp_n) == 0;
        if (perfect_int){
            dp[n][amount][ge] = dp[n][amount][1 - ge] = 1;
            return 1;
        } else {
            dp[n][amount][ge] = dp[n][amount][1 - ge] = 0;
            return 0;
        }
    }

    INT result = 0;

    if (ge == 0){
        for (int j = 1; j <= amount; j++){
            result += task(dp, n, j, 1);
        }
    } else {
        for (INT i = 1; i < n/2+1; i++){
            result += task(dp, i, 1, 1) * task(dp, n-i, amount-1, 1);
        }
    }
    dp[n][amount][ge] = result;
    return result;
}


int main(){
    INT ***array = create_array(1 << 15);
    int AMOUNT;
    INT n;
    cin >> AMOUNT;
    for (int i = 0; i < AMOUNT; i++){
        cin >> n;
        cout << task(array, n, 4, 0) << endl;
    }
}