// Created by David Zashkolny on 14.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#ifndef CPP_PROJECT_TENSOR_H
#define CPP_PROJECT_TENSOR_H

#include <iostream>

typedef int ARRAY_SIZE;
typedef int INT;
typedef float FLOAT;


// ====================================== N_DIM_ARRAY ==================================================================

template<typename TYPE>
struct MemoryItem{
    TYPE value;
    MemoryItem *next;
};


struct cutting{
    ARRAY_SIZE start = 0;
    ARRAY_SIZE end = 0;
    ARRAY_SIZE step = 1;
};

// ================================== TENSOR ===========================================================================

template<typename TYPE>
class Tensor{
public:
    Tensor();
    Tensor(ARRAY_SIZE dimension, const ARRAY_SIZE *shape);
    explicit Tensor(TYPE element);
    Tensor(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape);
    void reshape(ARRAY_SIZE new_dimension, const ARRAY_SIZE *new_shape);
//    ~Tensor();

    TYPE* chain();

    Tensor<TYPE> &operator=(const Tensor<TYPE> &other);
    Tensor<TYPE> &operator[](ARRAY_SIZE n);
    Tensor<TYPE> &operator[](cutting *cut);
    Tensor<TYPE> &copy();

    void print();

private:
    ARRAY_SIZE mDimension = 0;
    MemoryItem<TYPE> *mArray;
    ARRAY_SIZE *mShape;

    MemoryItem<TYPE> *createNDimArray(ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel);
    MemoryItem<TYPE> *createNDimArray(ARRAY_SIZE dimension, const ARRAY_SIZE *shape);

    MemoryItem<TYPE> *copyNDimArray(MemoryItem<TYPE> *array,
                                    ARRAY_SIZE dimension,
                                    const ARRAY_SIZE *shape,
                                    ARRAY_SIZE dimLevel);

    void deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel);
    void deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape);
    void createChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *resArray, ARRAY_SIZE &startIndex);
    void fillArrayFromChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *_chain,
                            ARRAY_SIZE &startIndex);

    void printNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel);

    void copyValues(MemoryItem<TYPE> *array1, MemoryItem<TYPE> *array2, ARRAY_SIZE dimension, const ARRAY_SIZE *shape,
                    ARRAY_SIZE dimLevel);
};


#endif //CPP_PROJECT_TENSOR_H