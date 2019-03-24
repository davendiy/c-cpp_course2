// Created by David Zashkolny on 17.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
using namespace std;


void printBottles(){
    // ask user amount of bottles and print respectively number
    // of lines of song 'N bottles of beer on the wall'
    int amount;
    cout << "Please, enter the number of bottles\n--> ";
    cin >> amount;
    for (int i = amount; i > 0; i--) {
        cout << i << " bottles of beer on the wall, " << i << " bottles of beer" << endl;
        cout << "Take one down, pass it around, " << i - 1 << " bottles of beer on the wall" << endl;
    }
}


void calculator(){
    char operation;
    cout << "Please, enter the arithmetic operation ('+', '-', '/', '*')\n--> ";
    cin >> operation;

    float a, b;
    cout << "Please, enter the 2 numbers:\n--> ";
    cin >> a;
    cout << "--> ";
    cin >> b;

    if (operation == '+') cout << "result: " << a + b << endl;
    else if (operation == '-') cout << "result: " << a - b << endl;
    else if (operation == '/') cout << "result: " << a / b << endl;
    else if (operation == '*') cout << "result: " << a * b << endl;
    else cout << "incorrect operation, sry)" << endl;
}


int main(){
    // ============================================
    // user menu again
    cout << "\n\n--------------task1---------------" << endl;

    char userVar;
    while (true){
        cout << "Please, choose one of the possible functions "
                "(1 - bottles, 2 - calculator, 3 - print('hello world'), 0 - exit\n--> ";
        cin >> userVar;
        if (userVar == 1) printBottles();
        else if (userVar == 2) calculator();
        else if (userVar == 3) cout << "Hello world" << endl;
        else if (userVar == 0) break;
        else cout << "incorrect function, try again" << endl;
    }

    // i think, that tasks 2 and 3 are not important, its so bored
}