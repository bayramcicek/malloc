// C11 standard
// created by cicek on Apr 08, 2020 15:42

#include <stdio.h>

/* minimum alan(byte) istek miktarı */
#define MIN_REQUEST 1024  /* minimum bytes to request */

/* blok başlığı için kullanılan union yapısı */
union header {  /* block header */
    struct {
        /* free listesindeki bir sonraki blok */
        union header *ptr;  /* next block in free list */

        /* blok boyutunu tutan değişken */
        unsigned size;  /* size of this block */
    } str;
};

/* (union header) -> (Header) olarak temsil et */
typedef union header Header;

/* başlangıç için boş liste oluştur */
static Header empty_list;

/* boş listenin başlangıcı -> NULL ata */
static Header *freep = NULL;  /* start of free list */

/* free: *add bloğunu free listesine ekle */
void new_free(void *add) {  /* free: put the block *add in free list */

    /* p: free liste başı - start of free list */
    Header *block_p, *p;

    /* block_p -> blok başlığına işaret eder */
    block_p = (Header *) add - 1;  /* point to block header */

    /* yeterli blok bulunma süreci */
    for (p = freep; !(block_p > p && block_p < p->str.ptr); p = p->str.ptr)
        if (p >= p->str.ptr && (block_p > p || block_p < p->str.ptr))
            break;

    /* free listesinin yeniden düzenlenmesi - update free list */
    /* kendisinden büyük bloğa eklenecek ise sol tarafa ekle */
    if (block_p + block_p->str.size == p->str.ptr) {

        /* size bilgisini güncelle ve
         * blok pointer, eklenen alanın başlangıcını göstersin */
        block_p->str.size += p->str.ptr->str.size;
        block_p->str.ptr = p->str.ptr->str.ptr;
    } else
        block_p->str.ptr = p->str.ptr;

    /* kendisinden küçük bloğa eklenecek ise sağ tarafa ekle */
    if (p + p->str.size == block_p) {

        /* size bilgisini güncelle ve
         * eklenen alan başlangıç olarak, blok pointer'ın
         * gösterdiği yeri göstersin */
        p->str.size += block_p->str.size;
        p->str.ptr = block_p->str.ptr;
    } else
        p->str.ptr = block_p;

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
    if (nu < MIN_REQUEST)
        nu = MIN_REQUEST;

    /* sbrk(n): sistemden n byte istekte bulun */
    /* sbrk(n) returns a pointer to n more bytes of storage */
    cp = sbrk(nu * sizeof(Header));

    /* hafızada yer yok ise NULL döndür */
    if (cp == (char *) -1)  /* no space at all */
        return NULL;

    up = (Header *) cp;
    up->str.size = nu;

    new_free((void *) (up + 1));

    return freep;
}

/* new_malloc: yeni yazdığımız alan tahsis edici fonksiyon */
/* new_malloc: general-purpose storage allocator */
void *new_malloc(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;

    /* nunits sayısı - number of nunits */
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    /* free list yoksa -> size = 0 ata */
    if ((prevp = freep) == NULL) {  /* no free list yet */
        empty_list.str.ptr = freep = prevp = &empty_list;
        empty_list.str.size = 0;
    }

    /* yeterince büyük alan bulma süreci */
    for (p = prevp->str.ptr;; prevp = p, p = p->str.ptr) {

        /* yeterince büyük alan bulununca - big enough */
        if (p->str.size >= nunits) {

            /* tam istenilen kadar alan bulununca */
            if (p->str.size == nunits)
                prevp->str.ptr = p->str.ptr;
            else {
                /* liste sonundan tahsis et - allocate tail end */
                p->str.size -= nunits;
                p += p->str.size;
                p->str.size = nunits;
            }

            /* free listesinin başlangıç adresini güncelle */
            freep = prevp;

            /* ayrılan alanın pointer'ını geri döndür */
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
