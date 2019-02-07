//
// Created by Mark Medved on 2/6/19.
//

#ifndef CS101PA_2_APINT_H
#define CS101PA_2_APINT_H
typedef struct apint_s *apint;

extern apint apintFromString(char *num);

extern char *toString(apint num);

extern void print(apint num);
extern void free_apint(apint *num);
extern apint add(apint a, apint b);

#endif //CS101PA_2_APINT_H
