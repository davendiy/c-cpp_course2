// Created by David Zashkolny on 20.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//


#include <iostream>
using namespace std;

int *growArray(const int *p_array, int *size);

void printArray(int *p_array, int size, int elements_set);


int main(){
    int next_element = 0;
    int size = 10;
    int *p_values = new int[size];
    int val;

    cout << "please, enter a number: ";
    cin >> val;
    while (val > 0){
        if (size == next_element + 1){
            p_values = growArray(p_values, &size);
        }
        p_values[next_element] = val;
        cout << "\n\nCurrent array values are: " << endl;
        printArray(p_values, size, next_element);
        cout << "\nPlease, enter the next element: ";
        cin >> val;
        next_element++;
    }

    delete[] p_values;
}


void printArray(int *p_array, int size, int elements_set){
    cout << "the total size of an array: " << size << endl;
    cout << "the last filled index of an array: " << elements_set << endl;
    cout << "values in array:" << endl;
    for (int i = 0; i <= elements_set; i++){
        cout << p_array[i] << ' ';
    }
}


int *growArray(const int *p_array, int *size) {
    *size *= 2;
    int *p_new_array = new int[*size];
    for (int i = 0; i < *size; i++) {
        p_new_array[i] = p_array[i];
    }
    delete[] p_array;
    return p_new_array;
}