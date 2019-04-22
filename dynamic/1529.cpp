// Created by David Zashkolny on 13.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <string>
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

double task(string &input_str, double **dp, unsigned long l, unsigned long r){

    if (dp[l][r] != -1) return dp[l][r];
    unsigned long index1 = input_str.find('.', l);
    if (index1 == string::npos || index1 > r){
        dp[l][r] = sqrt(r - l + 1);
        return dp[l][r];
    }
    unsigned long index2 = input_str.find('X', l);
    if (index2 == string::npos || index2 > r){
        dp[l][r] = 0;
        return 0;
    }

    double res_min = sqrt(r - l + 1);
    for (unsigned long i = l; i < r; i++){
        double tmp = task(input_str, dp, i + 1, r) + task(input_str, dp, l, i);
        if (tmp < res_min) {
            res_min = tmp;
        }
    }
    dp[l][r] = res_min;
    return res_min;
}


double task2(string &input_str, double **dp){
    unsigned long n = input_str.size();

    for (unsigned long i = 0; i < n; i++){
        if (input_str[i] == '.') dp[i][i] = 0;
        else dp[i][i] = 1;
    }

    for (unsigned long i = n-1; i > 0; i--){
        unsigned long cur_x = 0;
        unsigned long cur_y = n - i;
        for (unsigned long j = 0; j < i; j++){
            double res = sqrt(cur_y - cur_x + 1);

            for (unsigned long k = 0; k < (cur_y - cur_x); k++){
                double tmp_res = dp[cur_x][cur_x + k] + dp[cur_x + k + 1][cur_y];
                if (tmp_res < res){
                    res = tmp_res;
                }
            }
            dp[cur_x][cur_y] = res;
            cur_x++;
            cur_y++;
        }
    }
    return dp[0][n - 1];
}


double **create_array(unsigned long n){
    double **array;
    array = new double*[n];
    for (unsigned long i = 0; i < n; i++){
        array[i] = new double[n];
        for (unsigned long j = 0; j < n; j++){
            array[i][j] = -1;
        }
    }
    return array;
}


void destroy(double **array, unsigned long n){
    for (unsigned long i = 0; i < n; i++){
        delete array[i];
    }
    delete array;
}


int main(){
    string test;
    unsigned long len = 0;
    double **dp;
    dp = create_array(3000);
    while (true){
        getline(cin, test, '\n');
        if (test.empty()) break;

        double result = task2(test, dp);

        printf("%.4lf", result);
        printf("\n");
    }
    destroy(dp, 2500);
}