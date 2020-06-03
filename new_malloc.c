// C11 standard
// created by cicek on Apr 08, 2020 15:42

#include <stdio.h>

/* minimum alan istek miktarı */
#define NALLOC 1024  /* minimum #units to request */

/* blok başlığı için kullanılan union yapısı */
union header {  /* block header */
    struct {
        /* free listesindeki bir sonraki blok */
        union header *ptr;  /* next block if on free list */

        /* blok boyutunu tutan değişken */
        unsigned size;  /* size of this block */
    } s;
};

/* (union header) -> (Header) olarak temsil et */
typedef union header Header;

/* başlangıç için boş liste oluştur */
static Header base;  /* empty list to get started */

/* boş listenin başlangıcı -> NULL ata */
static Header *freep = NULL;  /* start of free list */

/* free: *ap bloğunu free listesine ekle */
void new_free(void *ap) {  /* free: put block ap in free list */
    Header *bp, *p;

    /* bp -> blok başlığına işaret eder */
    bp = (Header *) ap - 1;  /* point to block header */

    /* yeterli blok bulunma süreci */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;  /* freed block at start or end of arena */

    /* free listesinin yeniden düzenlenmesi */
    /* update free list */
    if (bp + bp->s.size == p->s.ptr) {  /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) {  /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;

    /* p, artık free listesinin başlangıcı oluyor */
    freep = p;  /* p: start of free list */
}

/* morecore: free listesinde istenilen alan yok ise
 * işletim sisteminden alan tahsisi iste */
/* morecore: ask system for more memory */
static Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    /* istenilen alan minimum istekten küçük ise
     * bunu minimum isteğe genişlet */
    if (nu < NALLOC)
        nu = NALLOC;

    /* sbrk(n): sistemden n byte istekte bulun */
    /* sbrk(n) returns a pointer to n more bytes of storage */
    cp = sbrk(nu * sizeof(Header));

    /* hafızada yer yok ise NULL döndür */
    if (cp == (char *) -1)  /* no space at all */
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;

    /* tahsis edilen alandan sonraki alanları serbest bırak */
    new_free((void *) (up + 1));

    return freep;
}

/* new_malloc: (yeni yazdığımız) alan tahsis edici fonksiyon */
/* new_malloc: general-purpose storage allocator */
void *new_malloc(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;

    /* istenilen alan + header bilgisi */
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    /* free list yoksa -> size = 0 ata */
    if ((prevp = freep) == NULL) {  /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    /* yeterince büyük alan bulma süreci */
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {

        /* yeterince büyük alan bulununca */
        if (p->s.size >= nunits) {  /* big enough */

            /* tam istenilen kadar alan bulununca */
            if (p->s.size == nunits)  /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {  /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            /* free listesinin başlangıç adresini güncelle */
            freep = prevp;

            /* header yapısından 1 sonraki tahsis edilmiş alanı geri döndür */
            return (void *) (p + 1);
        }

        /* free listesinde yeteri kadar alan yok ise
         * işletim sisteminden istekte bulun.
         * eğer NULL dönüyor ise boş alan yok demektir */
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;  /* none left */

    }
}
