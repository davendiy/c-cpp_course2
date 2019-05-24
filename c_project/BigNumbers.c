// Created by David Zashkolny on 24.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include "BigNumbers.h"

long int binPow(long int a, long int n) {
    long int res = 1;
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}


BigNumber *fromChars(const char *number, SIZE size) {
    BigNumber *res = (BigNumber *) malloc(sizeof(BigNumber));
    int start = 0;
    if (number[0] == '-') {
        res->sign = -1;
        res->intsAmount = (size-1) / ELEM_SIZE_NUM + 1;
        start = 1;
    } else {
        res->sign = 1;
        res->intsAmount = size / ELEM_SIZE_NUM + 1;
    }

    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * (res->intsAmount));
    for (SIZE itr = 0; itr < res->intsAmount; itr++){
        res->body[itr] = 0;
    }

    int tmp = 0;
    SIZE elemIndex = 0;
    for (int itr = size-1; itr >= start; --itr){
        for (int itr2 = 0; itr2 < ELEM_SIZE_NUM; ++itr2){
            char tmp_char = number[itr];
            tmp = atoi(&tmp_char);
            tmp *= (int ) binPow(10, itr2);
            res->body[elemIndex] += tmp;
            --itr;
            if (itr < start) break;
        }
        if (itr == -1) break;
        ++itr;
        ++elemIndex;
    }
    return res;
}


void print(const BigNumber *a) {
    if (a->sign == -1){
        printf("-");
    }
    SIZE start = a->intsAmount -1;
    while (a->body[start] == 0 && start > 0) start--;
    printf("%ld", a->body[start]);
    if (start > 0) {
        for (int itr = start - 1; itr >= 0; itr--)
            printf("%08ld", a->body[itr]);
    }
    printf("\n");
}


void delRedundantZeros(BigNumber *a) {
    while (a->body[a->intsAmount-1] == 0 && a->intsAmount > 1) a->intsAmount--;
    ELEM_TYPE *res = (ELEM_TYPE * ) malloc(sizeof(ELEM_TYPE) * a->intsAmount);
    for (SIZE itr = 0; itr < a->intsAmount; itr++) {
        res[itr] = a->body[itr];
    }
    free(a->body);
    a->body = res;
}


BigNumber *_add(const BigNumber *a, const BigNumber *b) {

    int carry = 0;
    int base = binPow(10, ELEM_SIZE_NUM);
    BigNumber *res = (BigNumber *) malloc(sizeof(BigNumber));
    res->sign = 1;
    res->intsAmount = (MAX(a->intsAmount, b->intsAmount)) + 1;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE i = 0; i < res->intsAmount; ++i){
        res->body[i] = 0;
    }

    for (SIZE i = 0; i < res->intsAmount || carry; ++i){
        res->body[i] = (i < a->intsAmount ? a->body[i] : 0) + carry + (i < b->intsAmount ? b->body[i] : 0);
        carry = res->body[i] >= base;
        if (carry) res->body[i] -= base;
    }
    return res;
}


BigNumber *_sub(const BigNumber *a, const BigNumber *b) {

    int carry = 0;
    int base = binPow(10, ELEM_SIZE_NUM);
    struct BigNumber *res = (BigNumber *) malloc(sizeof(BigNumber));
    res->sign = 1;
    res->intsAmount = MAX(a->intsAmount, b->intsAmount);
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE i = 0; i< res->intsAmount; ++i){
        res->body[i] = 0;
    }

    for (SIZE i = 0; i < a->intsAmount || carry; i++){
        res->body[i] = a->body[i] - carry - (i < b->intsAmount ? b->body[i] : 0);
        carry = res->body[i] < 0;
        if (carry) res->body[i] += base;
    }
    while (res->intsAmount > 1 && res->body[res->intsAmount-1] == 0){
        res->intsAmount--;
    }
    delRedundantZeros(res);
    return res;
}


ELEM_TYPE *growUp(ELEM_TYPE *array, SIZE size) {
    ELEM_TYPE *res = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * (size + 1));
    for (SIZE i = 0; i < size; ++i){
        res[i] = array[i];
    }
    res[size] = 0;
    free(array);
    return res;
}


void normalize(BigNumber *n) {

    ELEM_TYPE base = binPow(10, ELEM_SIZE_NUM);
    for (SIZE i = 0; i < n->intsAmount; ++i){
        n->body[i+1] += n->body[i] / base;

        n->body[i] %= base;
        if (n->body[i] < 0) n->body[i] = base - n->body[i];
    }
}


void extendBigNumber(BigNumber *x, SIZE n) {
    if (n & 1){
        n++;
    }
    if (n >= x->intsAmount){
        ELEM_TYPE *new_array = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * n);
        for (SIZE itr = 0; itr < n; itr++){
            if (itr < x->intsAmount){
                new_array[itr] = x->body[itr];
            } else {
                new_array[itr] = 0;
            }
        }
        x->intsAmount = n;
        free(x->body);
        x->body = new_array;
    }
}


