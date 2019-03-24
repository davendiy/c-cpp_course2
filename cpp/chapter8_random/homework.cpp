// Created by David Zashkolny on 18.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;


int randRange(int low, int high){
    return rand() % (high - low + 1) + low;
}


// TODO task 1-5


int main(){
    srand(time(NULL));
    for (int i = 0; i < 5; i++){
        cout << randRange(10, 100);
    }
}