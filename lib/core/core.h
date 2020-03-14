#if (!defined INQUERY_CORE_HEADER_INCLUDED)
#define INQUERY_CORE_HEADER_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#if (defined __GNUC__ || defined __clang__)
#   define inq_likely(p) (__builtin_expect (!!(p), 1))
#else
#   define inq_likely(p) (p)
#   warning "inq_likely() has no effect on non GCC-compatible C compilers"
#endif


#if (defined __GNUC__ || defined __clang__)
#   define inq_unlikely(p) (__builtin_expect (!!(p), 0))
#else
#   define inq_unlikely(p) (p)
#   warning "inq_likely() has no effect on non GCC-compatible C compilers"
#endif


#if !(defined NDEBUG)
#   define inq_assert(p) do {                                          \
        if (inq_unlikely (!(p))) {                                     \
            printf("inq_assert() condition failed: %s [%s, %s, %d]\n", \
                    #p, __func__, __FILE__, __LINE__);                 \
            abort();                                                   \
        }                                                              \
    } while (0)
#else
#   define inq_assert(p) ((void 0)
#endif


#define inq_require(p) do {                                           \
    if (inq_unlikely (!(p))) {                                        \
        printf("inq_require() condition failed @ %s() [%s:%d]: %s\n", \
                __func__, __FILE__, __LINE__, #p);                    \
        exit(EXIT_FAILURE);                                           \
    }                                                                 \
} while (0)


#endif /* INQUERY_CORE_HEADER_INCLUDED */