BigNumber *karatsuba_mul(BigNumber *X, BigNumber *Y) {
    SIZE n = MAX(X->intsAmount, Y->intsAmount);
    if (n > 1){
        extendBigNumber(X, n);
        extendBigNumber(Y, n);
    }

    BigNumber *res = (BigNumber *) malloc(sizeof(BigNumber));
    res->sign = 1;
    res->intsAmount = X->intsAmount * 2;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE itr = 0; itr < res->intsAmount; itr++){
        res->body[itr] = 0;
    }

    if (X->intsAmount == 1){
        res->body[0] = X->body[0] * Y->body[0];
        return res;
    }

    SIZE k = X->intsAmount / 2;
    BigNumber *Xr = (BigNumber *) malloc(sizeof(BigNumber));
    BigNumber *Xl = (BigNumber *) malloc(sizeof(BigNumber));
    BigNumber *Yr = (BigNumber *) malloc(sizeof(BigNumber));
    BigNumber *Yl = (BigNumber *) malloc(sizeof(BigNumber));

    Xr->intsAmount = Yr->intsAmount = k;
    Xl->intsAmount = Yl->intsAmount = X->intsAmount - k;
    Xr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xr->intsAmount);
    Xl->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xl->intsAmount);
    Yr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Yr->intsAmount);
    Yl->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Yl->intsAmount);
    for (SIZE itr = 0; itr < X->intsAmount; ++itr){
        if (itr < k){
            Xr->body[itr] = X->body[itr];
            Yr->body[itr] = Y->body[itr];
        } else {
            Xl->body[itr - k] = X->body[itr];
            Yl->body[itr - k] = Y->body[itr];
        }
    }

    BigNumber *P1 = karatsuba_mul(Xl, Yl);
    BigNumber *P2 = karatsuba_mul(Xr, Yr);

    BigNumber *Xlr = (BigNumber *) malloc(sizeof(BigNumber));
    BigNumber *Ylr = (BigNumber *) malloc(sizeof(BigNumber));

    Xlr->intsAmount = Ylr->intsAmount = Xr->intsAmount;
    Xlr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xlr->intsAmount);
    Ylr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xlr->intsAmount);
    for (SIZE itr = 0; itr < Xlr->intsAmount; itr++){
        Xlr->body[itr] = Xl->body[itr] + Xr->body[itr];
        Ylr->body[itr] = Yl->body[itr] + Yr->body[itr];
    }

    BigNumber *P3 = karatsuba_mul(Xlr, Ylr);
    for (SIZE itr = 0; itr < X->intsAmount; ++itr){
        P3->body[itr] -= P2->body[itr] + P1->body[itr];
        res->body[itr] = P2->body[itr];
    }

    for (SIZE itr = X->intsAmount; itr < 2 * X->intsAmount; ++itr){
        res->body[itr] = P1->body[itr - X->intsAmount];
    }

    for (SIZE itr = k; itr < X->intsAmount + k; ++itr){
        res->body[itr] += P3->body[itr - k];
    }
    free(P1->body);
    free(P2->body);
    free(P3->body);
    free(Xl->body);
    free(Xr->body);
    free(Yr->body);
    free(Yl->body);
    free(Xlr->body);
    free(Ylr->body);

    free(P1);
    free(P2);
    free(P3);
    free(Xl);
    free(Xr);
    free(Yr);
    free(Yl);
    free(Xlr);
    free(Ylr);

    return res;
}


BigNumber *mul(const BigNumber *X, const BigNumber *Y) {
    BigNumber *tmp_X = copy(X);
    BigNumber *tmp_Y = copy(Y);
    tmp_X->sign = 1;
    tmp_Y->sign = 1;
    BigNumber *res = karatsuba_mul(tmp_X, tmp_Y);
    normalize(res);
    res->sign = X->sign * Y->sign;
    return res;
}


BigNumber *copy(const BigNumber *a) {
    BigNumber *res = (BigNumber *) malloc(sizeof(BigNumber));
    res->sign = a->sign;
    res->intsAmount = a->intsAmount;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE itr = 0; itr < res->intsAmount; ++itr){
        res->body[itr] = a->body[itr];
    }
    return res;
}

BigNumber *add(const BigNumber *a, const BigNumber *b) {
    BigNumber *tmp_a = copy(a);
    tmp_a->sign = 1;
    BigNumber *tmp_b = copy(b);
    tmp_b->sign = 1;
    if (a->sign == 1 && b->sign == 1) return _add(tmp_a, tmp_b);
    else if (a->sign == 1 && b->sign == -1) return sub(tmp_a, tmp_b);
    else if (a->sign == -1 && b->sign == 1) return sub(tmp_b, tmp_a);
    else {
        BigNumber *res = _add(tmp_a, tmp_b);
        res->sign = -1;
        return res;
    }
}

int _absRelation(const BigNumber *a, const BigNumber *b, SIZE last_index) {
    if (a->body[last_index] > b->body[last_index]) return 1;
    else if (a->body[last_index] < b->body[last_index]) return -1;
    else if (last_index == 0) return 0;
    else return _absRelation(a, b, last_index - 1);
}

int absRelation(BigNumber *a, BigNumber *b) {
    delRedundantZeros(a);
    delRedundantZeros(b);
    if (a->intsAmount > b->intsAmount) return 1;
    else if (a->intsAmount < b->intsAmount) return -1;
    else return _absRelation(a, b, a->intsAmount-1);
}


BigNumber *sub(const BigNumber *a, const BigNumber *b) {
    BigNumber *tmp_a = copy(a);
    BigNumber *tmp_b = copy(b);
    tmp_a->sign = 1;
    tmp_b->sign = 1;

    int rel = absRelation(tmp_a, tmp_b);
    if (a->sign == 1 && b->sign == 1 && rel >= 0) return _sub(tmp_a, tmp_b);

    else if (a->sign == 1 && b->sign == 1 && rel == -1){
        BigNumber *res = _sub(tmp_b, tmp_a);
        res->sign = -1;
        return res;
    }
    else if (a->sign == -1 && b->sign == 1){
        BigNumber *res = _add(tmp_a, tmp_b);
        res->sign = -1;
        return res;
    }
    else if (a->sign == 1 && b->sign == -1) return _add(tmp_a, tmp_b);

    else if (a->sign == -1 && b->sign == -1){
        return sub(b, a);
    }
}