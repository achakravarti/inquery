/******************************************************************************
 *                     ___                                   
 *                    |_ _|_ __   __ _ _   _  ___ _ __ _   _ 
 *                     | || '_ \ / _` | | | |/ _ \ '__| | | |
 *                     | || | | | (_| | |_| |  __/ |  | |_| |
 *                    |___|_| |_|\__, |\__,_|\___|_|   \__, |
 *                                  |_|                |___/ 
 *
 * Inquery - India Query RESTful microservice
 * Copyright (c) 2020 Abhishek Chakravarti <abhishek@taranjali.org>. 
 * See the accompanying inquery/AUTHORS file for the full list of contributors.
 *
 * This is the inquery/lib/core.h header file; it declares the core interface
 * on which the Inquery microservice is built.
 *
 * This code is released under the GPLv3 License. See the accompanying 
 * inquery/LICENSE file or <http://opensource.org/licenses/GPL-3.0> for complete
 * licensing details.
 *
 * BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAT YOU
 * HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/


#if (!defined INQUERY_CORE_HEADER_INCLUDED)
#define INQUERY_CORE_HEADER_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*******************************************************************************
 * BRANCH PREDICTION
 */


/*
 * inq_likely() - hint that a predicate is likely to be true
 */
#if (defined __GNUC__ || defined __clang__)
#   define inq_likely(p) (__builtin_expect (!!(p), 1))
#else
#   define inq_likely(p) (p)
#   warning "inq_likely() has no effect on non GCC-compatible C compilers"
#endif


/*
 * inq_unlikely() - hint that a predicate is unlikely to be true
 */
#if (defined __GNUC__ || defined __clang__)
#   define inq_unlikely(p) (__builtin_expect (!!(p), 0))
#else
#   define inq_unlikely(p) (p)
#   warning "inq_likely() has no effect on non GCC-compatible C compilers"
#endif


/*******************************************************************************
 * RUNTIME CHECKS
 */


/*
 * inq_assert() - assert that a predicate is true
 */
#if !(defined NDEBUG)
#   define inq_assert(p) do {                                          \
        if (inq_unlikely (!(p))) {                                     \
            printf("inq_assert() condition failed: %s [%s, %s, %d]\n", \
                    #p, __func__, __FILE__, __LINE__);                 \
            abort();                                                   \
        }                                                              \
    } while (0)
#else
#   define inq_assert(p)
#endif


/*
 * inq_require() - ensure that a predicate is true
 */
#define inq_require(p) do {                                           \
    if (inq_unlikely (!(p))) {                                        \
        printf("inq_require() condition failed @ %s() [%s:%d]: %s\n", \
                __func__, __FILE__, __LINE__, #p);                    \
        exit(EXIT_FAILURE);                                           \
    }                                                                 \
} while (0)


/*******************************************************************************
 * HEAP MEMORY MANAGEMENT
 */


#define inq_heap_init()

#define inq_heap_exit()

extern void *inq_heap_new(size_t sz);

extern void inq_heap_resize(void **bfr, size_t sz);

extern void inq_heap_free(void **bfr);


#endif /* INQUERY_CORE_HEADER_INCLUDED */

