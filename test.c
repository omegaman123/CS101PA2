#include <stddef.h>
#include <memory.h>
#include "apint.h"
#include "stdlib.h"
#include <stdio.h>

// Creates two apints from the passed strings, computes 'numOne + numTwo'
// and prints out the result and expected value.
// After, free created apints and strings.
void testAddFunc(char *numOne, char *numTwo, char *expected) {
    char *s;
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    apint res = add(b, c);
    s = toString(res);
    printf("%s - %s = %s; \tExpected %s\n", numOne, numTwo, s, expected);
    free(s);
    free_apint(&b);
    free_apint(&c);
    free_apint(&res);

}

// Creates two apints from the passed strings, computes 'numOne - numTwo'
// and prints out the result and expected value.
// After, free created apints and strings.
void testSubtractFunc(char *numOne, char *numTwo, char *expected) {
    char *s;
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    apint res = subtract(b, c);
    s = toString(res);
    printf("%s - %s = %s; \tExpected %s\n", numOne, numTwo, s, expected);
    free(s);
    free_apint(&b);
    free_apint(&c);
    free_apint(&res);
}

// Creates two apints from the passed strings, computes 'numOne * numTwo'
// and prints out the result and expected value.
// After, free created apints and strings.
void testMultiplyFunc(char *numOne, char *numTwo, char *expected) {
    char *s;
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    apint res = multiply(b, c);
    s = toString(res);
    printf("%s * %s = %s; \tExpected: %s\n", numOne, numTwo, s, expected);
    free(s);
    free_apint(&b);
    free_apint(&c);
    free_apint(&res);
}


// Creates two apints from the passed strings, computes 'numOne C.T numTwo'
// and prints out the result and expected value.
// After, free created apints and strings.
void testCompareToFunction(char *numOne, char *numTwo, int expected) {
    apint b = apintFromString(numOne);
    apint c = apintFromString(numTwo);
    int res = compareTo(b, c);
    printf("%s compared to %s is %d; \tExpected: %d\n", numOne, numTwo, res, expected);
    free_apint(&b);
    free_apint(&c);
}


int main() {

    printf("Testing toString method and print method for apints.\n");
    apint a = apintFromString("12345");
    char *s = toString(a);
    printf("%s\n", s);
    free(s);
    print(a);
    free_apint(&a);

    printf("Printing empty apint. Expecting empty lines\n");
    a = apintDefault();
    s = toString(a);
    printf("%s\n", s);
    free(s);
    print(a);
    free_apint(&a);

    a = apintFromInt(12211);
    s = toString(a);
    printf("%s\n", s);
    free(s);
    print(a);
    free_apint(&a);

    a = apintFromString("-12345");
    s = toString(a);
    printf("%s\n", s);
    free(s);
    print(a);
    free_apint(&a);

    a = apintFromString("0");
    s = toString(a);
    printf("%s\n", s);
    free(s);
    print(a);
    free_apint(&a);

    printf("\n");
    testAddFunc("123", "67", "190");
    testAddFunc("11", "9", "20");
    testAddFunc("99", "99", "198");
    testAddFunc("-20", "10", "-10");
    testAddFunc("20", "-21", "-1");
    testAddFunc("20", "-19", "1");
    testAddFunc("-20", "-10", "-30");
    testAddFunc("123456789", "987654321", "1111111110");
    printf("\n");

    testSubtractFunc("20", "5", "15");
    testSubtractFunc("20", "10", "10");
    testSubtractFunc("20", "20", "0");
    testSubtractFunc("200", "199", "1");
    testSubtractFunc("20", "-20", "40");
    testSubtractFunc("20", "-19", "39");
    testSubtractFunc("-10", "20", "-30");
    testSubtractFunc("-30", "19", "-49");
    testSubtractFunc("-20", "-10", "-10");
    testSubtractFunc("-20", "-30", "10");
    testSubtractFunc("1111111110", "987654321", "123456789");
    testSubtractFunc("1111111110", "123456789", "987654321");
    testSubtractFunc("98123749871234987","12345678987654382374878","-12345580863904511139891");
    testSubtractFunc("12345678987654382374878","98123749871234987","12345580863904511139891");

    printf("\n");

    testCompareToFunction("20", "10", 1);
    testCompareToFunction("10", "20", -1);
    testCompareToFunction("10", "10", 0);
    testCompareToFunction("200", "10", 1);
    testCompareToFunction("-20", "20", -1);
    testCompareToFunction("-20", "-10", -1);
    testCompareToFunction("20", "-100", 1);
    printf("\n");

    // Expected values for large multiplication was found using a big calculator,
    // https://www.calculator.net/big-number-calculator.html
    // Multiply heavily uses the add method for apints and would not work
    // without the add method functioning properly.
    testMultiplyFunc("2", "4", "8");
    testMultiplyFunc("3", "5", "15");
    testMultiplyFunc("9", "2", "18");
    testMultiplyFunc("9", "9", "81");
    testMultiplyFunc("11", "2", "22");
    testMultiplyFunc("12", "2", "24");
    testMultiplyFunc("1", "20", "20");
    testMultiplyFunc("2020", "0", "0");
    testMultiplyFunc("20", "20", "400");
    testMultiplyFunc("200", "2", "400");
    testMultiplyFunc("123", "45", "5535");
    testMultiplyFunc("123", "456", "56088");
    testMultiplyFunc("-123", "45", "-5535");
    testMultiplyFunc("2020", "20", "40400");
    testMultiplyFunc("-2020", "-20", "40400");
    testMultiplyFunc("1111111111111", "20", "22222222222220");
    testMultiplyFunc("28931489238942893","14","405040849345200502");
    testMultiplyFunc("12345678987654321", "456", "5629629618370370376");
    testMultiplyFunc("12345678987654321", "456789", "5639370359091629635269");
    testMultiplyFunc("12345678987654321", "456789123", "5639371877610145116750483");
    testMultiplyFunc("86923149862314","28931489238942893","2514816174856557902319858834402");

    return 0;
}

