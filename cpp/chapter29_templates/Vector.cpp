// Created by David Zashkolny on 22.04.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//


#include <iostream>
#include <string>

template <typename VECTOR_TYPE>
class Vector {

public:

    Vector()              // constructor (creates array of 32 elements)
    :_vector(NULL){
        _vector = new VECTOR_TYPE[32];
        _size = 32;
    }

    Vector(int size)     // constructor (creates array of size elements)
    :_vector(NULL){
        if (size >= 0){
            _vector = new VECTOR_TYPE[size];
            _size = size;
        }
        else {
            throw 1;
        }
    }

    Vector(const Vector<VECTOR_TYPE> &other)     // constructor that creates copy of other
        :_vector(NULL){
        _vector = new VECTOR_TYPE[other._size];
        _size = other._size;
        for (int i = 0; i < _size; i++){
            _vector[i] = other._vector[i];
        }

    }

    ~Vector(){       // destructor
        delete[] _vector;
    }

    VECTOR_TYPE get(int key) {          // analog of the array[key]
        if (0 <= key && key < _size){
            return _vector[key];
        }
        else {
            throw 1;
        }
    }

    void set(int key, VECTOR_TYPE value) {    // analog of the array[key] = tmp
        if (0 <= key && key <= _size){
            _vector[key] = value;
        }
        else {
            throw 1;
        }
    }

    void push_back(VECTOR_TYPE value) {              // analog of vector<int>.push_back
        _growUp();
        _vector[_size-1] = value;
    }


    void push_front(VECTOR_TYPE value) {             // analog of vector<int>.push_front
        _size++;
        VECTOR_TYPE *_tmp_vector = new VECTOR_TYPE[_size];
        _tmp_vector[0] = value;
        for (int i = 1; i < _size; i++){
            _tmp_vector[i] = _vector[i-1];
        }
        delete[] _vector;
        _vector = _tmp_vector;

    }
    int size(){
        return _size;
    };

    Vector &operator=(const Vector other) {    // copy of array
        if (this == &other) {
            return *this;
        }

        delete[] _vector;
        _vector = new VECTOR_TYPE[other._size];
        _size = other._size;
        for (int i = 0; i < _size; i++) {
            _vector[i] = other._vector[i];
        }
        return *this;
    }

private:

    VECTOR_TYPE *_vector;       // dynamic array with data
    int _size;   // size of array
    void _growUp() {     // resize array of length _size into array of length _size + 1
        VECTOR_TYPE *_tmp_vector = new VECTOR_TYPE[_size + 1];
        for (int i = 0; i < _size; i++){
            _tmp_vector[i] = _vector[i];
        }
        delete[] _vector;
        _vector = _tmp_vector;
        _size += 1;

    }
};


template <typename VECTOR_TYPE>
void print_array(Vector<VECTOR_TYPE> &array){
    for (int i = 0; i < array.size(); i++){
        std::cout << array.get(i) << ' ';
    }
    std::cout << std::endl;
}

template <typename VECTOR_TYPE>
bool isInVector(Vector<VECTOR_TYPE> &array, VECTOR_TYPE element){
    bool success = false;
    for (int i = 0; i < array.size(); i++){
        if (element == array.get(i)){
            success = true;
            break;
        }
    }
    return success;
}


// функция сортировки
template <typename VECTOR_TYPE>
void quicksort(Vector<VECTOR_TYPE> &mas, int first, int last){
    int mid, count;
    int f = first, l = last;
    mid = mas.get((f + l) / 2); // вычисление опорного элемента
    do {
        while (mas.get(f) < mid) f++;
        while (mas.get(l) > mid) l--;
        // перестановка элементов
        if (f <= l){
            count = mas.get(f);
            mas.set(f, mas.get(l));
            mas.set(l, count);
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) quicksort(mas, first, l);
    if (f < last) quicksort(mas, f, last);
}


int main(){

    int n;
    std::cout << "please, enter the amount of elements in the array:" << std::endl;
    std::cin >> n;
    Vector<int> test (n);
    for (int i = 0; i < n; i++){
        int tmp;
        std::cout << "a[" << i <<"] = ";
        std::cin >> tmp;
        test.set(i, tmp);
    }

    int a = 10;
    int b = 100;
    test.push_back(a);
    print_array(test);
    test.push_front(b);
    std::cout << "Array:" << std::endl;
    print_array(test);

    quicksort(test, 0, test.size()-1);
    std::cout << "Array after sort:" << std::endl;
    print_array(test);

    Vector<double> second(0);

    second.push_back(0.5);
    second.push_front(0.2);

    std::cout << "second array:" << std::endl;
    print_array(second);

    std::cout << "1 in second: " << isInVector(second, 1.) << std::endl;
    return 0;
}