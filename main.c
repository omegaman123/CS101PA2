#include <stddef.h>
#include <memory.h>
#include "apint.h"
#include "stdlib.h"
#include <stdio.h>

int main() {


    apint_t a = apintFromString("12345");
    char* s  = toString(a);
    printf("%s\n",s);
    free(s);
    print(a);

    a = apintFromString("-12345");
    s  = toString(a);
    printf("%s\n",s);
    free(s);
    print(a);




    return 0;
}