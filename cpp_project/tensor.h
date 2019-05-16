// Created by David Zashkolny on 14.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#ifndef CPP_PROJECT_TENSOR_H
#define CPP_PROJECT_TENSOR_H

#include <iostream>
#include <fstream>

typedef int ARRAY_SIZE;
typedef int INT;
typedef float FLOAT;


// ====================================== N_DIM_ARRAY ==================================================================

// element of N-dimensional array that has a structure like a tree
// each element is pair (value, array of sons), where value is zero if array of sons != NULL
template<typename TYPE>
struct MemoryItem{
    TYPE value;
    MemoryItem *next;
};


// element for getting slice from tensor
// realises python-like slice list[start:end:step]
struct cutting{
    ARRAY_SIZE start = 0;
    ARRAY_SIZE end = 0;
    ARRAY_SIZE step = 1;
};

// ================================== TENSOR ===========================================================================

/*Numpy-like n-dimensional array*/

template<typename TYPE>
class Tensor{
public:
    // constructor of empty 0-dimensional array
    Tensor();

    /* Create n-dimension tensor of zeros with given shape
     *
     * @param dimension: number of dimensions (n)
     * @param shape: pointer on n-elements array - shape of tensor */
    Tensor(ARRAY_SIZE dimension, const ARRAY_SIZE *shape);

    /* Create 1-dimensional tensor from simple element
     *
     * @param element: any simple element*/
    explicit Tensor(TYPE element);

    /* Morph n1-dimension tensor with shape1 into n2-dimensional tensor with shape2 if it is possible.
     * product(shape1) == product(shape2) == amount of all the elements in tensor.
     *
     * @param new_dimension: n2
     * @param new_shape: shape2 */
    void reshape(ARRAY_SIZE new_dimension, const ARRAY_SIZE *new_shape);
//    ~Tensor();


    /* Returns the sequence of all the elements from tensor */
    TYPE* chain();

    /* Overload of operator =: create one more POINTER on tensor 'other' */
    Tensor<TYPE> &operator=(const Tensor<TYPE> &other);

    /* Overload of operator tensor[n] - returns i-th element of tensor (which is actually n-1-dimensional tensor) */
    Tensor<TYPE> &operator[](ARRAY_SIZE i);

    /* Overload of operator tensor[slice={start, end, step}] - returns python-like slice
     * of elements of tensor  (tensor[start:end:step] in python). */
    Tensor<TYPE> &operator[](cutting *slice);

    /* Create full copy of tensor */
    Tensor<TYPE> &copy();

    /* Print tensor in the standard output */
    void print();

    /* Print tensor in the given output */
    void write(std::ostream &stream);

private:

    ARRAY_SIZE mDimension = 0;    // dimension of tensor
    MemoryItem<TYPE> *mArray;     // tree-like array of elements
    ARRAY_SIZE *mShape;           // pointer on the array of shapes


    /* Create n-dimensional tensor from given n-dimensional array
     *
     * @param array: pointer on array of MemoryItems which is actually recursive tree of elements.
     * @param dimension: number of dimensions (n)
     * @param shape: pointer on n-elements array - shape of tensor */
    Tensor(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape);


    /* Auxiliary recursive function for creating n-dimensional tree-like array of zeros.
     *
     * @param dimension: dimension of the given array (depth of tree)
     * @param shape: array of all the shape of tree
     * @param dimLevel: start index of elements from shape, that relate to given Level of array*/
    MemoryItem<TYPE> *createNDimArray(ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel);


    /* Create n-dimensional tree-like array of zeros
     *
     * @param dimension: dimension of the given array (depth of tree)
     * @param shape: pointer on the array of shapes of tree.*/
    MemoryItem<TYPE> *createNDimArray(ARRAY_SIZE dimension, const ARRAY_SIZE *shape);


    /* Create full copy of tree-like array
     *
     * @param array: root of the tree
     * @param dimension: depth of the tree
     * @param shape: all the shape of the tree
     * @param dimLevel: start index of elements from shape, that relate to given root*/
    MemoryItem<TYPE> *copyNDimArray(MemoryItem<TYPE> *array,
                                    ARRAY_SIZE dimension,
                                    const ARRAY_SIZE *shape,
                                    ARRAY_SIZE dimLevel);


    /* Auxiliary recursive function for deleting n-dimensional tree-like array
     *
     * @param array: root of the tree
     * @param dimension: depth of the tree
     * @param shape: all the shape of the tree
     * @param dimLevel: start index of elements from shape, that relate to given root*/
    void deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape, ARRAY_SIZE dimLevel);


    /* Delete n-dimensional tree-like array
     *
     * @param array: root of the tree
     * @param dimension: depth of the tree
     * @param shape: all the shape of the tree */
    void deleteNDimArray(MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape);


    /* Auxiliary recursive function for creating the sequence of all the elements of tree-like array
     *
     * @param array: root of the tree
     * @param dimLevel: start index of elements from shape, that relate to given root
     * @param resArray: pointer on the result array
     * @param startIndex: start position of the free space in resArray */
    void createChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *resArray, ARRAY_SIZE &startIndex);


    /* Auxiliary recursive function for reshaping of the tensor.
     * Fills the tensor with elements from the given sequence
     *
     * @param array: root of the tree
     * @param dimLevel: start index of elements from shape, that relate to given root
     * @param _chain: result of the method .chain() - sequence of all the elements of the tensor
     * @param startIndex: start position of reading elements from _chain*/
    void fillArrayFromChain(MemoryItem<TYPE> *array, ARRAY_SIZE dimLevel, TYPE *_chain,
                            ARRAY_SIZE &startIndex);


    /* Auxiliary recursive function for printing the array.
     *
     * @param stream: output stream
     * @param array: root of the tree
     * @param dimension: depth of the tree
     * @param shape: all the shapes of the tree
     * @param dimLevel: start index of elements from shape, that relate to given root */
    void printNDimArray(std::ostream &stream, MemoryItem<TYPE> *array, ARRAY_SIZE dimension, const ARRAY_SIZE *shape,
            ARRAY_SIZE dimLevel);


    /* Auxiliary recursive function for copying the array
     *
     * @param array1: root of array-to
     * @param array2: root of array-from
     * @param dimension: depth of the tree
     * @param shape: all the shapes of the tree
     * @param dimLevel: start index of elements from shape, that relate to given root */
    void copyValues(MemoryItem<TYPE> *array1, MemoryItem<TYPE> *array2, ARRAY_SIZE dimension, const ARRAY_SIZE *shape,
                    ARRAY_SIZE dimLevel);
};


#endif //CPP_PROJECT_TENSOR_H