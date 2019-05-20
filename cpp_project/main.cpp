#include "src/tensor.hxx"
#include <cassert>


int main(){

    auto *shape = new ARRAY_SIZE[3];
    shape[0] = 3;
    shape[1] = 10;
    shape[2] = 10;
    Tensor<float> test1(3, shape);
    Tensor<float> test2(3, shape);

    test1 = test1 + 1;
    test1.print();

    int x = 0;
    int y = 300;
    for (int i = 0; i < shape[0]; i++){
        for (int j = 0; j < shape[1]; j++) {
            for (int k = 0; k < shape[2]; k++) {
                test1[i][j][k] = Tensor<float>(x);
                test2[i][j][k] = Tensor<float>(y);
                x++;
                y--;
            }
        }
    }

    test1.print();
    test2.print();

    auto tmp = test1 + test2;
    tmp.print();
    tmp = test1 - test2;
    tmp.print();
    tmp = test1 * test2;
    tmp.print();
    tmp = test1 / test2;
    tmp.print();

    tmp = test1 / 3;
    tmp.print();
}