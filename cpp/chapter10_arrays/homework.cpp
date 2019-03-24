// Created by David Zashkolny on 18.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
using namespace std;


// TODO tasks

void qsort(int *array, int first, int last){
    int mid, tmp;
    int tmp_first = first, tmp_last = last;

    mid = array[(first + last) / 2];
    do {
        while (array[tmp_first] < mid) tmp_first++;
        while (array[tmp_last] > mid) tmp_last--;

        if (tmp_first <= tmp_last){
            tmp = array[tmp_last];
            array[tmp_last] = array[tmp_first];
            array[tmp_first] = tmp;
            tmp_first++;
            tmp_last--;
        }
    } while (tmp_first < tmp_last);

    if (first < tmp_last) qsort(array, first, tmp_last);
    if (tmp_first < last) qsort(array, tmp_first, last);
}


int main(){
    int test[11] = {1, 5, 2, 7, 4, 8, 3, 78, 9, 0, 1};
    qsort(test, 0, 10);
    for (int i = 0; i < 11; i++) cout << test[i] << ' ';
    return 0;
}