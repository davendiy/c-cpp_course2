// Created by David Zashkolny on 14.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>
#include <fstream>
#include "tensor.h"


// ====================================== N_DIM_ARRAY ==================================================================

// recursive function to create n dimensional array like tree
template<typename TYPE>
MemoryItem<TYPE>* Tensor<TYPE>::createNDimArray(ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel){
    if (dimension < 1){
        return nullptr;
    } else {
        auto *res = new MemoryItem<TYPE>[shape[dimLevel]];
        for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
            res[itr] = MemoryItem<TYPE>();
            if (dimension == 1) {
                res[itr].next = nullptr;
            } else {
                res[itr].next = createNDimArray(dimension-1, shape, dimLevel+1);
            }
            res[itr].value = 0;
        }
        return res;
    }
}


// create n dimension array like tree
template<typename TYPE>
MemoryItem<TYPE>* Tensor<TYPE>::createNDimArray(ARRAY_SIZE dimension, const ARRAY_SIZE *shape){
    return createNDimArray(dimension, shape, 0);
}


// delete n-dimensional array
template <typename TYPE>
void Tensor<TYPE>::deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel){

    if (dimension > 1){
        for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
            deleteNDimArray(array[itr].next, dimension-1, shape, dimLevel+1);
        }

    }
    delete[] array;
}


// full copy of n-dimensional array
template <typename TYPE>
MemoryItem<TYPE>* Tensor<TYPE>::copyNDimArray(MemoryItem<TYPE> *array,ARRAY_SIZE dimension, const ARRAY_SIZE *shape,
                                              ARRAY_SIZE dimLevel) {
    if (dimension < 1){
        return nullptr;
    }
    auto *res = new MemoryItem<TYPE>[shape[dimLevel]];
    for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
        MemoryItem<TYPE> tmp;
        if (dimension > 1){
            tmp.next = copyNDimArray(array[itr].next, dimension-1, shape, dimLevel + 1);
            tmp.value = 0;
        } else {
            tmp.value = array[itr].value;
            tmp.next = nullptr;
        }
        res[itr] = tmp;
    }
    return res;
}

// non-recursive function for deleting
template <typename TYPE>
void Tensor<TYPE>::deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape) {
    deleteNDimArray(array, dimension, shape, 0);
}


// ================================== TENSOR ===========================================================================

// constructor of an empty array
template<typename TYPE>
Tensor<TYPE>::Tensor()
        :mShape(nullptr)
        ,mArray(nullptr)
{}

// constructor from single element
template<typename TYPE>
Tensor<TYPE>::Tensor(TYPE element)
        :mShape(nullptr)
        ,mArray(nullptr)
{
    mShape = new ARRAY_SIZE[1];
    mShape[0] = 1;
    mArray = new MemoryItem<TYPE>[1];
    mArray[0].next = nullptr;
    mArray[0].value = element;
    mDimension = 1;
}

// constructor of an n-dimension array (m1, m2, m3, ...) of zeros
template<typename TYPE>
Tensor<TYPE>::Tensor(ARRAY_SIZE dimension, const ARRAY_SIZE *shape)
        :mShape(nullptr)
        ,mArray(nullptr)
{
    mDimension = dimension;
    mShape = new ARRAY_SIZE[dimension];
    for (ARRAY_SIZE itr = 0; itr < dimension; ++itr){
        mShape[itr] = shape[itr];
    }
    mArray = createNDimArray(dimension, shape);
}


// constructor from n-dimensional array
template<typename TYPE>
Tensor<TYPE>::Tensor(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape)
        :mShape(nullptr)
        ,mArray(nullptr)
{
    mDimension = dimension;
    mShape = new ARRAY_SIZE[dimension];
    for (ARRAY_SIZE itr = 0; itr < dimension; ++itr){
        mShape[itr] = shape[itr];
    }
    mArray = array;
}

//// destructor
//template <typename TYPE>
//Tensor<TYPE>::~Tensor() {
//    deleteNDimArray(mArray, mDimension, mShape);
//    delete[] mShape;
//    mDimension = 0;
//}


