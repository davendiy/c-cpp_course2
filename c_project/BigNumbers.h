// Created by David Zashkolny on 12.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#ifndef C_PROJECT_BIGNUMBERS_H
#define C_PROJECT_BIGNUMBERS_H

#include "stdio.h"
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define ELEM_SIZE_NUM 8
typedef size_t SIZE;
typedef long int ELEM_TYPE;

#define MAX(a, b)       a > b ? a : b
#define MIN(a, b)       a < b ? a : b


typedef struct BigInteger{
    size_t intsAmount;
    int sign;
    ELEM_TYPE *body;
} BigInteger;


long int binPow(long int a, long int n);

BigInteger *copy(const BigInteger *a);

BigInteger *fromChars(const char *number, SIZE size);


void print(const BigInteger *a);


void delRedundantZeros(BigInteger *a);

int _absRelation(const BigInteger *a, const BigInteger *b, SIZE last_index);

int absRelation(BigInteger *a, BigInteger *b);


BigInteger *_add(const BigInteger *a, const BigInteger *b);

// subtraction (a >= b)
BigInteger *_sub(const BigInteger *a, const BigInteger *b);


BigInteger *add(const BigInteger *a, const BigInteger *b);

BigInteger *sub(const BigInteger *a, const BigInteger *b);


ELEM_TYPE *growUp(ELEM_TYPE *array, SIZE size);


void normalize(BigInteger *n);


void extendBigInteger(BigInteger *x, SIZE n);



BigInteger *karatsuba_mul(BigInteger *X, BigInteger *Y);;


BigInteger *mul(const BigInteger *X, const BigInteger *Y);


void shiftRight(BigInteger *number);


BigInteger *divide(const BigInteger *X, const BigInteger *Y);


BigInteger **xgcd(const BigInteger *a, const BigInteger *b);

BigInteger *gcd(const BigInteger *a, const BigInteger *b);

BigInteger *lcm(const BigInteger *a, const BigInteger *b);

#endif //C_PROJECT_BIGNUMBERS_H
