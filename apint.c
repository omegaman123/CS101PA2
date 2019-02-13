//
// Created by Mark Medved on 2/6/19.
//

#include <stddef.h>
#include <memory.h>
#include "apint.h"
#include "stdlib.h"
#include <stdio.h>

// An apint is comprised of a sign character, integer length or size, and an
// array of integers
struct apint {
    char sign;
    int size;
    int *digits;
};

struct apint *apintDefault() {
    apint s = calloc(sizeof(apint), 1);
    s->size = 0;
    s->sign = '+';
    s->digits = NULL;
    return s;
};


// Create an apint from a single string and optional sign character.
struct apint *apintFromString(char *num) {
    if (num == NULL) {
        return 0;
    }
    apint s = calloc(sizeof(apint), 1);

    if (*num == '-') {
        s->sign = '-';
        num += 1;
    } else if (*num == '+') {
        s->sign = '+';
        num += 1;
    } else {
        s->sign = '+';
    }

    s->size = strlen(num);
    s->digits = calloc(sizeof(int), s->size);
    for (int i = 0; i < s->size; i++) {

        char a = *(num + i);
        if (a < '0' || a > '9') {
            return NULL;
        }
        *(s->digits + i) = a - '0';
    }
    return s;
};

// Return number of digits in an integer.
int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

// Create an apint from a single integer.
struct apint *apintFromInt(int num) {
    char sgn = '+';
    apint s = calloc(sizeof(apint), 1);
    if (num < 0) {
        sgn = '-';
        num = abs(num);
    }
    s->size = countDigits(num);
    s->digits = calloc(sizeof(int), s->size);
    int digits[s->size];
    int c = 0;
    int n = num;
    while (n != 0) {
        digits[c] = n % 10;
        n /= 10;
        c++;
    }
    c = 0;
    for (int i = s->size - 1; i >= 0; i--) {
        *(s->digits + c) = digits[i];
        c++;
    }
    s->sign = sgn;

    return s;
};

// Return a string representation of apint int array with sign if negative.
char *toString(apint num) {
    if (num == NULL) {
        return NULL;
    }
    char *s;
    char *s1;
    if (num->sign == '-') {
        s = calloc(sizeof(char), num->size + 2);
        *s = '-';
        s1 = s + 1;
    } else {
        s = calloc(sizeof(char), num->size + 1);
        s1 = s;
    }
    int i = 0;
    for (i = 0; i < num->size; i++) {
        *(s1 + i) = *(num->digits + i) + '0';
    }
    *(s1 + i) = '\0';

    return s;
}

// Add apint a and b in form 'a + b' and return result.
apint add(apint a, apint b) {

    // Handle signs depending on whether there is a negative number present and
    // if its bigger and smaller than a positive number.
    char sgn = '+';
    if (a->size < b->size) {
        apint tmp = a;
        a = b;
        b = tmp;
    }
    if (a->sign == '+' && b->sign == '-') {
        b->sign = '+';
        if (compareTo(a, b) == -1) {
            apint tmp = subtract(b, a);
            b->sign = '-';
            tmp->sign = '-';
            return tmp;
        }
        apint tmp = subtract(a, b);
        b->sign = '-';
        return tmp;
    }
    if (a->sign == '-' && b->sign == '+') {
        a->sign = '+';
        if (compareTo(a, b) == 1) {
            apint tmp = subtract(a, b);
            b->sign = '-';
            tmp->sign = '-';
            return tmp;
        }
        apint tmp = subtract(b, a);
        b->sign = '-';
        return tmp;
    }
    if (a->sign == '-' && b->sign == '-') {
        sgn = '-';
    }

    int *res = calloc(sizeof(int), a->size + 1);

    // Iterate through each digit of both numbers starting at the end.
    // Record the sum and store the result in an array while handling
    // carryout if number > 10.
    int carryout = 0;
    int counter = 0;
    int i;
    for (i = 0; i < a->size; i++) {

        int addVal;
        if (counter > b->size - 1) {
            addVal = 0;
        } else {
            addVal = *((b->digits + b->size - 1) - counter);
        }
        int val = *(a->digits + (a->size - 1 - i)) + addVal + carryout;
        carryout = val / 10;
        val = val % 10;
        counter++;
        *(res + i) = val;
    }
    if (carryout > 0) {
        *(res + i++) = carryout;
    }

    int rs;
    for (rs = i; rs > 1; rs--) {
        if (*(res + rs - 1) != 0) {
            break;
        }
    }

    // Flip storage array as it is in reverse order.
    int *resOrdered = calloc(sizeof(int), rs);
    for (int j = 0; j < rs; j++) {
        int tmp = *((res + rs - 1) - j);
        *(resOrdered + j) = tmp;

    }
    free(res);
    apint returnVal = calloc(sizeof(apint), 1);
    returnVal->digits = resOrdered;
    returnVal->sign = sgn;
    returnVal->size = rs;
    return returnVal;

}

