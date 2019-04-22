// Created by David Zashkolny on 23.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
#include "vectorOfInt.h"

using namespace myVector;


// constructor (creates array of 32 elements)
vectorOfInt::vectorOfInt()
    :_vector(NULL)
{
    _vector = new int[32];
    _size = 32;
}


// constructor (creates array of size elements)
vectorOfInt::vectorOfInt(VECTOR_INT size)
    :_vector(NULL)
{
    if (size >= 0){
        _vector = new int[size];
        _size = size;
    }
    else {
        throw 1;
    }
}


// constructor that creates copy of other
vectorOfInt::vectorOfInt(const vectorOfInt& other)
    :_vector(NULL)
{
    _vector = new int[other._size];
    _size = other._size;
    for (VECTOR_INT i = 0; i < _size; i++){
        _vector[i] = other._vector[i];
    }
}


// destructor
vectorOfInt::~vectorOfInt() {
    delete _vector;
}


// analog of vector<int>.push_front
VECTOR_INT vectorOfInt::size() {
    return _size;
}


// analog of the array[key]
int vectorOfInt::get(VECTOR_INT key) {
    if (0 <= key && key < _size){
        return _vector[key];
    }
    else {
        throw 1;
    }
}


// analog of the array[key] = tmp
void vectorOfInt::set(VECTOR_INT key, int value) {
    if (0 <= key && key <= _size){
        _vector[key] = value;
    }
    else {
        throw 1;
    }
}


// analog of vector<int>.push_back
void vectorOfInt::push_back(int value) {
    _growUp();
    _vector[_size-1] = value;

}


// analog of vector<int>.push_front
void vectorOfInt::push_front(int value) {
    _size++;
    int *_tmp_vector = new int[_size];
    _tmp_vector[0] = value;
    for (VECTOR_INT i = 1; i < _size; i++){
        _tmp_vector[i] = _vector[i-1];
    }
    delete _vector;
    _vector = _tmp_vector;
}


// copy of array
vectorOfInt& vectorOfInt::operator=(const vectorOfInt &other) {
    if (this == &other){
        return *this;
    }

    delete _vector;
    _vector = new int[other._size];
    _size = other._size;
    for (VECTOR_INT i = 0; i < _size; i++){
        _vector[i] = other._vector[i];
    }
    return *this;
}


// resize array of length _size into array of length _size + 4096
void vectorOfInt::_growUp() {
    int *_tmp_vector = new int[_size + 1];
    for (VECTOR_INT i = 0; i < _size; i++){
        _tmp_vector[i] = _vector[i];
    }
    delete _vector;
    _vector = _tmp_vector;
    _size += 1;
}
