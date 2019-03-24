// Created by David Zashkolny on 20.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
using namespace std;


void swap1(int a, int b){
    int tmp = a;
    a = b;
    b = tmp;
}


void swap2(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void swap3(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}


int main(){
    int *p_pointer2int = NULL;
    int *pointer = NULL, nonPointer;
    int x = 10;

    p_pointer2int = &x;

    cout << p_pointer2int << ' ' << *p_pointer2int << endl;
    cout << &x << ' ' << x << endl;
    *p_pointer2int = 2;

    cout << x << endl;

    cout << "\n\n\n\n\n";

    int test_a, test_b;
    cout << "--> ";
    cin >> test_a >> test_b;

    swap1(test_a, test_b);
    cout << test_a << " " << test_b << endl;

    swap2(&test_a, &test_b);
    cout << test_a << ' ' << test_b << endl;

    swap3(test_a, test_b);
    cout << test_a << ' ' << test_b << endl;

    int original = 10;
    int &copy = original;

    copy = 20;
    cout << original;
}
