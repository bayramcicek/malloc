// C11 standard
// created by cicek on Feb 13, 2020 09:18

#include <stdio.h>
#include <stdlib.h>
//#include "malloc_new.h"

int main() {
    printf("Hello, World!\n");

    int *ptr;

    /* normal malloc fonksiyonu */
    /* a block of 5 ints */
    ptr = malloc(5 * sizeof(int)); // malloc returns a pointer to the allocated memory.

    if (ptr != NULL) {
        *(ptr + 3) = 50;  /* assign 50 to 3th int */
    }

    for (int i = 0; i < 5; i++) {
        printf("%d: %d\n", i, *(ptr + i));
    }
    /*
     * output:

Hello, World!
0: 0
1: 0
2: 0
3: 50
4: 0

Process finished with exit code 0
     *
     */

    printf("%lu\n", sizeof(char*));
    printf("%lu", sizeof(long*));


    return 0;
}
