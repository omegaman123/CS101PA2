//
// Created by Mark Medved on 2/6/19.
//

#ifndef CS101PA_2_APINT_H
#define CS101PA_2_APINT_H
typedef struct apint *apint_t;

extern apint_t apintFromString(char *num);

extern char *toString(apint_t num);

extern void print(apint_t num);

#endif //CS101PA_2_APINT_H
