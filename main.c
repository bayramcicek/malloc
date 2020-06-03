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
        *(new_ptr + 7) = 99;  /* index'lere atama işlemleri */
        *(new_ptr + 0) = 12;
        *(new_ptr + 2) = 33;
        *(new_ptr + 3) = -45;
        *(new_ptr + 5) = 77;
        *(new_ptr + 8) = 11;
    }

    /* print -> index - value - address */
    printf("index\tvalue\taddress\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\t->%3d\t -> %p\n", i, *(new_ptr + i), (new_ptr + i));
    }

    /* new_free() */
    new_free(new_ptr);

    printf("\n***\n"
           "Alan tahsisi ve serbest bırakılması başarıyla tamamlandı!"
           "\nAllocation and deallocation is done successfully!\n"
           "***\n");


    /* OUTPUTS / ÇIKTILAR (IDE - Terminal):
     *
     *
running from IDE:

    Normal malloc():
    index	value	address
    0	->  0	 -> 0x5597d4aab6b0
    1	->  0	 -> 0x5597d4aab6b4
    2	->  0	 -> 0x5597d4aab6b8
    3	-> 49	 -> 0x5597d4aab6bc
    4	->  0	 -> 0x5597d4aab6c0
    5	->  0	 -> 0x5597d4aab6c4
    6	->  0	 -> 0x5597d4aab6c8
    7	->  0	 -> 0x5597d4aab6cc
    8	->  0	 -> 0x5597d4aab6d0
    9	->  0	 -> 0x5597d4aab6d4

    new_malloc():
    index	value	address
    0	-> 12	 -> 0x5597d4acffd0
    1	->  0	 -> 0x5597d4acffd4
    2	-> 33	 -> 0x5597d4acffd8
    3	->-45	 -> 0x5597d4acffdc
    4	->  0	 -> 0x5597d4acffe0
    5	-> 77	 -> 0x5597d4acffe4
    6	->  0	 -> 0x5597d4acffe8
    7	-> 99	 -> 0x5597d4acffec
    8	-> 11	 -> 0x5597d4acfff0
    9	->  0	 -> 0x5597d4acfff4

    ***
    Alan tahsisi ve serbest bırakılması başarıyla tamamlandı!
    Allocation and deallocation is done successfully!
    ***

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
    0       ->  0    -> 0x55d1d99f86b0
    1       ->  0    -> 0x55d1d99f86b4
    2       ->  0    -> 0x55d1d99f86b8
    3       -> 49    -> 0x55d1d99f86bc
    4       ->  0    -> 0x55d1d99f86c0
    5       ->  0    -> 0x55d1d99f86c4
    6       ->  0    -> 0x55d1d99f86c8
    7       ->  0    -> 0x55d1d99f86cc
    8       ->  0    -> 0x55d1d99f86d0
    9       ->  0    -> 0x55d1d99f86d4

    new_malloc():
    index   value   address
    0       -> 12    -> 0x55d1d9a1cfd0
    1       ->  0    -> 0x55d1d9a1cfd4
    2       -> 33    -> 0x55d1d9a1cfd8
    3       ->-45    -> 0x55d1d9a1cfdc
    4       ->  0    -> 0x55d1d9a1cfe0
    5       -> 77    -> 0x55d1d9a1cfe4
    6       ->  0    -> 0x55d1d9a1cfe8
    7       -> 99    -> 0x55d1d9a1cfec
    8       -> 11    -> 0x55d1d9a1cff0
    9       ->  0    -> 0x55d1d9a1cff4

    ***
    Alan tahsisi ve serbest bırakılması başarıyla tamamlandı!
    Allocation and deallocation is done successfully!
    ***


     */

    return 0;
}
