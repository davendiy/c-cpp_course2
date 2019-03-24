// Created by David Zashkolny on 23.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

// testing of vectorOfInt

#include "vectorOfInt.h"
#include <iostream>
using namespace myVector;


void print_array(vectorOfInt &array){
    for (VECTOR_INT i = 0; i < array.size(); i++){
        std::cout << array.get(i) << ' ';
    }
    std::cout << std::endl;
}



int main(){

    VECTOR_INT n;
    std::cout << "please, enter the amount of elements in the array:" << std::endl;
    std::cin >> n;
    vectorOfInt test (n);
    for (VECTOR_INT i = 0; i < n; i++){
        int tmp;
        std::cout << "a[" << i <<"] = ";
        std::cin >> tmp;
        test.set(i, tmp);
    }

    test.push_back(10);
    print_array(test);
    test.push_front(-100);
    print_array(test);

    vectorOfInt second = test;
    std::cout << "second:" << std::endl;
    print_array(second);
    return 0;
}