// recursively fill the chain array
template<typename TYPE>
void Tensor<TYPE>::createChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *resArray, ARRAY_SIZE &startIndex) {
    if (mDimension - dimLevel < 1){
        return;
    } else if (mDimension - dimLevel == 1){
        for (ARRAY_SIZE itr = 0; itr < mShape[dimLevel]; ++itr){
            resArray[startIndex] = array[itr].value;
            startIndex++;
        }
    } else {
        for (ARRAY_SIZE itr = 0; itr < mShape[dimLevel]; ++itr){
            createChain(array[itr].next, dimLevel + 1, resArray, startIndex);
        }
    }
}


// build a chain of all the elements of Array
template<typename TYPE>
TYPE* Tensor<TYPE>::chain() {
    ARRAY_SIZE amount = 1;
    for (ARRAY_SIZE itr = 0; itr < mDimension; ++itr){
        amount *= mShape[itr];
    }
    if (mDimension >= 1){
        TYPE *resArray = new TYPE[amount];
        ARRAY_SIZE startIndex = 0;
        createChain(mArray, 0, resArray, startIndex);
        return resArray;
    } else {
        TYPE *resArray = nullptr;
        return resArray;
    }
}

// fills n dimensional array from 1-dimensional chain
template <typename TYPE>
void Tensor<TYPE>::fillArrayFromChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *_chain,
                                      ARRAY_SIZE &startIndex) {
    if (mDimension - dimLevel < 1){
        return;
    } else if (mDimension - dimLevel == 1){
        for (ARRAY_SIZE itr = 0; itr < mShape[dimLevel]; ++itr){
            array[itr].value = _chain[startIndex];
            startIndex++;
        } return;
    } else {
        for (ARRAY_SIZE itr = 0; itr < mShape[dimLevel]; ++itr){
            fillArrayFromChain(array[itr].next, dimLevel + 1, _chain, startIndex);
        }
        return;
    }

}


// reshape array to new measurements
template<typename TYPE>
void Tensor<TYPE>::reshape(ARRAY_SIZE new_dimension, const ARRAY_SIZE *new_shape) {
    ARRAY_SIZE amount1 = 1;
    ARRAY_SIZE amount2 = 1;

    for (ARRAY_SIZE itr = 0; itr < mDimension; ++itr){    // check if we can do reshape
        amount1 *= mShape[itr];
    }
    for (ARRAY_SIZE itr = 0; itr < new_dimension; ++itr){
        amount2 *= new_shape[itr];
    }
    if (amount1 != amount2){
        throw std::length_error("Bad dimension for reshape");
    }

    TYPE *_chain = chain();

    MemoryItem<TYPE> *newArray = createNDimArray(new_dimension, new_shape);
    mDimension = new_dimension;
    mShape = new ARRAY_SIZE[new_dimension];
    for (ARRAY_SIZE itr = 0; itr < new_dimension; ++itr){
        mShape[itr] = new_shape[itr];
    }
    ARRAY_SIZE startIndex = 0;
    fillArrayFromChain(newArray, 0, _chain, startIndex);
    mArray = newArray;
}

// full copy of tensor
template<typename TYPE>
Tensor<TYPE>& Tensor<TYPE>::copy() {
    auto *res = new Tensor<TYPE>(mDimension, mShape);
    res->mArray = copyNDimArray(mArray, mDimension, mShape, 0);
    return *res;
}

// x1 = x2 copying all the values from x2 to x1
template<typename TYPE>
Tensor<TYPE>& Tensor<TYPE>::operator=(const Tensor<TYPE> &other) {
    if (this != &other){
        if (this->mDimension != other.mDimension) throw std::invalid_argument("different dimensions");
        bool success = true;
        for (ARRAY_SIZE itr = 0; itr < this->mDimension; ++itr)
            if (this->mShape[itr] != other.mShape[itr]){
                success = false;
                break;
            }
        if (!success) throw std::invalid_argument("different shapes");

        copyValues(this->mArray, other.mArray, mDimension, mShape, 0);
    }
    return *this;
}

