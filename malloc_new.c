// C11 standard
// created by cicek on Apr 08, 2020 15:42

#include <stdio.h>
#include <stdlib.h>
#include "malloc_new.h"

typedef long Align; /* for alignment to long boundary */

union header { /* block header */

    struct {
        union header *ptr;  /* next block if on free list */
        unsigned size;      /* size of this block */
    } s;

    Align x; /* force alignment of blocks */
};

typedef union header Header;