// Subtract two apints in the form 'a - b' and return the result.
apint subtract(apint a, apint b) {
    char sgn = '+';

    // Handle signs depending on whether there are negative numbers
    // and if they are greater or smaller than the other possibly
    // positive number.
    if (a->size < b->size) {
        apint tmp = a;
        a = b;
        b = tmp;
        sgn = '-';
    }

    if (b->sign == '-' && a->sign == '+') {

        b->sign = '+';
        apint res = add(a, b);
        b->sign = '-';
        return res;
    }

    if (a->sign == '-' && b->sign == '+') {
        a->sign = '+';
        apint returnVal = add(a, b);
        returnVal->sign = '-';
        a->sign = '+';
        return returnVal;
    }
    if (a->sign == '-' && b->sign == '-') {
        if (compareTo(a, b) == 1) {
            apint tmp = a;
            a = b;
            b = tmp;
        } else {
            sgn = '-';
        }
    }

    // Iterate through each digit of both numbers, starting from the last digit.
    // Store each difference in an array, handling carryout if the difference is
    // negative.
    int *res = calloc(sizeof(int), a->size);
    int carryout = 0;
    int counter = 0;
    int i;
    for (i = 0; i < a->size; i++) {

        int subVal;
        if (counter > b->size - 1) {
            subVal = 0;
        } else {
            subVal = *((b->digits + b->size - 1) - counter);
        }
        int place = *(a->digits + (a->size - 1 - i));
        int val = place - subVal - carryout;
        if (val < 0) {
            val = (place + 10) - subVal - carryout;
            carryout = 1;
        } else {
            carryout = 0;
        }
        counter++;
        *(res + i) = val;
    }

    int rs;
    for (rs = i; rs > 1; rs--) {
        if (*(res + rs - 1) != 0) {
            break;
        }
    }

    // Flip storage array as it is in reverse order.
    int *resOrdered = calloc(sizeof(int), rs);
    for (int j = 0; j < rs; j++) {
        int tmp = *((res + rs - 1) - j);
        *(resOrdered + j) = tmp;

    }
    free(res);
    apint returnVal = calloc(sizeof(apint), 1);
    returnVal->digits = resOrdered;
    returnVal->sign = sgn;
    returnVal->size = rs;
    return returnVal;

}

//Multiply two apints in form 'a * b', and return result.
apint multiply(apint a, apint b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    //Handle signs, same sign means positive, different means negative.
    char sgn;
    if (a->sign == b->sign) {
        sgn = '+';
    } else {
        sgn = '-';
    }

    if (a->size < b->size) {
        apint tmp = a;
        a = b;
        b = tmp;
    }

    //Create an apint res at 0 which all products for each place will be added to.
    apint res = apintFromString("0");

    int place = 0;

    // Iterate through each digit of the first, longer number with the shorter
    // second number. Record the result in an array attached to an apint and
    // add it to the the growing result.
    for (int i = 0; i <= b->size - 1; i++) {
        int size = a->size;
        int *currentPlace = calloc(sizeof(int), place + a->size + 1);
        for (int k = 0; k < place; k++) {
            currentPlace[a->size - 1 - k] = 0;
        }

        int l;
        int carryout = 0;
        for (l = 0; l <= a->size - 1; l++) {
            int product = *(b->digits + b->size - 1 - i) * *(a->digits + a->size - 1 - l);
            int val = product % 10;
            int placeVal = val + carryout;
            carryout = (product / 10);
            if (placeVal > 10) {
                int newPlaceVal = placeVal % 10;
                carryout = carryout + (placeVal / 10);
                currentPlace[(a->size) - l] = newPlaceVal;
            } else {
                currentPlace[(a->size) - l] = placeVal;
            }

        }
        int k;
        if (carryout > 0) {
            currentPlace[(a->size) - l] = carryout;
            size++;
        } else {
            for (k = 0; k < a->size + i; k++) {
                currentPlace[k] = currentPlace[k + 1];
            }
            currentPlace[k] = 0;

        }

        // Create temp apint and attach array to it and add it using add method to
        // the growing result.
        apint resTemp = apintFromString("0");
        resTemp->size = size + place;
        resTemp->digits = currentPlace;
        apint res1 = add(res, resTemp);

        free_apint(&resTemp);
        free(res);
        res = res1;
        place++;
    }

    res->sign = sgn;
    return res;

}


//Print out an apint utilizing the created toString method.
void print(apint num) {
    if (num == NULL) {
        return;
    }
    char *s = toString(num);
    printf("%s\n", s);
    free(s);

}

//Frees an apint by freeing its integer array and its own pointer.
void free_apint(apint *num) {
    if (num == NULL) {
        return;
    }
    free((*num)->digits);
    free(*num);
    *num = NULL;

}

//Compares apint a to apint b, returning -1 if 'a < b'; 0 if 'a = b'; 1 if 'a > b'
int compareTo(apint a, apint b) {
    if (a->sign == '-' && b->sign == '+') {
        return -1;

    } else if (a->sign == '+' && b->sign == '-') {
        return 1;
    } else if (a->sign == '-' && b->sign == '-') {
        if (a->size > b->size) {
            return -1;
        } else if (a->size < b->size) {
            return 1;
        } else {
            for (int i = 0; i < a->size; i++) {
                if (*(a->digits + i) > *(b->digits + i)) {
                    return -1;
                } else if (*(a->digits + i) < *(b->digits + i)) {
                    return 1;
                }
            }
            return 0;
        }
    } else {
        if (a->size > b->size) {
            return 1;
        } else if (a->size < b->size) {
            return -1;
        } else {
            for (int i = 0; i < a->size; i++) {
                if (*(a->digits + i) > *(b->digits + i)) {
                    return 1;
                } else if (*(a->digits + i) < *(b->digits + i)) {
                    return -1;
                }

            }
        }
        return 0;
    }
}