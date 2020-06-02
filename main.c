// C11 standard
// created by cicek on Feb 13, 2020 09:18

#include <stdio.h>
#include <stdlib.h>
#include "new_malloc.h"

int main() {

    /* -------------------------- Normal malloc() ------------------------- */

    printf("\nNormal malloc():\n");
    int *ptr;

    /* normal malloc() fonksiyonu - a block of 10 ints */
    /* malloc() returns a pointer from the allocated memory */
    ptr = malloc(10 * sizeof(int));

    if (ptr != NULL) {
        *(ptr + 3) = 49;  /* index 3'e 49'u ata - assign 49 to 3rd int */
    }

    /* print -> index - value - address */
    printf("index\tvalue\taddress\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\t->%3d\t -> %p\n", i, *(ptr + i), (ptr + i));
    }

    /* normal free() */
    free(ptr);


    /* --------------------------- new_malloc() --------------------------- */

    printf("\nnew_malloc():\n");
    int *new_ptr;

    /* yeni yazdığımız new_malloc() fonksiyonu - a block of 10 ints */
    /* new_malloc() returns a pointer from the allocated memory */
    new_ptr = new_malloc(10 * sizeof(int));

    if (new_ptr != NULL) {
        *(new_ptr + 7) = 99;  /* index 7'ye 99'u ata - assign 99 to 7th int */
    }

    /* print -> index - value - address */
    printf("index\tvalue\taddress\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\t->%3d\t -> %p\n", i, *(new_ptr + i), (new_ptr + i));
    }

    /* new_free() */
    new_free(ptr);


    /* OUTPUTS / ÇIKTILAR (IDE - Terminal):
     *
     *
running from IDE:

    Normal malloc():
    index	value	address
    0	->  0	 -> 0x55ef1a6b26b0
    1	->  0	 -> 0x55ef1a6b26b4
    2	->  0	 -> 0x55ef1a6b26b8
    3	-> 49	 -> 0x55ef1a6b26bc
    4	->  0	 -> 0x55ef1a6b26c0
    5	->  0	 -> 0x55ef1a6b26c4
    6	->  0	 -> 0x55ef1a6b26c8
    7	->  0	 -> 0x55ef1a6b26cc
    8	->  0	 -> 0x55ef1a6b26d0
    9	->  0	 -> 0x55ef1a6b26d4

    new_malloc():
    index	value	address
    0	->  0	 -> 0x55ef1a6d6fd0
    1	->  0	 -> 0x55ef1a6d6fd4
    2	->  0	 -> 0x55ef1a6d6fd8
    3	->  0	 -> 0x55ef1a6d6fdc
    4	->  0	 -> 0x55ef1a6d6fe0
    5	->  0	 -> 0x55ef1a6d6fe4
    6	->  0	 -> 0x55ef1a6d6fe8
    7	-> 99	 -> 0x55ef1a6d6fec
    8	->  0	 -> 0x55ef1a6d6ff0
    9	->  0	 -> 0x55ef1a6d6ff4

    Process finished with exit code 0

     */

    /*
     *
     *
running from terminal:

    cicek@ubuntu2004:~$ gcc main.c new_malloc.c
    cicek@ubuntu2004:~$ ./a.out

    Normal malloc():
    index   value   address
    0       ->  0    -> 0x5625e6e656b0
    1       ->  0    -> 0x5625e6e656b4
    2       ->  0    -> 0x5625e6e656b8
    3       -> 49    -> 0x5625e6e656bc
    4       ->  0    -> 0x5625e6e656c0
    5       ->  0    -> 0x5625e6e656c4
    6       ->  0    -> 0x5625e6e656c8
    7       ->  0    -> 0x5625e6e656cc
    8       ->  0    -> 0x5625e6e656d0
    9       ->  0    -> 0x5625e6e656d4

    new_malloc():
    index   value   address
    0       ->  0    -> 0x5625e6e89fd0
    1       ->  0    -> 0x5625e6e89fd4
    2       ->  0    -> 0x5625e6e89fd8
    3       ->  0    -> 0x5625e6e89fdc
    4       ->  0    -> 0x5625e6e89fe0
    5       ->  0    -> 0x5625e6e89fe4
    6       ->  0    -> 0x5625e6e89fe8
    7       -> 99    -> 0x5625e6e89fec
    8       ->  0    -> 0x5625e6e89ff0
    9       ->  0    -> 0x5625e6e89ff4


     */

    return 0;
}
