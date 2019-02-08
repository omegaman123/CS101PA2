#include <stddef.h>
#include <memory.h>
#include "apint_s.h"
#include "stdlib.h"
#include <stdio.h>

void testAddFunc(char* numOne, char* numTwo){
    char* s;
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    apint res = add(b,c);
    s = toString(res);
    printf("%s + %s = %s\n",numOne, numTwo, s);
    free(s);
    free_apint(&b);
    free_apint(&c);
    free_apint(&res);

}

void testSubtractFunc(char* numOne, char* numTwo){
    char* s;
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    apint res = subtract(b,c);
    s = toString(res);
    printf("%s - %s = %s\n",numOne, numTwo, s);
    free(s);
    free_apint(&b);
    free_apint(&c);
    free_apint(&res);
}

void testCompareToFunction(char* numOne, char* numTwo){

    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    int res = compareTo(b,c);
    printf("%s compared to %s is %d\n",numOne, numTwo, res);
    free_apint(&b);
    free_apint(&c);
}



int main() {


    apint a = apintFromString("12345");
    char* s  = toString(a);
    printf("%s\n",s);
    free(s);
    print(a);
    free_apint(&a);


    a = apintFromString("-12345");
    s  = toString(a);
    printf("%s\n",s);
    free(s);
    print(a);
    free_apint(&a);

    printf("\n");
    testAddFunc("123", "67");
    testAddFunc("11", "9");
    testAddFunc("99", "99");
    testAddFunc("-20", "-10");
    testAddFunc("123456789","987654321");
    testAddFunc("-20","10");
    testAddFunc("20","-21");
    testAddFunc("20","-19");
    printf("\n");
    testSubtractFunc("20","5");
    testSubtractFunc("20","10");
    testSubtractFunc("20","20");
    testSubtractFunc("200","199");
    testSubtractFunc("20","-20");
    testSubtractFunc("20","-19");
    testSubtractFunc("-10","20");
    testSubtractFunc("-30","19");
    testSubtractFunc("-20","-10");
    testSubtractFunc("-20","-30");
    printf("\n");
    testCompareToFunction("20","10");
    testCompareToFunction("10","20");
    testCompareToFunction("10","10");
    testCompareToFunction("200","10");
    testCompareToFunction("-20","20");
    testCompareToFunction("-20","-10");
    testCompareToFunction("20","-100");


    return 0;
}

