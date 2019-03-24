// Created by David Zashkolny on 23.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <string>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

typedef long long int INT;


class Comparable{
public:
    __int8_t compare(Comparable& other);
    virtual void print() = 0;

protected:
    virtual INT _int_repr() = 0;
};


__int8_t Comparable::compare(Comparable &other) {

    if (this == &other) return 0;

    else if (this->_int_repr() > other._int_repr()) return 1;

    else return -1;
}


class HightScoreElement : public Comparable{
public:
    HightScoreElement();                                    // constructor, not implemented
    HightScoreElement(string& new_name, int new_score);     // constructor with parameters

    string name;
    int score;

    virtual void print();

protected:
    virtual INT _int_repr();

private:
};


HightScoreElement::HightScoreElement(){}

HightScoreElement::HightScoreElement(string &new_name, int new_score)
    :name("") {
    name = new_name;
    score = new_score;
}


void HightScoreElement::print() {
    cout << name << " : " << score << " " << _int_repr() << endl;
}

INT HightScoreElement::_int_repr() {
    return score;
}


class ComplexInt : public Comparable{
public:
    ComplexInt();               // constructor, not implemented
    ComplexInt(int a, int b);   // constructor with parameters
    int real;
    int imag;

    virtual void print();
protected:
    virtual INT _int_repr();
};


ComplexInt::ComplexInt() {}

ComplexInt::ComplexInt(int a, int b) {
    real = a;
    imag = b;
}

INT ComplexInt::_int_repr() {
    return (long long int) sqrt(real * real + imag * imag);
}

void ComplexInt::print() {
    cout << real << " + " << imag << "j" << " " << _int_repr() << endl;
}


void quicksort(vector<Comparable*> &array, int first, int last){
    Comparable *mid, *tmp;
    int tmp_f = first, tmp_l = last;
    mid = array[(tmp_f + tmp_l) / 2];
    do {
        while (array[tmp_f]->compare(*mid) < 0) tmp_f++;
        while (array[tmp_l]->compare(*mid) > 0) tmp_l--;

        if (tmp_f <= tmp_l){
            tmp = array[tmp_f];
            array[tmp_f] = array[tmp_l];
            array[tmp_l] = tmp;
            tmp_f++;
            tmp_l--;
        }
    } while (tmp_f < tmp_l);
    if (first < tmp_l) quicksort(array, first, tmp_l);
    if (tmp_f < last) quicksort(array, tmp_f, last);
}


int main(){

    vector<Comparable*> test;

    string tmp_name = "test1";
    test.push_back(new HightScoreElement(tmp_name, 10));

    string tmp_name2 = "test2";
    test.push_back(new HightScoreElement(tmp_name2, 5));

    test.push_back(new ComplexInt(15, 85));
    test.push_back(new ComplexInt(3, 4));


    for (vector<Comparable*>::iterator itr = test.begin(), end = test.end(); itr != end; ++itr){
        (*itr)->print();
    }
    quicksort(test, 0, (int) test.size() - 1);

    for (vector<Comparable*>::iterator itr = test.begin(), end = test.end(); itr != end; ++itr){
        (*itr)->print();
    }
}