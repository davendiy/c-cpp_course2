#include "tensor.h"
#include <cassert>

// TODO I LIKE THIS SMELL OF DEBUGGING IN THE EVENING


int main(){

    auto *test_shape = new ARRAY_SIZE[2];
    test_shape[0] = 2;
    test_shape[1] = 2;

    Tensor<int> test(2, test_shape);

    auto *test_shape2 = new ARRAY_SIZE[1];
    test_shape2[0] = 4;
    test.reshape(1, test_shape2);
}