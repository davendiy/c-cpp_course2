// Created by David Zashkolny on 14.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#ifndef CPP_PROJECT_TENSOR_H
#define CPP_PROJECT_TENSOR_H

#include <iostream>
#define BAD_DIMENSION_EXCEPTION 20


typedef size_t ARRAY_SIZE;
typedef int INT;
typedef float FLOAT;


// ====================================== N_DIM_ARRAY ==================================================================

template<typename TYPE>
struct MemoryItem{
    TYPE value;
    MemoryItem *next;
};


// ================================== TENSOR ===========================================================================

template<typename TYPE>
class Tensor{
public:
    Tensor();
    Tensor(ARRAY_SIZE dimension, const ARRAY_SIZE *shape);
    Tensor(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape);
    Tensor reshape(ARRAY_SIZE new_dimension, const ARRAY_SIZE *new_shape);
    ~Tensor();

    TYPE* chain();


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
    void deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape){
        deleteNDimArray(array, dimension, shape, 0);
    }

    void createChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *resArray, ARRAY_SIZE &startIndex);
    void fillArrayFromChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *chain,
            ARRAY_SIZE &startIndex);
};

#endif //CPP_PROJECT_TENSOR_H
