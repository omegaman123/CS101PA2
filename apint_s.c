//
// Created by Mark Medved on 2/6/19.
//

#include <stddef.h>
#include <memory.h>
#include "apint_s.h"
#include "stdlib.h"
#include <stdio.h>


struct apint_s {
    char sign;
    int size;
    int *digits;
};


struct apint_s *apintFromString(char *num) {
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

apint add(apint a, apint b) {

    char sgn;
    if (a->size < b->size) {
        apint tmp = a;
        a = b;
        b = tmp;
    }
    if (a->sign == '-' && b->sign == '-') {
        sgn = '-';
    } else {
        sgn = '+';
    }

    int *res = calloc(sizeof(int), a->size + 1);

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

    int *resOrdered = calloc(sizeof(int), i);
    for (int j = 0; j < i; j++) {
        int tmp = *((res + i - 1) - j);
        *(resOrdered + j) = tmp;

    }
    free(res);
    apint returnVal = calloc(sizeof(apint), 1);
    returnVal->digits = resOrdered;
    returnVal->sign = sgn;
    returnVal->size = i;
    return returnVal;

}

apint subtract(apint a, apint b){
    char sgn;

    if (a->size < b->size) {
        apint tmp = a;
        a = b;
        b = tmp;
    }

    if (b->sign == '-' && a->sign == '+'){
        return add(a,b);
    }

    if (a->sign == '-' && b->sign == '+'){
        apint returnVal = add(a,b);
        returnVal->sign = '-';
        return returnVal;
    }
    if (a->sign == '-' && b->sign == '-'){
      sgn = '-';
    }

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
        if ( val < 0){
            val = (place + 10) - subVal - carryout;
            carryout = 1;
        } else {
            carryout = 0;
        }
        counter++;
        *(res + i) = val;


    }

    int *resOrdered = calloc(sizeof(int), i);
    for (int j = 0; j < i; j++) {
        int tmp = *((res + i - 1) - j);
        *(resOrdered + j) = tmp;

    }
    free(res);
    apint returnVal = calloc(sizeof(apint), 1);
    returnVal->digits = resOrdered;
    returnVal->sign = sgn;
    returnVal->size = i;
    return returnVal;

}


void print(apint num) {
    if (num == NULL) {
        return;
    }
    char *s = toString(num);
    printf("%s\n", s);
    free(s);

}

void free_apint(apint *num) {
    if (num == NULL) {
        return;
    }
    free((*num)->digits);
    free(*num);
    *num = NULL;

}