// Created by David Zashkolny on 17.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>

using namespace std;


void printList(char array[], int length){
    // function that prints given array of chars

    for (int _i = 0; _i < length; _i++){
        cout << array[_i] << ' ';
    }
    cout << endl;
}


bool inList(const char array[], const char &element, int length){
    // function that checks if an element is in the given array
    // :param array: given array
    // :param element: element to be searched
    // :param length: length of the array
    bool res = false;
    for (int _i = 0; _i < length; _i++){
        if (element == array[_i]){
            res = true;
            break;
        }
    }
    return res;
}


int main() {
    // ============================================
    // 99 bottles on the wall
    cout << "\n\n--------------task1---------------" << endl;

    for (int i = 100; i > 0; i--) {
        cout << i << " bottles of beer on the wall, " << i << " bottles of beer" << endl;
        cout << "Take one down, pass it around, " << i - 1 << " bottles of beer on the wall" << endl;
    }

    // ============================================
    // program-menu, where user must choose one of different variants from the list
    // if user chose incorrect variant - print list again
    cout << "\n\n--------------task2---------------" << endl;

    char variants[5] = {'1', '2', '3', '4', '5'};
    char userVariant;
    cout << "Please, choose any variant from the list" << endl;

    while (true) {
        cout << "list: ";
        printList(variants, 4);
        cin >> userVariant;
        if (inList(variants, userVariant, 4)) break;
        else cout << "try again" << endl;
    }

    // ===========================================
    // calculate the sum of all of the numbers user wrote while he doesn't write 0
    cout << "\n\n--------------task3---------------" << endl;

    int sum = 0;
    int currNumber;
    do {
        cout << "\nCurrent sum = " << sum << endl;
        cout << "Please, enter the number (0 for exit):\n--> ";
        cin >> currNumber;
        sum += currNumber;
    } while (currNumber != 0);

    // ===========================================
    // it is checking user password again
    cout << "\n\n--------------task4---------------" << endl;

    string password = "qwerty";
    string userPassword;
    bool success = false;
    cout << "Please, enter your password:" << endl;
    for (int i = 5; i > 0; i--) {
        cout << "--> ";
        cin >> userPassword;
        if (userPassword == password) {
            cout << "Welcome!" << endl;
            success = true;
            break;
        } else cout << "attempts left: " << i - 1 << endl;
    }
    if (!success)
        cout << "Get out here!" << endl;


    // ===========================================
    // task 5 so easy

    // ===========================================
    cout << "\n\n--------------task6---------------" << endl;

    cout << "Here are the squares of the first 20 numbers" << endl;
    for (int i = 1; i <= 20; i++){
        cout << i * i << endl;
    }
}
