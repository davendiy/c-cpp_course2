// Created by David Zashkolny on 20.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>

using namespace std;

// TODO доробити
int task(int size, int* t_array, int* l_array){
    return 0;
}


int main(){

    int tasks, amount;
    int *t_array, *l_array;

    cin >> tasks;
    for (int i = 0; i < tasks; i++){
        cin >> amount;

        t_array = new int[amount];
        l_array = new int[amount];
        for (int j = 0; j < amount; j++) cin >> t_array[i] >> l_array[i];


        int answer = task(amount, t_array, l_array);

        cout << '#' << i << ' ' << answer << endl;

        delete[] t_array;
        delete[] l_array;
    }

}