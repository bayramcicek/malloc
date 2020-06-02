// C11 standard
// created by cicek on May 15, 2020 11:15

#ifndef MALLOC_NEW_MALLOC_H
#define MALLOC_NEW_MALLOC_H

// TODO: fonksiyon ve/veya veri yapıları tanımları.

/* free: put the block in free list */
/* free: belirlenen bloğu free listesine ekle */
void free(void *);

/* new_malloc: general-purpose storage allocator */
/* new_malloc: (yeni yazdığımız) alan tahsis edici fonksiyon */
void *new_malloc(unsigned);

#endif //MALLOC_NEW_MALLOC_H
