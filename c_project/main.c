// Created by David Zashkolny on 12.05.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

// TODO add the subtraction and improve addition to work with negative numbers
// TODO add the multiplication
// TODO add the division
// TODO add the gcd and lcm for big numbers
// TODO add the changing to other number system
// TODO add the reading number in binary and hexadecimal system
// TODO write the tests and user interface
// TODO refactor, comments etc.

#include <stdio.h>
#include "BigNumbers.h"

BigNumber *read(){
    char *number = (char *) malloc(sizeof(char) * 1000);
    fgets(number, 1000, stdin);
    SIZE size = 0;
    while ((number[size] != '\n' && number[size] != ' ') && size < 1000) size++;
    BigNumber *res = fromChars(number, size);
    free(number);
    return res;
}


int main() {


//    printf("%ld", binPow(10, 10));
//
//
//    int size;
//    scanf("%d", &size);
//    char *number = (char *) malloc(sizeof(char)*size);
//    scanf("\n");
//    for (int itr=0; itr < size; ++itr){
//        scanf("%c", &number[itr]);
//    }
//    scanf("\n");
//    BigNumber *num1 = fromChars(number, size);
//    free(number);
//
//    scanf("%d", &size);
//    number = (char *) malloc(sizeof(char)*size);
//    scanf("\n");
//    scanf("%[^\n]s", number);
//
//    BigNumber *num2 = fromChars(number, size);

    BigNumber *num1 = read();
    BigNumber *num2 = read();

    BigNumber *res_add = add(num1, num2);

    print(num1);
    print(num2);
    print(res_add);

    BigNumber *res_sub = sub(num1, num2);
    print(res_sub);

    BigNumber *res_mul = mul(num1, num2);
    print(res_mul);

    return 0;
}