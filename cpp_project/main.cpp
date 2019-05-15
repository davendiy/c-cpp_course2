#include <iostream>
#include "tensor.h"
#include <cassert>

int main(){

    void *test;
    test = reinterpret_cast<void*>(createNDimArray<INT>(8));
}