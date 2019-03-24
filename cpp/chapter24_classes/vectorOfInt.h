// Created by David Zashkolny on 23.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#ifndef CPP_VECTOROFINT_H
#define CPP_VECTOROFINT_H

#endif //CPP_VECTOROFINT_H

typedef long long int VECTOR_INT;

namespace myVector {


    class vectorOfInt {

    public:

        vectorOfInt();                    // constructor (creates array of 32 elements)
        vectorOfInt(VECTOR_INT size);     // constructor (creates array of size elements)
        vectorOfInt(const vectorOfInt &other);     // constructor that creates copy of other
        ~vectorOfInt();                   // destructor
        int get(VECTOR_INT key);          // analog of the array[key]
        void set(VECTOR_INT key, int value);    // analog of the array[key] = tmp
        void push_back(int value);              // analog of vector<int>.push_back
        void push_front(int value);             // analog of vector<int>.push_front
        VECTOR_INT size();

        vectorOfInt &operator=(const vectorOfInt &other);    // copy of array

    private:

        int *_vector;       // dynamic array with data
        VECTOR_INT _size;   // size of array
        void _growUp();     // resize array of length _size into array of length _size + 1
    };
}