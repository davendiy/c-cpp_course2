// Created by David Zashkolny on 14.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
#include "tensor.h"
//
//// ====================================== N_DIM_ARRAY ==================================================================
//
//template<typename TYPE>
//MemoryItem<TYPE>* Tensor<TYPE>::createNDimArray(ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel){
//    if (dimension < 1){
//        return nullptr;
//    } else {
//        auto *res = new MemoryItem<TYPE>[shape[dimLevel]];
//        for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
//            res[itr] = MemoryItem<TYPE>();
//            if (dimension == 1) {
//                res[itr].next = nullptr;
//            } else {
//                res[itr].next = createNDimArray(dimension-1, shape, dimLevel+1);
//            }
//            res[itr].value = 0;
//        }
//        return res;
//    }
//}
//
//
//template<typename TYPE>
//MemoryItem<TYPE>* Tensor<TYPE>::createNDimArray(ARRAY_SIZE dimension, const ARRAY_SIZE *shape){
//    return createNDimArray(dimension, shape, 0);
//}
//
//
//// delete n-dimensional array
//template <typename TYPE>
//void Tensor<TYPE>::deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel){
//
//    if (dimension > 1){
//        for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
//            deleteNDimArray(array[itr].next, dimension-1, shape, dimLevel+1);
//        }
//
//    }
//    delete[] array;
//}
//
//
//// copy of n-dimensional array
//template <typename TYPE>
//MemoryItem<TYPE>* Tensor<TYPE>::copyNDimArray(MemoryItem<TYPE> *array,ARRAY_SIZE dimension, const ARRAY_SIZE *shape,
//                                              ARRAY_SIZE dimLevel) {
//    if (dimension < 1){
//        return nullptr;
//    }
//    auto *res = new MemoryItem<TYPE>[shape[dimLevel]];
//    for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
//        MemoryItem<TYPE> tmp;
//        if (dimension > 1){
//            tmp.next = copyNDimArray(array[itr].next, dimension-1, shape, dimLevel + 1);
//            tmp.value = 0;
//        } else {
//            tmp.value = array[itr].value;
//            tmp.next = nullptr;
//        }
//        res[itr] = tmp;
//    }
//    return res;
//}
//
//template <typename TYPE>
//void Tensor<TYPE>::deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape) {
//    deleteNDimArray(array, dimension, shape, 0);
//}
//
//
//// ================================== TENSOR ===========================================================================
//
//// constructor of an empty array
//template<typename TYPE>
//Tensor<TYPE>::Tensor()
//        :mShape(nullptr)
//        ,mArray(nullptr)
//{}
//
//
//// constructor of an n-dimension array (m1, m2, m3, ...) of zeros
//template<typename TYPE>
//Tensor<TYPE>::Tensor(ARRAY_SIZE dimension, const ARRAY_SIZE *shape)
//        :mShape(nullptr)
//        ,mArray(nullptr)
//{
//    mDimension = dimension;
//    mShape = new ARRAY_SIZE[dimension];
//    for (ARRAY_SIZE itr = 0; itr < dimension; ++itr){
//        mShape[itr] = shape[itr];
//    }
//    mArray = createNDimArray(dimension, shape);
//}
//
//
//// constructor from n-dimensional array
//template<typename TYPE>
//Tensor<TYPE>::Tensor(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape)
//        :mShape(nullptr)
//        ,mArray(nullptr)
//{
//    mDimension = dimension;
//    mShape = new ARRAY_SIZE[dimension];
//    for (ARRAY_SIZE itr = 0; itr < dimension; ++itr){
//        mShape[itr] = shape[itr];
//    }
//    mArray = copyNDimArray(array, dimension, shape, 0);
//}
//
//// destructor
//template <typename TYPE>
//Tensor<TYPE>::~Tensor() {
//    deleteNDimArray(mArray, mDimension, mShape);
//    delete[] mShape;
//}
//
//
//// recursive fill the chain array
//template<typename TYPE>
//void Tensor<TYPE>::createChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *resArray, ARRAY_SIZE &startIndex) {
//    if (mDimension - dimLevel < 1){
//        return;
//    } else if (mDimension - dimLevel == 1){
//        for (ARRAY_SIZE itr = 0; itr < mShape[dimLevel]; ++itr){
//            resArray[startIndex] = array[itr].value;
//            startIndex++;
//        }
//    } else {
//        for (ARRAY_SIZE itr = 0; itr < mShape[dimLevel]; ++itr){
//            createChain(array[itr].next, dimLevel + 1, resArray, startIndex);
//        }
//    }
//}
//
//
//// build a chain of all the elements of Array
//template<typename TYPE>
//TYPE* Tensor<TYPE>::chain() {
//    ARRAY_SIZE amount = 1;
//    for (ARRAY_SIZE itr = 0; itr < mDimension; ++itr){
//        amount *= mShape[itr];
//    }
//    if (mDimension >= 1){
//        TYPE *resArray = new TYPE[amount];
//        ARRAY_SIZE startIndex = 0;
//        createChain(mArray, 0, resArray, startIndex);
//        return resArray;
//    } else {
//        TYPE *resArray = nullptr;
//        return resArray;
//    }
//}
//
//template <typename TYPE>
//void Tensor<TYPE>::fillArrayFromChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *chain,
//                                      ARRAY_SIZE &startIndex) {
//    if (mDimension - dimLevel < 1){
//        return;
//    } else if (mDimension - dimLevel == 1){
//        for (ARRAY_SIZE itr = 0; itr < mShape[dimLevel]; ++itr){
//            array[itr].value = chain[startIndex];
//            startIndex++;
//        }
//    } else {
//        for (ARRAY_SIZE itr = 0; itr < mShape[dimLevel]; ++itr){
//            fillArrayFromChain(array[itr].next, dimLevel + 1, chain, startIndex);
//        }
//    }
//}
//
//
//// reshape array to new measurements
//template<typename TYPE>
//Tensor<TYPE> Tensor<TYPE>::reshape(ARRAY_SIZE new_dimension, const ARRAY_SIZE *new_shape) {
//    ARRAY_SIZE amount1 = 1;
//    ARRAY_SIZE amount2 = 1;
//
//    for (ARRAY_SIZE itr = 0; itr < mDimension; ++itr){    // check if we can do reshape
//        amount1 *= mShape[itr];
//    }
//    for (ARRAY_SIZE itr = 0; itr < new_dimension; ++itr){
//        amount2 *= new_shape[itr];
//    }
//    if (amount1 != amount2){
//        throw std::length_error("Bad dimension for reshape");
//    }
//
//    TYPE *_chain = chain();
//
//    MemoryItem<TYPE> *newArray = createNDimArray(new_dimension, new_shape);
//    mDimension = new_dimension;
//    mShape = new ARRAY_SIZE[new_dimension];
//    for (ARRAY_SIZE itr = 0; itr < new_dimension; ++itr){
//        mShape[itr] = new_shape[itr];
//    }
//    ARRAY_SIZE startIndex = 0;
//    fillArrayFromChain(newArray, 0, _chain, startIndex);
//    mArray = newArray;
//}
