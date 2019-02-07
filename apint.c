//
// Created by Mark Medved on 2/6/19.
//

#include <stddef.h>
#include <memory.h>
#include "apint.h"
#include "stdlib.h"
#include <stdio.h>



struct apint {
    char sign;
    int size;
    int *digits;
};


struct apint *apintFromString(char *num) {
    if (num == NULL) {
        return 0;
    }
    apint_t s = calloc(sizeof(apint_t), 1);

    if (*num == '-') {
        s->sign = '-';
        num += 1;
    } else if (*num == '+'){
        s->sign = '+';
        num += 1;
    } else {
        s->sign = '+';
    }

    s->size = strlen(num);
    s->digits = calloc(sizeof(int),s->size);
    for (int i = 0; i < s->size; i++) {

        char a = *(num + i);
        if (a < '0' || a > '9'){
            return NULL;
        }
        *(s->digits + i) = a - '0';
    }
    return s;
};

 char* toString(apint_t num){

    if(num == NULL){
        return NULL;
    }
    char *s;
    char *s1;
    if (num->sign == '-') {
        s = calloc(sizeof(char), num->size + 2);
        *s = '-';
        s1 = s+1;
    } else{
        s = calloc(sizeof(char),num->size + 1);
        s1 = s;
    }
     int i = 0;
    for (i = 0; i < num->size ; i++) {
        *(s1+i) = *(num->digits + i) + '0';
    }
    *(s1 + i) = '\0';

    return s;
}

void print(apint_t num){
    if(num == NULL){
        return;
    }
    char *s = toString(num);
    printf("%s\n",s);
    free(s);

 }