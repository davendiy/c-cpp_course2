// Created by David Zashkolny on 14.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//


#include <iostream>
#include <cassert>

template<typename T, size_t N>
struct NDimensionalArray{
    typedef typename NDimensionalArray<T, N - 1>::type *type;
};


template<typename T>
struct NDimensionalArray<T, 1>{
    typedef T *type;
};


template<typename T>
void initializeNDimensionalArray(T &, size_t){}

template <typename T>
void initializeNDimensionalArray(T *& arr, size_t N){
    arr = new T[N];
    for (size_t itr = 0; itr < N; ++itr)
        initializeNDimensionalArray(arr[itr], N);
}


int main()
{
    typedef NDimensionalArray<int, 3>::type ThreeDimensionalArray;
    typedef NDimensionalArray<int, 2>::type TwoDimensionalArray;
    typedef NDimensionalArray<int, 1>::type OneDimensionalArray;

    static_assert(std::is_same<ThreeDimensionalArray, int***>::value, "three");
    static_assert(std::is_same<TwoDimensionalArray, int**>::value, "two");
    static_assert(std::is_same<OneDimensionalArray, int*>::value, "one");

    ThreeDimensionalArray arr;
    initializeNDimensionalArray(arr, 1);

    assert(arr != nullptr);
    assert(arr[0] != nullptr);
    assert(arr[0][0] != nullptr);
}

//
//void createNDimensionZeros(int dimensions, int *shape){
//
//    if (dimensions == 1){
//        int *res = new int[shape[0]];
//
//    }
//}