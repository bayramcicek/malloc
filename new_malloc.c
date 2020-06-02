// C11 standard
// created by cicek on Apr 08, 2020 15:42

#include <stdio.h>
#include "new_malloc.h"

/* minimum alan istek miktarı */
#define NALLOC 1024 /* minimum #units to request */

/* blok başlığı için kullanılan union yapısı */
union header { /* block header */
    struct {
        /* free listesindeki bir sonraki blok */
        union header *ptr; /* next block if on free list */

        /* blok boyutunu tutan değişken */
        unsigned size; /* size of this block */
    } s;
};

/* (union header) -> (Header) olarak kısalt */
typedef union header Header;

/* başlangıç için boş liste oluştur */
static Header base; /* empty list to get started */

/* boş listenin başlangıcı -> NULL ata */
static Header *freep = NULL; /* start of free list */

/* free: *ap bloğunu free listesine ekle */
void new_free(void *ap) { /* free: put block ap in free list */
    Header *bp, *p;

    /* bp -> blok başlığına işaret eder */
    bp = (Header *) ap - 1; /* point to block header */

    /* yeterli blok bulunma süreci */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */

    if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) { /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) -1) /* no space at all */
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;

    new_free((void *) (up + 1));

    return freep;
}

/* new_malloc: general-purpose storage allocator */
/* new_malloc: (yeni yazdığımız) alan tahsis edici fonksiyon */
void *new_malloc(unsigned nbytes) {
    Header *p, *prevp;
//    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits) /* exactly */
                prevp->s.ptr = p->s.ptr;
            else { /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *) (p + 1);
        }
        if (p == freep) /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL; /* none left */

    }
}
