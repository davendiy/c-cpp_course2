// Created by David Zashkolny on 16.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
using namespace std;

int main() {

    // ===========================================================
    // input 2 ages and print the one that older
    // if both of them are older than 100 - do smth else
    cout << "\n------------------task1-------------------" << endl;
    int age1, age2;
    cout << "Please, enter the age of 2 people:\n--> ";
    cin >> age1;
    cout << "--> ";
    cin >> age2;

    if (age1 > age2) cout << "First human is older" << endl;
    else if (age2 > age1) cout << "Second human is older" << endl;
    else if (age1 == age2) cout << "They are peers" << endl;

    if (age1 > 100 && age2 > 100) cout << "They both older than 100, so the program have to do smth else" << endl;

    // ===========================================================
    // input number and check if it is same with one of 2 passwords
    cout << "\n------------------task2-------------------" << endl;
    int password1 = 123141;
    int password2 = 2;
    int user_password;
    cout << "Please, enter the password\n--> ";
    cin >> user_password;
    if (user_password == password1 || user_password == password2) cout << "Access is allowed" << endl;
    else cout << "Password is wrong!" << endl;

    // ===========================================================
    // simple calculator
    // input any of 4 standard operation and 2 numbers
    // print the result of operation
    cout << "\n------------------task3-------------------" << endl;
    char operation;
    cout << "Please, enter the arithmetic operation ('+', '-', '/', '*')\n--> ";
    cin >> operation;

    float a, b;
    cout << "Please, enter the 2 numbers:\n--> ";
    cin >> a;
    cout << "--> ";
    cin >> b;

    if (operation == '+') cout << "result: " << a + b << endl;
    if (operation == '-') cout << "result: " << a - b << endl;
    if (operation == '/') cout << "result: " << a / b << endl;
    if (operation == '*') cout << "result: " << a * b << endl;

    // ===========================================================
    // extension of task2
    // there are 4 different users with own passwords
    // user must input his name and his password (he has 2 attempts)
    cout << "\n------------------task3-------------------" << endl;

    string names[4] = {"name1", "name2", "name3", "name4"};
    string passwords[4] = {"password", "1234", "2288", "qwerty"};

    string username;
    string password;
    bool flag = false;
    for (int i = 0; i < 2; i++)
    {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (int j = 0; j < 4; j++)
            if (names[j] == username && passwords[j] == password)
            {
                cout << "Welcome, " << username << endl;
                flag = true;
                break;
            }
        if (flag) break;
        else cout << "Try again" << endl;
    }

    if (!flag) cout << "Get out here!" << endl;

}