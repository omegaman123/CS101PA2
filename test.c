#include <stddef.h>
#include <memory.h>
#include "apint_s.h"
#include "stdlib.h"
#include <stdio.h>

void testAddFunc(char* numOne, char* numTwo,char* expected){
    char* s;
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    apint res = add(b,c);
    s = toString(res);
    printf("%s - %s = %s \tExpected %s\n",numOne, numTwo, s,expected);
    free(s);
    free_apint(&b);
    free_apint(&c);
    free_apint(&res);

}

void testSubtractFunc(char* numOne, char* numTwo,char* expected){
    char* s;
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    apint res = subtract(b,c);
    s = toString(res);
    printf("%s - %s = %s \tExpected %s\n",numOne, numTwo, s,expected);
    free(s);
    free_apint(&b);
    free_apint(&c);
    free_apint(&res);
}


void testMultiplyFunc(char* numOne, char* numTwo,char* expected){
    char* s;
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    apint res = multiply(b,c);
    s = toString(res);
    printf("%s * %s = %s; \tExpected: %s\n",numOne, numTwo, s,expected);
    free(s);
    free_apint(&b);
    free_apint(&c);
    free_apint(&res);


}

void testCompareToFunction(char* numOne, char* numTwo, int expected){

    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    int res = compareTo(b,c);
    printf("%s compared to %s is %d; \tExpected: %d\n",numOne, numTwo, res,expected);
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

    a = apintFromInt(12211);
    s  = toString(a);
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

    a = apintFromString("0");
    s  = toString(a);
    printf("%s\n",s);
    free(s);
    print(a);
    free_apint(&a);

    printf("\n");
    testAddFunc("123", "67","190");
    testAddFunc("11", "9","20");
    testAddFunc("99", "99","198");
    testAddFunc("-20", "-10","-30");
    testAddFunc("123456789","987654321","1111111110");
    testAddFunc("-20","10","-10");
    testAddFunc("20","-21","-1");
    testAddFunc("20","-19","1");
    printf("\n");
    testSubtractFunc("20","5","15");
    testSubtractFunc("20","10","10");
    testSubtractFunc("20","20","0");
    testSubtractFunc("200","199","1");
    testSubtractFunc("20","-20","40");
    testSubtractFunc("20","-19","39");
    testSubtractFunc("-10","20","-30");
    testSubtractFunc("-30","19","-49");
    testSubtractFunc("-20","-10","-10");
    testSubtractFunc("-20","-30","10");
    printf("\n");
    testCompareToFunction("20","10",1);
    testCompareToFunction("10","20",-1);
    testCompareToFunction("10","10",0);
    testCompareToFunction("200","10",1);
    testCompareToFunction("-20","20",-1);
    testCompareToFunction("-20","-10",-1);
    testCompareToFunction("20","-100",1);
    printf("\n");
    testMultiplyFunc("2","4","8");
    testMultiplyFunc("3","5","15");
    testMultiplyFunc("9","2","18");
    testMultiplyFunc("9","9","81");
    testMultiplyFunc("11","2","22");
    testMultiplyFunc("12","2","24");
    testMultiplyFunc("20","20","400");
    testMultiplyFunc("200","2","400");
    testMultiplyFunc("123","45","5535");
    testMultiplyFunc("-123","45","-5535");
    testMultiplyFunc("2020","20","40400");
    testMultiplyFunc("1","20","20");
    testMultiplyFunc("2020","0","0");
    testMultiplyFunc("1111111111111","20","22222222222220");
    testMultiplyFunc("-2020","-20","40400");
    testMultiplyFunc("123","456","56088");
    testMultiplyFunc("12345678987654321","456","5629629618370370376");
    testMultiplyFunc("12345678987654321","456789","5639370359091629635269");
    testMultiplyFunc("12345678987654321","456789123","5639371877610145116750483");

    return 0;
}

