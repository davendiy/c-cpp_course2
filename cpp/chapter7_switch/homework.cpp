// Created by David Zashkolny on 18.02.19.
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

    switch (operation){
        case '+':
            cout << "result: " << a + b << endl;
            break;
        case '-':
            cout << "result: " << a - b << endl;
            break;
        case '/':
            cout << "result: " << a / b << endl;
            break;
        case '*':
            cout << "result: " << a * b << endl;
            break;
        default:
            cout << "incorrect operation, sry)" << endl;
    }

}


int main(){
    // ============================================
    // user menu again
    cout << "\n\n--------------task1---------------" << endl;
    bool exit = false;
    char userVar;
    while (true){
        cout << "Please, choose one of the possible functions "
                "(1 - bottles, 2 - calculator, 3 - print('hello world'), 0 - exit\n--> ";
        cin >> userVar;

        switch (userVar) {
            case '1':
                printBottles();
                break;
            case '2':
                calculator();
                break;
            case '3':
                cout << "Hello world!" << endl;
                break;
            case '0':
                exit = true;
                break;
            default:
                cout << "incorrect function, try again";
        }

        if (exit) break;
    }

    // i think, that tasks 2 and 3 are not important, its so bored
}