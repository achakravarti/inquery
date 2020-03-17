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


#include <stdbool.h>
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
 * STRING
 */

typedef char inquery_string;

#if (defined __GNUC__ || defined __clang__)
#   define inquery_string_smart \
            __attribute__((cleanup(inquery_string_free))) inquery_string
#else
#   define inquery_string_smart inquery_string
#   warning "inquery_string_smart leaks memory on non GCC-compatible compilers"
#endif

extern inquery_string *inquery_string_new(const char *cstr);

extern inquery_string *inquery_string_new_empty(void);

extern inquery_string *inquery_string_copy(const inquery_string *ctx);

extern void inquery_string_free(inquery_string **ctx);

extern size_t inquery_string_len(const inquery_string *ctx);

extern size_t inquery_string_sz(const inquery_string *ctx);

extern int inquery_string_cmp(const inquery_string *lhs, 
        const inquery_string *rhs);

inline bool inquery_string_lt(const inquery_string *lhs,
        const inquery_string *rhs)
{
    inquery_assert (lhs && rhs);

    return inquery_string_cmp(lhs, rhs) < 0;
}

inline bool inquery_string_eq(const inquery_string *lhs,
        const inquery_string *rhs)
{
    inquery_assert (lhs && rhs);

    return !inquery_string_cmp(lhs, rhs);
}

inline bool inquery_string_gt(const inquery_string *lhs,
        const inquery_string *rhs)
{
    inquery_assert (lhs && rhs);

    return inquery_string_cmp(lhs, rhs) > 0;
}

extern void inquery_string_add(inquery_string **ctx, const inquery_string *add);

extern size_t inquery_string_find(const inquery_string *ctx, 
        const inquery_string *what);

extern void inquery_string_replace(inquery_string **ctx, 
        const inquery_string *what, const inquery_string *with);

extern void inquery_string_replace_first(inquery_string **ctx, 
        const inquery_string *what, const inquery_string *with);


/*******************************************************************************
 * OBJECT MODEL
 */


/*
 * inquery_object - reference counted object
 */
typedef struct inquery_object inquery_object;


/*
 * struct inquery_object_vtable - object payload v-table
 */
struct inquery_object_vtable {
    void *(*payload_copy)(const void *payload);
    void (*payload_free)(void *payload);
};


/*
 * inquery_object_smart - declare smart pointer to object
 */
#if (defined __GNUC__ || defined __clang__)
#   define inquery_object_smart \
            __attribute__((cleanup(inquery_object_free))) inquery_object
#else
#   define inquery_object_smart inquery_object
#   warning "inquery_object_smart leaks memory on non GCC-compatible compilers"
#endif


/*
 * inquery_object_new() - create new object
 */
extern inquery_object *inquery_object_new(void *payload,
        const struct inquery_object_vtable *vt);


/*
 * inquery_object_new_noload() - create new object without payload
 */
extern inquery_object *inquery_object_new_noload(void);


/*
 * inquery_object_copy() - copy existing object
 */
extern inquery_object *inquery_object_copy(const inquery_object *ctx);


/*
 * inquery_object_free() - free object from heap memory
 */
extern void inquery_object_free(inquery_object **ctx);


/*
 * inquery_object_payload() - get constant handle to object payload
 */
extern const void *inquery_object_payload(const inquery_object *ctx);


/*
 * inquery_object_payload_mutable() - get mutable handle to object payload
 */
extern void *inquery_object_payload_mutable(inquery_object **ctx);


#endif /* INQUERY_CORE_HEADER_INCLUDED */

