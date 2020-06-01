// C11 standard
// created by cicek on May 15, 2020 11:15

#ifndef MALLOC_NEW_MALLOC_H
#define MALLOC_NEW_MALLOC_H

// TODO: fonksiyon ve/veya veri yapıları tanımları.

/* free: put block ap in free list */
void free(void *);

/* malloc: general-purpose storage allocator */
void *new_malloc(unsigned);

#endif //MALLOC_NEW_MALLOC_H
