// Created by David Zashkolny on 16.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
using namespace std;

int main(){
    // ===========================================
    cout << "-----task 1--------" << endl;
    cout << "David Zashkolny" << endl;

    // ===========================================
    cout << "\n-----task 2--------" << endl;

    int a, b;
    cout << "Please, enter the 2 numbers:\n--> ";
    cin >> a;
    cout << "--> ";
    cin >> b;
    int c = a + b;
    cout << a << " + " << b << " = " << c << endl;

    // ===========================================
    cout << "\n-----task 3--------" << endl;

    float a2, b2;
    cout << "Please, enter the 2 numbers:\n--> ";
    cin >> a2;
    cout << "--> ";
    cin >> b2;
    float c2 = a2 / b2;
    cout << a2 << " / " << b2 << " = " << c2 << endl;
    return 0;
}