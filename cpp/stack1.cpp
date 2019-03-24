// Created by David Zashkolny on 20.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <cstddef>
#include <iostream>

using namespace std;


struct stackElement{
    int value;
    stackElement *next;
};


stackElement* createStack(int data){
    stackElement* tmp;
    tmp = new stackElement;
    tmp->next = NULL;
    tmp->value = data;
    return tmp;
}


void push(stackElement* &stack, int data){
    stackElement *newElement = createStack(data);
    newElement->next = stack;
    stack = newElement;
}


int pop(stackElement* &stack){
    int res = stack->value;
    stackElement *tmp = stack;
    stack = stack->next;
    delete tmp;
    return res;
}


int main(){
    stackElement* test = createStack(0);
    push(test, 1);
    push(test, 2);
    push(test, 3);

    int tmp = pop(test);
    cout << "your stack:" << endl;
    while (test != NULL){
        cout << tmp << ' ';
        tmp = pop(test);
    }
}

