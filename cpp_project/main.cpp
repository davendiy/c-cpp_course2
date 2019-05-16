#include "tensor.hxx"
#include <cassert>


int main(){

    auto *test_shape = new ARRAY_SIZE[2];
    test_shape[0] = 2;
    test_shape[1] = 2;

    Tensor<int> test(2, test_shape);
    test[0][0] = Tensor<int>(1);
    test[0][1] = Tensor<int>(2);
    test[1][0] = Tensor<int>(3);
    test[1][1] = Tensor<int>(4);
    test.print();

    auto *test_shape2 = new ARRAY_SIZE[1];
    test_shape2[0] = 4;
    test.reshape(1, test_shape2);
    test.print();
    cutting cut1;
    cut1.start = 3;
    cut1.end = -1;
    cut1.step = -1;
    test[&cut1].print();

    auto sum = test + test[&cut1];
    sum.print();

    test[0] = Tensor<int>(5);
    test[1] = Tensor<int>(6);
    test.print();

    test.reshape(2, test_shape);

    test_shape = new ARRAY_SIZE[3];
    test_shape[0] = 3;
    test_shape[1] = 2;
    test_shape[2] = 2;
    Tensor<int> test2(3, test_shape);

    test2[0] = test;
    test2.print();

    cutting tmp;
    tmp.start = 2;
    tmp.end = -1;
    tmp.step = -2;
    auto test3 = test2[&tmp];
    test3.print();

}