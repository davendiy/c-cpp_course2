// Created by David Zashkolny on 05.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//


#include <vector>
#include <iostream>
#include <map>
using namespace std;

void printMap(map<string, string> map_to_print);


int main(){
    vector<int> test(10);
    int i = 0;
    for (vector<int>::iterator itr = test.begin(), end = test.end(); itr != end; ++itr){
        *itr = i;
        i++;
    }
    for (vector<int>::iterator itr = test.begin(), end = test.end(); itr != end; ++itr){
        cout << *itr << endl;
    }
}


void printMap(map<string, string> map_to_print){
    for (map<string, string>::iterator itr = map_to_print.begin(), end = map_to_print.end(); itr != end; ++itr){
        cout << itr->first << ' ' << itr->second;
    }
}