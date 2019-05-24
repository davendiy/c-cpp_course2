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


typedef struct BigNumber{
    size_t intsAmount;
    int sign;
    ELEM_TYPE *body;
} BigNumber;


long int binPow(long int a, long int n);

BigNumber *copy(const BigNumber *a);

BigNumber *fromChars(const char *number, SIZE size);


void print(const BigNumber *a);


void delRedundantZeros(BigNumber *a);

int _absRelation(const BigNumber *a, const BigNumber *b, SIZE last_index);

int absRelation(BigNumber *a, BigNumber *b);


BigNumber *_add(const BigNumber *a, const BigNumber *b);

// subtraction (a >= b)
BigNumber *_sub(const BigNumber *a, const BigNumber *b);


BigNumber *add(const BigNumber *a, const BigNumber *b);

BigNumber *sub(const BigNumber *a, const BigNumber *b);


ELEM_TYPE *growUp(ELEM_TYPE *array, SIZE size);


void normalize(BigNumber *n);


void extendBigNumber(BigNumber *x, SIZE n);



BigNumber *karatsuba_mul(BigNumber *X, BigNumber *Y);;


BigNumber *mul(const BigNumber *X, const BigNumber *Y);


#endif //C_PROJECT_BIGNUMBERS_H
