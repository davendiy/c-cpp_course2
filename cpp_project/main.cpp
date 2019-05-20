// Created by David Zashkolny on 14.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include "src/tensor.hxx"
#include <iostream>
#include <fstream>

using namespace std;

typedef int TEST_TYPE;


/* read tensor's values from the file
 * @param tensor: tensor;
 * @param file: file where N1*N2*..*NN numbers have been written, separated by space or enter */
void readTensor(Tensor<TEST_TYPE> &tensor, ifstream &file){
    if (tensor.dimension() == 1){
        TEST_TYPE tmp;
        for (ARRAY_SIZE itr = 0; itr < tensor.shape()[0] && file >> tmp; ++itr){
            tensor[itr] = Tensor<TEST_TYPE >(tmp);
        }
    } else {
        for (ARRAY_SIZE itr = 0; itr < tensor.shape()[0]; ++itr){
            readTensor(tensor[itr], file);
        }
    }
    if (file.fail() && !file.eof()) throw domain_error("Couldn't read information from file");
}

/* read tensor's parameters, create one and read its values from the file.
 * @param file: file where N1*N2*..*NN numbers have been written, separated by space or enter */
Tensor<TEST_TYPE > &loadFromFile(ifstream &file){
    ARRAY_SIZE dim;
    if (file >> dim && dim > 0){
        auto *shape = new ARRAY_SIZE[dim];
        for (ARRAY_SIZE itr = 0; itr < dim && file >> shape[itr]; ++itr);
        if (file.fail() && !file.eof()) throw domain_error("Couldn't read information from file");

        auto res = new Tensor<TEST_TYPE >(dim, shape);
        readTensor(*res, file);
        return *res;
    } else {
        throw domain_error("Bad file");
    }
}



int main() {
    char mod;

    cout << "Do you want to input arrays from file?(y/n)\n--> ";
    cin >> mod;
    if (mod == 'y' || mod == 'Y'){
        ifstream inputFile("../input.txt", ios::in);
        if (!inputFile.is_open()){
            cout << "Could not open the file";
            return 0;
        }

        auto testTensor1 = loadFromFile(inputFile);
        auto testTensor2 = loadFromFile(inputFile);
        testTensor1.print();
        testTensor2.print();
    }
}