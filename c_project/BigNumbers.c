// Created by David Zashkolny on 24.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include "BigNumbers.h"

const char GLOBAL_NUMBERS[] = "0123456789abcdefghijklmnopqrstuvwxyz";


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


int convert2int(char numb) {
    int res = -1;
    for (int itr = 0; itr < 36; ++itr){
        if (GLOBAL_NUMBERS[itr] == numb){
            res = itr;
            break;
        }
    }
    return res;
}


BigInteger *fromChars(const char *number, SIZE size) {
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
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


BigInteger *fromOtherChars(const char *number, SIZE size, int base) {
    BigInteger *res = fromInt(0);
    int start = 0;
    if (number[start] == '-'){
        res->sign = -1;
        start = 1;
    }
    if (base > 36 || base < 2){
        exit(1);
    }
    BigInteger *tmpAdd;
    BigInteger *tmpRes;
    BigInteger *tmpMul;
    BigInteger *multiplier = fromInt(1);
    BigInteger *bigBase = fromInt(base);
    int tmp_num;
    for (SIZE itr = size-1; itr >= start; --itr){
        tmp_num = convert2int(number[itr]);
        if (tmp_num == -1 || tmp_num >= base){
            exit(1);
        }

        tmpMul = fromInt(tmp_num);
        tmpAdd = mul(tmpMul, multiplier);
        tmpRes = add(res, tmpAdd);

        free(res->body);
        free(res);
        free(tmpAdd->body);
        free(tmpAdd);
        free(tmpMul->body);
        free(tmpMul);

        res = tmpRes;

        tmpMul = mul(multiplier, bigBase);
        free(multiplier->body);
        free(multiplier);
        multiplier = tmpMul;
        if (itr == 0) break;
    }
    free(multiplier->body);
    free(multiplier);
    free(bigBase->body);
    free(bigBase);
    return res;
}


void print(const BigInteger *a) {
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


void delRedundantZeros(BigInteger *a) {
    while (a->body[a->intsAmount-1] == 0 && a->intsAmount > 1) a->intsAmount--;
    ELEM_TYPE *res = (ELEM_TYPE * ) malloc(sizeof(ELEM_TYPE) * a->intsAmount);
    for (SIZE itr = 0; itr < a->intsAmount; itr++) {
        res[itr] = a->body[itr];
    }
    free(a->body);
    a->body = res;
}


BigInteger *_add(const BigInteger *a, const BigInteger *b) {

    int carry = 0;
    int base = binPow(10, ELEM_SIZE_NUM);
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
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


BigInteger *_sub(const BigInteger *a, const BigInteger *b) {

    int carry = 0;
    int base = binPow(10, ELEM_SIZE_NUM);
    struct BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
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



void normalize(BigInteger *n) {

    ELEM_TYPE base = binPow(10, ELEM_SIZE_NUM);
    for (SIZE i = 0; i < n->intsAmount; ++i){
        n->body[i+1] += n->body[i] / base;

        n->body[i] %= base;
        if (n->body[i] < 0) n->body[i] = base - n->body[i];
    }
}


void extendBigInteger(BigInteger *x, SIZE n) {
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


BigInteger *karatsuba_mul(BigInteger *X, BigInteger *Y) {
    SIZE n = MAX(X->intsAmount, Y->intsAmount);
    if (n > 1){
        extendBigInteger(X, n);
        extendBigInteger(Y, n);
    }

    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
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
    BigInteger *Xr = (BigInteger *) malloc(sizeof(BigInteger));
    BigInteger *Xl = (BigInteger *) malloc(sizeof(BigInteger));
    BigInteger *Yr = (BigInteger *) malloc(sizeof(BigInteger));
    BigInteger *Yl = (BigInteger *) malloc(sizeof(BigInteger));

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

    BigInteger *P1 = karatsuba_mul(Xl, Yl);
    BigInteger *P2 = karatsuba_mul(Xr, Yr);

    BigInteger *Xlr = (BigInteger *) malloc(sizeof(BigInteger));
    BigInteger *Ylr = (BigInteger *) malloc(sizeof(BigInteger));

    Xlr->intsAmount = Ylr->intsAmount = Xr->intsAmount;
    Xlr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xlr->intsAmount);
    Ylr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xlr->intsAmount);
    for (SIZE itr = 0; itr < Xlr->intsAmount; itr++){
        Xlr->body[itr] = Xl->body[itr] + Xr->body[itr];
        Ylr->body[itr] = Yl->body[itr] + Yr->body[itr];
    }

    BigInteger *P3 = karatsuba_mul(Xlr, Ylr);
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


BigInteger *mul(const BigInteger *X, const BigInteger *Y) {
    BigInteger *tmp_X = copy(X);
    BigInteger *tmp_Y = copy(Y);
    tmp_X->sign = 1;
    tmp_Y->sign = 1;
    BigInteger *res = karatsuba_mul(tmp_X, tmp_Y);
    normalize(res);
    delRedundantZeros(res);
    res->sign = X->sign * Y->sign;
    free(tmp_X->body);
    free(tmp_Y->body);
    free(tmp_X);
    free(tmp_Y);
    return res;
}


BigInteger *copy(const BigInteger *a) {
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
    res->sign = a->sign;
    res->intsAmount = a->intsAmount;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE itr = 0; itr < res->intsAmount; ++itr){
        res->body[itr] = a->body[itr];
    }
    return res;
}

BigInteger *add(const BigInteger *a, const BigInteger *b) {
    BigInteger *tmp_a = copy(a);
    tmp_a->sign = 1;
    BigInteger *tmp_b = copy(b);
    tmp_b->sign = 1;
    BigInteger *res;
    if (a->sign == 1 && b->sign == 1) res = _add(tmp_a, tmp_b);
    else if (a->sign == 1 && b->sign == -1) res = sub(tmp_a, tmp_b);
    else if (a->sign == -1 && b->sign == 1) res = sub(tmp_b, tmp_a);
    else {
        res = _add(tmp_a, tmp_b);
        res->sign = -1;
    }
    free(tmp_a->body);
    free(tmp_b->body);
    free(tmp_a);
    free(tmp_b);
    delRedundantZeros(res);
    return res;
}

int _absRelation(const BigInteger *a, const BigInteger *b, SIZE last_index) {
    if (a->body[last_index] > b->body[last_index]) return 1;
    else if (a->body[last_index] < b->body[last_index]) return -1;
    else if (last_index == 0) return 0;
    else return _absRelation(a, b, last_index - 1);
}

int absRelation(BigInteger *a, BigInteger *b) {
    delRedundantZeros(a);
    delRedundantZeros(b);
    if (a->intsAmount > b->intsAmount) return 1;
    else if (a->intsAmount < b->intsAmount) return -1;
    else return _absRelation(a, b, a->intsAmount-1);
}


BigInteger *sub(const BigInteger *a, const BigInteger *b) {
    BigInteger *tmp_a = copy(a);
    BigInteger *tmp_b = copy(b);
    tmp_a->sign = 1;
    tmp_b->sign = 1;

    BigInteger *res;
    int rel = absRelation(tmp_a, tmp_b);
    if (a->sign == 1 && b->sign == 1 && rel >= 0) res = _sub(tmp_a, tmp_b);

    else if (a->sign == 1 && b->sign == 1 && rel == -1){
        res = _sub(tmp_b, tmp_a);
        res->sign = -1;
    }
    else if (a->sign == -1 && b->sign == 1){
        res = _add(tmp_a, tmp_b);
        res->sign = -1;
    }
    else if (a->sign == 1 && b->sign == -1) res = _add(tmp_a, tmp_b);

    else {
        res = sub(b, a);
    }
    free(tmp_a->body);
    free(tmp_b->body);
    free(tmp_a);
    free(tmp_b);
    delRedundantZeros(res);
    return res;
}


void shiftRight(BigInteger *number) {
    delRedundantZeros(number);
    extendBigInteger(number, number->intsAmount+1);
    for (SIZE itr = number->intsAmount-1; itr > 0; --itr){
        number->body[itr] = number->body[itr-1];
    }
    number->body[0] = 0;
}


BigInteger *divide(const BigInteger *X, const BigInteger *Y) {
    if (Y->intsAmount == 1 && Y->body[0] == 0){
        exit(1);
    }

    BigInteger *tmp_y = copy(Y);
    tmp_y->sign = 1;

    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
    res->sign = 1;
    res->intsAmount = X->intsAmount;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);

    BigInteger *cur = fromInt(0);
    for (SIZE i = X->intsAmount-1; i >= 0; --i){
        shiftRight(cur);
        cur->body[0] = X->body[i];
        delRedundantZeros(cur);
        int x = 0, l = 0, r = binPow(10, ELEM_SIZE_NUM);
        while (l <= r){
            int m = (l + r) / 2;
            BigInteger *tmp_m = (BigInteger *) malloc(sizeof(BigInteger));
            tmp_m->sign = 1;
            tmp_m->intsAmount = 1;
            tmp_m->body = (ELEM_TYPE* ) malloc(sizeof(ELEM_TYPE));
            tmp_m->body[0] = m;

            BigInteger *tmp = mul(tmp_y, tmp_m);
            if (absRelation(tmp, cur) <= 0){
                x = m;
                l = m + 1;
            } else r = m - 1;
            free(tmp->body);
            free(tmp);

            free(tmp_m->body);
            free(tmp_m);
        }
        res->body[i] = x;
        BigInteger *tmp_x = (BigInteger *) malloc(sizeof(BigInteger));
        tmp_x->sign = 1;
        tmp_x->intsAmount = 1;
        tmp_x->body = (ELEM_TYPE*) malloc(sizeof(ELEM_TYPE));
        tmp_x->body[0] = x;
        BigInteger *tmp_cur = mul(tmp_y, tmp_x);
        BigInteger *tmp_cur2 = sub(cur, tmp_cur);
        free(cur->body);
        free(cur);
        cur = tmp_cur2;
        free(tmp_cur->body);
        free(tmp_cur);
        free(tmp_x->body);
        free(tmp_x);
        if (i == 0){
            break;
        }
    }
    free(tmp_y->body);
    free(tmp_y);
    res->sign = X->sign * Y->sign;
    if (res->sign == -1 && !(cur->intsAmount == 1 && cur->body[0] == 0)){
        res->body[0] += 1;
        normalize(res);
    }
    delRedundantZeros(res);
    return res;
}


BigInteger **xgcd(const BigInteger *a, const BigInteger *b) {

    BigInteger *tmp_a = copy(a);
    tmp_a->sign = 1;
    BigInteger *tmp_b = copy(b);
    tmp_b->sign = 1;

    BigInteger **resArray = (BigInteger **) malloc(sizeof(BigInteger *) * 3);
    if (absRelation(tmp_a, tmp_b) == -1){
        BigInteger *c = tmp_a;
        tmp_a = tmp_b;
        tmp_b = c;
    }

    if (tmp_b->intsAmount == 1 && tmp_b->body[0] == 0){

        resArray[0] = fromInt(1);
        resArray[1] = fromInt(0);
        resArray[2] = copy(tmp_a);

    } else {
        BigInteger *q = divide(tmp_a, tmp_b);
        BigInteger *tmp = mul(q, tmp_b);
        BigInteger *r = sub(tmp_a, tmp);
        free(tmp->body);
        free(tmp);

        if (absRelation(tmp_b, r) != 1){
            exit(1);
        }
        BigInteger **preArray = xgcd(tmp_b, r);
        resArray[0] = preArray[1];

        tmp = mul(q, preArray[1]);
        resArray[1] = sub(preArray[0], tmp);
        free(tmp->body);
        free(tmp);

        resArray[2] =preArray[2];
        free(preArray[0]->body);
        free(preArray[0]);
        free(q->body);
        free(q);
        free(r->body);
        free(r);
    }
    free(tmp_a->body);
    free(tmp_b->body);
    return resArray;
}

BigInteger *gcd(const BigInteger *a, const BigInteger *b) {

    BigInteger *tmp_a = copy(a);
    tmp_a->sign = 1;
    BigInteger *tmp_b = copy(b);
    tmp_b->sign = 1;

    while (!(tmp_b->intsAmount == 1 && tmp_b->body[0] == 0)){
        BigInteger *q = divide(tmp_a, tmp_b);
        BigInteger *tmp = mul(q, tmp_b);
        BigInteger *remainder = sub(tmp_a, tmp);
        free(q->body);
        free(q);
        free(tmp->body);
        free(tmp);

        free(tmp_a->body);
        free(tmp_a);
        tmp_a = tmp_b;
        tmp_b = remainder;
    }
    return tmp_a;
}


BigInteger *lcm(const BigInteger *a, const BigInteger *b) {
    BigInteger *tmp = mul(a, b);
    BigInteger *_gcd = gcd(a, b);
    BigInteger *res = divide(tmp, _gcd);
    free(tmp->body);
    free(tmp);
    free(_gcd->body);
    free(_gcd);
    return res;
}

BigInteger *fromInt(ELEM_TYPE num) {
    ELEM_TYPE base = binPow(10, ELEM_SIZE_NUM);
    ELEM_TYPE abs_num = num < 0 ? -num : num;
    BigInteger *res = (BigInteger*) malloc(sizeof(BigInteger));
    res->sign = num < 0 ? -1 : 1;
    if (abs_num < base){
        res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE));
        res->body[0] = num;
        res->intsAmount = 1;
    } else {
        res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * 2);
        res->body[0] = abs_num % base;
        res->body[1] = abs_num / base;
        res->intsAmount = 2;
    }
    return res;
}
