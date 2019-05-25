// Created by David Zashkolny on 12.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

// TODO add input like table of coefficients
// TODO write the tests and user interface
// TODO refactor, comments etc.

#include <stdio.h>
#include "headers/BigNumbers.h"

BigInteger *read(){
    char *number = (char *) malloc(sizeof(char) * 1000);
    fgets(number, 1000, stdin);
    SIZE size = 0;
    while ((number[size] != '\n' && number[size] != ' ') && size < 1000) size++;
    BigInteger *res = fromChars(number, size);
    free(number);
    return res;
}


BigInteger *readAny(int base){
    char *number = (char *) malloc(sizeof(char) * 1000);
    fgets(number, 1000, stdin);
    SIZE size = 0;
    while ((number[size] != '\n' && number[size] != ' ') && size < 1000) size++;
    BigInteger *res = fromOtherChars(number, size, base);
    free(number);
    return res;
}


int main() {


    BigInteger *num1 = read();
    BigInteger *num2 = read();

    BigInteger *res_add = add(num1, num2);

    print(num1);
    print(num2);
    printf("addition:\n");
    print(res_add);

    BigInteger *res_sub = sub(num1, num2);
    printf("subtraction:\n");
    print(res_sub);

    BigInteger *res_mul = mul(num1, num2);
    printf("multiplication:\n");
    print(res_mul);

    BigInteger *res_div = divide(num1, num2);
    printf("division:\n");
    print(res_div);

    BigInteger *tmp = mul(res_div, num2);
    BigInteger *remainder = sub(num1, tmp);
    printf("remainder:\n");
    print(remainder);

    BigInteger **res_xgcd = xgcd(num1, num2);
    printf("gcd(a, b) = xa + yb\n");

    printf("gcd(a, b):\n");
    print(gcd(num1, num2));
    printf("x:\n");
    print(res_xgcd[0]);
    printf("y\n");
    print(res_xgcd[1]);

    printf("lcm(a, b):\n");
    print(lcm(num1, num2));

    printf("please, enter the number in binary system:\n");
    BigInteger *num3 = readAny(2);
    print(num3);

    printf("please, enter the number in hexadecimal system:\n");
    BigInteger *num4 = readAny(16);
    print(num4);
    return 0;
}