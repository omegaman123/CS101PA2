//
// Created by Mark Medved on 2/6/19.
//

#ifndef CS101PA_2_APINT_H
#define CS101PA_2_APINT_H
typedef struct apint *apint;

// Return an apint representation of a string with optional sign character.
// Caller is responsible for freeing the returned apint using free_apint();
extern apint apintFromString(char *num);

// Default constructor - return an empty apint.
// Caller is responsible for freeing the returned apint using free_apint();
extern apint apintDefault();

// Return string representation of passed in apint.
// Caller is responsible for freeing the returned string.
extern char *toString(apint num);

// Print out the string representation of the passed in apint on stdout.
extern void print(apint num);

// Frees the passed in apint.
extern void free_apint(apint *num);

// Return an apint result of 'a + b'.
// Caller is responsible for freeing the returned apint using free_apint();
extern apint add(apint a, apint b);

// Return an apint result of 'a - b';
// Caller is responsible for freeing the returned apint using free_apint();
extern apint subtract(apint a, apint b);

// Returns 0 if two apints are equal. -1 if 'a < b'. +1 if 'a > b'
extern int compareTo(apint a, apint b);

// Return an apint represention of a passed in integer.
// Caller is responsible for freeing the returned apint using free_apint();
extern struct apint *apintFromInt(int num);

// Return an apint result of 'a * b';
// Caller is responsible for freeing the returned apint using free_apint();
extern apint multiply(apint a, apint b);

#endif //CS101PA_2_APINT_H
