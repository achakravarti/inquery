#include <string.h>
#include "core.h"


extern void *inq_heap_new(size_t sz)
{
    void *bfr;

    inq_assert (sz);
    inq_require (bfr  = malloc(sz));
    
    memset(bfr, 0, sz);
    return bfr;
}


extern void inq_heap_resize(void **bfr, size_t sz)
{
    inq_assert (bfr && *bfr && sz);
    inq_require (*bfr = realloc(*bfr, sz));

}


extern void inq_heap_free(void **bfr)
{
    if (inq_likely (bfr && *bfr)) {
        free(*bfr);
        *bfr = NULL;
    }
}

