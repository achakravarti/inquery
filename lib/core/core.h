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
 * inquery_likely() - hint that a predicate is likely to be true
 */
#if (defined __GNUC__ || defined __clang__)
#   define inquery_likely(p) (__builtin_expect (!!(p), 1))
#else
#   define inquery_likely(p) (p)
#   warning "inquery_likely() has no effect on non GCC-compatible compilers"
#endif


/*
 * inquery_unlikely() - hint that a predicate is unlikely to be true
 */
#if (defined __GNUC__ || defined __clang__)
#   define inquery_unlikely(p) (__builtin_expect (!!(p), 0))
#else
#   define inquery_unlikely(p) (p)
#   warning "inquery_likely() has no effect on non GCC-compatible compilers"
#endif


/*******************************************************************************
 * RUNTIME CHECKS
 */


/*
 * inquery_assert() - assert that a predicate is true
 */
#if !(defined NDEBUG)
#   define inquery_assert(p) do {                                          \
        if (inquery_unlikely (!(p))) {                                     \
            printf("inquery_assert() condition failed: %s [%s, %s, %d]\n", \
                    #p, __func__, __FILE__, __LINE__);                     \
            abort();                                                       \
        }                                                                  \
    } while (0)
#else
#   define inquery_assert(p)
#endif


/*
 * inquery_require() - ensure that a predicate is true
 */
#define inquery_require(p) do {                                           \
    if (inquery_unlikely (!(p))) {                                        \
        printf("inquery_require() condition failed @ %s() [%s:%d]: %s\n", \
                __func__, __FILE__, __LINE__, #p);                        \
        exit(EXIT_FAILURE);                                               \
    }                                                                     \
} while (0)


/*******************************************************************************
 * HEAP MEMORY MANAGEMENT
 */

/*
 * inquery_heap_init() - initialise heap memory manager
 */
#define inquery_heap_init()


/*
 * inquery_heap_exit() - shut down heap memory manager
 */
#define inquery_heap_exit()


/*
 * inquery_heap_new() - allocate new block of heap memory
 */
extern void *inquery_heap_new(size_t sz);


/*
 * inquery_heap_resize() - resize existing block of heap memory
 */
extern void inquery_heap_resize(void **bfr, size_t sz);


/*
 * inquery_heap_free() - free existing block of heap memory
 */
extern void inquery_heap_free(void **bfr);


/*******************************************************************************
 * OBJECT MODEL
 */


typedef struct inquery_object inquery_object;


struct inquery_object_vtable {
    void *(*payload_copy)(const void *payload);
    void (*payload_free)(void **payload);
};


#if (defined __GNUC__ || defined __clang__)
#   define inquery_object_smart __attribute__((cleanup(inquery_object_free)))
#else
#   define inquery_object_smart
#   warning "inquery_object_smart has no effect on non GCC-compatible compilers"
#endif


extern inquery_object *inquery_object_new(size_t id, void *payload,
        const struct inquery_object_vtable *vt);

extern inquery_object *inquery_object_copy(const inquery_object *ctx);

extern void inquery_object_free(inquery_object **ctx);

extern const void *inquery_object_payload(const inquery_object *ctx);

extern void *inquery_object_payload_mutable(inquery_object **ctx);


#endif /* INQUERY_CORE_HEADER_INCLUDED */

