// Created by David Zashkolny on 20.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
using namespace std;


int **createArray(int size1, int size2){

    int **array = new int*[size1];
    for (int i = 0; i < size1; i++){
        array[i] = new int[size2];
    }
    return array;
}


void printArray(int **p_p_array, int size1, int size2){
    cout << "Array:" << endl;
    for (int i = 0; i < size1; i++){
        for (int j = 0; j < size2; j++) cout << p_p_array[i][j] << ' ';
        cout << endl;
    }
}


void destroyArray(int **p_p_array, int size1){
    for (int i = 0; i < size1; i++){
        delete[] p_p_array[i];
    }
    delete[] p_p_array;
}


int main(){
    int n;
    int **cayley_table;

    cout << "please, enter the size of an array: ";
    cin >> n;

    cayley_table = createArray(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cayley_table[i][j] = (i+1) * (j+1);
        }
    }

    printArray(cayley_table, n, n);
    destroyArray(cayley_table, n);
}