// returns n-1 dimensional element of tensor (even if this element just simple value)
template<typename TYPE>
Tensor<TYPE>& Tensor<TYPE>::operator[](ARRAY_SIZE i) {
    if (i > mShape[0] || i < 0){
        throw std::out_of_range("index is out of range");
    } else if (mDimension > 1){
        auto *newShape = new ARRAY_SIZE[mDimension - 1];
        for (ARRAY_SIZE itr = 0; itr < mDimension - 1; ++itr){
            newShape[itr] = mShape[itr+1];
        }
        auto *res = new Tensor<TYPE>(mArray[i].next, mDimension - 1, newShape);
        return *res;
    } else {Tensor<TYPE>();
        auto *tmpArr = &mArray[i];
        auto *tmpShape = new ARRAY_SIZE[1];
        tmpShape[0] = 1;
        auto *res = new Tensor<TYPE>(tmpArr, 1, tmpShape);
        return *res;
    }
}

template<typename TYPE>
void Tensor<TYPE>::print() {
    printNDimArray(std::cout, mArray, mDimension, mShape, 0);
    std::cout << std::endl;
}

template<typename TYPE>
void Tensor<TYPE>::write(std::ostream &stream){
    printNDimArray(stream, mArray, mDimension, mShape, 0);
    stream << std::endl;
}

template<typename TYPE>
void Tensor<TYPE>::printNDimArray(std::ostream &stream, MemoryItem<TYPE> *array, ARRAY_SIZE dimension,
                                  const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel) {
    if (dimension == 1){
        for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
            std::cout << array[itr].value << ' ';
        }
        stream << std::endl;
    } else {
        for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
            printNDimArray(stream, array[itr].next, dimension-1, shape, dimLevel+1);
            for (ARRAY_SIZE i = 0; i < dimension-2; i++){
                stream << std::endl;
            }
        }
    }
}

template <typename TYPE>
void Tensor<TYPE>::copyValues(MemoryItem<TYPE> *array1, MemoryItem<TYPE> *array2, ARRAY_SIZE dimension,
                              const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel) {
    if (dimension == 1){
        for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr){
            array1[itr].value = array2[itr].value;
        }
    } else {
        for (ARRAY_SIZE itr = 0; itr < shape[dimLevel]; ++itr) {
            copyValues(array1[itr].next, array2[itr].next, dimension - 1, shape, dimLevel + 1);
        }
    }
}

template <typename TYPE>
Tensor<TYPE>& Tensor<TYPE>::operator[](cutting *slice) {
    if (slice->start < slice->end && slice->step > 0){
        ARRAY_SIZE amount = (slice->end - slice->start) / slice->step + 1;
        auto *tmpArray = new MemoryItem<TYPE>[amount];
        ARRAY_SIZE tmpIndex = 0;
        for (ARRAY_SIZE itr = slice->start; itr < mShape[0] && itr < slice->end && itr >= 0; itr += slice->step){
            tmpArray[tmpIndex] = mArray[itr];
            tmpIndex += 1;
        }
        ARRAY_SIZE *resShape;
        resShape = new ARRAY_SIZE[mDimension];
        for (ARRAY_SIZE itr = 0; itr < mDimension; ++itr){
            resShape[itr] = mShape[itr];
        }
        resShape[0] = amount;
        // create *res instead res because of deleting local variables
        auto *res = new Tensor<TYPE>(tmpArray, mDimension, resShape);
        return *res;
    } else if (slice->end < slice->start && slice->step < 0){
        ARRAY_SIZE amount = 1 + (slice->start - slice->end) / -slice->step;
        auto *tmpArray = new MemoryItem<TYPE>[amount];
        ARRAY_SIZE j = 0;
        for (ARRAY_SIZE itr = slice->start; itr > slice->end && itr >= 0 && itr < mShape[0]; itr += slice->step){
            tmpArray[j] = mArray[itr];
            j++;
        }
        auto *tmpShape = new ARRAY_SIZE[mDimension];
        for (ARRAY_SIZE itr = 0; itr < mDimension; ++itr){
            tmpShape[itr] = mShape[itr];
        }
        tmpShape[0] = amount;
        // create *res instead res because of deleting local variables
        auto *res = new Tensor<TYPE>(tmpArray, mDimension, tmpShape);
        return *res;
    } else {
        auto res = Tensor<TYPE>();
        return res;
    }
}
