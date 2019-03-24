// Created by David Zashkolny on 20.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
#include <cstddef>

using namespace std;

const char END = '.';
const char START = ' ';


int *numbers;
char *operations;
int numberCount, operationCount;


struct node{
    node *parent;
    int current_number;
    int depth;
    bool here_operation;
    char operation;
};


struct elementQueue{
    struct node *node;
    elementQueue *next;
};


struct Queue{
    elementQueue *HEAD;
    elementQueue *END;
};


Queue *create(){
    Queue *res;
    res = new Queue;
    res->HEAD = NULL;
    res->END = NULL;
    return res;
}


void enqueue(Queue* &queue, elementQueue* &data){
    if (queue->END == NULL && queue->HEAD == NULL){
        queue->HEAD = data;
        queue->END = data;
    } else {
        queue->END->next = data;
        queue->END = data;
        data->next = NULL;
    }
}


elementQueue* dequeue(Queue* &queue){
    if (queue->HEAD == NULL){
        delete queue;
        return NULL;
    } else{
        elementQueue *tmp = queue->HEAD;
        queue->HEAD = queue->HEAD->next;
        return tmp;
    }
}



bool growArray(bool* array, int *size){
    *size *= 2;
    bool *newArray = new bool[*size];
    for (int i = 0; i < *size; i++){
        newArray[i] = array[i];
    }
    delete[] array;
    return newArray;
}



int doOperation(int a, int b, char operation) {
    if (operation == '+') return a + b;
    else if (operation == '-') return a - b;
    else if (operation == '/') return a / b;
    else return a * b;
}


int res(node* last_node){
    // find temporary result for each node IF HERE DON'T OPERATION
    node *tmp = last_node;
    int res = 0;
    int tmp_token = 0;
    char last_operation = START;
    int multiplicator = 0;

    while (tmp != NULL){
        if (tmp->here_operation && last_operation == START) {
            last_operation = tmp->operation;
            res = tmp_token;
            tmp_token = 0;
        } else if (tmp->here_operation){
            res = doOperation(tmp_token, res, last_operation);
            last_operation = tmp->operation;
            tmp_token = 0;
        } else {
            multiplicator = 1;
            while (multiplicator <= tmp_token) multiplicator *= 10;
            tmp_token = tmp->current_number * multiplicator + tmp_token;
        } tmp = tmp->parent;
    } res = doOperation(tmp_token, res, last_operation);
    return res;
}


int res2(node* last_node){
    // find temporary result for each node IF HERE DON'T OPERATION
    node *tmp = last_node;
    int res = 0;
    int tmp_token = 0;
    char last_operation = START;
    int multiplicator = 0;

    while (tmp != NULL){
        if (tmp->here_operation && last_operation == START) {
            last_operation = tmp->operation;
            res = tmp_token;
            tmp_token = 0;
            cout << tmp->operation;
        } else if (tmp->here_operation){
            res = doOperation(tmp_token, res, last_operation);
            last_operation = tmp->operation;
            tmp_token = 0;
        } else {
            cout << tmp->current_number;
            multiplicator = 1;
            while (multiplicator <= tmp_token) multiplicator *= 10;
            tmp_token = tmp->current_number * multiplicator + tmp_token;
        } tmp = tmp->parent;
    } res = doOperation(tmp_token, res, last_operation);
    return res;
}



int test(){
    node first = {NULL, 1, 0, false, ' '};
    node second = {&first, 1, 1, false, ' '};
    node third = {&second, 0, 2, true, '+'};
    node fourth = {&third, 0, 3, false, ' '};
    node fifth = {&fourth, 0, 4, true, '-'};
    node sixth = {&fifth, 5, 5, false, ' '};
    cout << res(&sixth);
    return 0;
}


int main(){
    bool* used = new bool[2];
    Queue *mainQueue = create();
    elementQueue *tmp;
    node *bestNode;
    int tmp_res;

    int task, steps_amount;
    cin >> numberCount;

    numbers = new int[numberCount];
    for (int i = 0; i < numberCount; i++){
        cin >> numbers[i];
        node *tmpNode = new node;
        tmpNode->parent = NULL;
        tmpNode->operation = false;
        tmpNode->current_number = numbers[i];

        elementQueue *tmpElement;
        tmpElement = new elementQueue;
        tmpElement->node = tmpNode;
        enqueue(mainQueue, tmpElement);
    }

    cin >> operationCount;
    operations = new char[operationCount];
    for (int i = 0; i < operationCount; i++){
        cin >> operations[i];
    }

    cin >> steps_amount >> task;

    while (mainQueue->HEAD != NULL){
        tmp = dequeue(mainQueue);
        if (tmp->node->depth > steps_amount) continue;
        if (!tmp->node->here_operation){
            tmp_res = res(tmp->node);
            if (tmp_res == task){
                bestNode = tmp->node;
                cout << tmp->node->depth + 2 << ' ';
                res2(tmp->node);
                break;
            }

            for (int i = 0; i < operationCount; i++){
                node *tmp_node;
                tmp_node = new node;
                tmp_node->here_operation = true;
                tmp_node->operation = operations[i];
                tmp_node->parent = tmp->node;
                tmp_node->depth = tmp->node->depth + 1;

                elementQueue *newElement;
                newElement = new elementQueue;
                newElement->node = tmp_node;
                enqueue(mainQueue, newElement);
            }

        }

        for (int i = 0; i < numberCount; i++){
            node *tmp_node;
            tmp_node = new node;
            tmp_node->here_operation = false;
            tmp_node->current_number = numbers[i];
            tmp_node->parent = tmp->node;
            tmp_node->depth = tmp->node->depth + 1;

            elementQueue *newElement;
            newElement = new elementQueue;
            newElement->node = tmp_node;
            enqueue(mainQueue, newElement);
        }


    }
}