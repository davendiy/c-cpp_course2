// Created by David Zashkolny on 20.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//


#include <cstddef>
#include <iostream>


struct listElement{
    int data;
    listElement *pre;
    listElement *next;
};


struct List{
    listElement *HEAD;
    listElement *Current;
    listElement *END;
};


List *createEmptyList(){
    listElement *tmp;
    tmp = new listElement;
    List *res = new List;
    res->Current = tmp;
    res->END = tmp;
    res->HEAD = tmp;
    return res;
}


void appendLeft(List* &list, int data){
    listElement *list_end = list->END;
    listElement *new_element;
    new_element = new listElement;
    new_element->data = data;
    new_element->pre = list_end;
    new_element->next = NULL;
    list_end->next = new_element;
    list->END = new_element;
}


void appendRight(List* &list, int data){
    listElement *list_head = list->HEAD;
    listElement *new_element;
    new_element = new listElement;
    new_element->data = data;
    new_element->next = list_head;
    new_element->pre = NULL;
    list_head->pre = new_element;
    list->HEAD = new_element;
}
