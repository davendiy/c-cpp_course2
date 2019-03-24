// Created by David Zashkolny on 06.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
using namespace std;

void quicksort(int *mas, int first, int last){
    int mid, count;
    int f = first, l = last;
    mid = mas[(f + l) / 2]; // вычисление опорного элемента
    do {
        while (mas[f] < mid) f++;
        while (mas[l] > mid) l--;
        // перестановка элементов
        if (f <= l){
            count = mas[f];
            mas[f] = mas[l];
            mas[l] = count;
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) quicksort(mas, first, l);
    if (f < last) quicksort(mas, f, last);
}

int min(int a, int b){
    if (a < b){
        return a;
    } else {
        return b;
    }
}


int dp2(const int* array, int len){
    int *dp = new int[len];
    dp[0] = 0;
    if (len >= 2) {
        dp[1] = array[1] - array[0];
    }

    if (len >= 3) {
        dp[2] = array[2] - array[0];
        for (int i = 3; i < len; i++) {
            dp[i] = min(dp[i-1], dp[i-2]) + array[i] - array[i-1];
        }
    }

    return dp[len-1];
}


int main(){
    int *task_arr;
    int n;
    cin >> n;
    task_arr = new int[n];
    for (int i = 0; i < n; i++) cin >> task_arr[i];
    quicksort(task_arr, 0, n-1);
//    for (int i = 0; i < n; i++) cout << task_arr[i] << ' ';
    cout << dp2(task_arr, n);
}