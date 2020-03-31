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
#include <stdint.h>
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


/*
 * inquery_string - UTF-8 string
 */
typedef char inquery_string;


/*
 * inquery_string_smart - smart string pointer
 */
#if (defined __GNUC__ || defined __clang__)
#   define inquery_string_smart \
            __attribute__((cleanup(inquery_string_free))) inquery_string
#else
#   define inquery_string_smart inquery_string
#   warning "inquery_string_smart leaks memory on non GCC-compatible compilers"
#endif


/*
 * inquery_string_new() - create new string
 */
extern inquery_string *inquery_string_new(const char *cstr);


/*
 * inquery_string_new_empty() - create new empty string
 */
extern inquery_string *inquery_string_new_empty(void);


/*
 * inquery_string_copy() - copy existing string
 */
extern inquery_string *inquery_string_copy(const inquery_string *ctx);


/*
 * inquery_string_free() - release string
 */
extern void inquery_string_free(inquery_string **ctx);


/*
 * inquery_string_len() - get length of string
 */
extern size_t inquery_string_len(const inquery_string *ctx);


/*
 * inquery_string_sz() - get size of string
 */
extern size_t inquery_string_sz(const inquery_string *ctx);


/*
 * inquery_string_cmp() - compare two strings
 */
extern int inquery_string_cmp(const inquery_string *lhs, 
        const inquery_string *rhs);


/*
 * inquery_string_lt() - check if string is less than another
 */
inline bool inquery_string_lt(const inquery_string *lhs,
        const inquery_string *rhs)
{
    inquery_assert (lhs && rhs);

    return inquery_string_cmp(lhs, rhs) < 0;
}


/*
 * inquery_string_eq() - check if string is equal to another
 */
inline bool inquery_string_eq(const inquery_string *lhs,
        const inquery_string *rhs)
{
    inquery_assert (lhs && rhs);

    return !inquery_string_cmp(lhs, rhs);
}


/*
 * inquery_string_gt() - check if string is greater than another
 */
inline bool inquery_string_gt(const inquery_string *lhs,
        const inquery_string *rhs)
{
    inquery_assert (lhs && rhs);

    return inquery_string_cmp(lhs, rhs) > 0;
}


/*
 * inquery_string_add() - concatenate two strings
 */
extern void inquery_string_add(inquery_string **ctx, const inquery_string *add);


/*
 * inquery_string_find() - find first occurrence of substring
 */
extern size_t inquery_string_find(const inquery_string *ctx, 
        const inquery_string *what);


/*
 * inquery_string_count() - count all occurrences of substring
 */
extern size_t inquery_string_count(const inquery_string *ctx,
        const inquery_string *what);


/*
 * inquery_string_replace() - replace all occurrences of substring
 */
extern void inquery_string_replace(inquery_string **ctx, 
        const inquery_string *what, const inquery_string *with);


/*
 * inquery_string_replace_first() - replace first occurrenct of substring
 */
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


/*******************************************************************************
 * VALUE
 */


/*
 * inquery_value - boxed value
 */
typedef inquery_object inquery_value;


/*
 * inquery_value_smart - smart boxed value
 */
#define inquery_value_smart inquery_object_smart


/*
 * enum inquery_value_type - enumerated value types
 */
enum inquery_value_type {
    INQUERY_VALUE_TYPE_NIL,
    INQUERY_VALUE_TYPE_INT,
    INQUERY_VALUE_TYPE_REAL,
    INQUERY_VALUE_TYPE_TEXT
};


/*
 * inquery_value_new() - create new nil value
 */
extern inquery_value *inquery_value_new(void);


/*
 * inquery_value_new_int() - create new integer value
 */
extern inquery_value *inquery_value_new_int(int64_t val);


/*
 * inquery_value_new_real() - create new real value
 */
extern inquery_value *inquery_value_new_real(double val);


/*
 * inquery_value_new_text() - create new text value
 */
extern inquery_value *inquery_value_new_text(const inquery_string *val);


/*
 * inquery_value_copy() - create copy of existing value
 */
inline inquery_value *inquery_value_copy(const inquery_value *ctx)
{
    return inquery_object_copy(ctx);
}


/*
 * inquery_value_free() - free value from heap
 */
inline void inquery_value_free(inquery_value **ctx)
{
    inquery_object_free(ctx);
}


/*
 * inquery_value_type() - get value type
 */
extern enum inquery_value_type inquery_value_type(const inquery_value *ctx);


/*
 * inquery_value_cmp() - comnpare two values
 */
extern int inquery_value_cmp(const inquery_value *ctx, 
        const inquery_value *cmp);


/*
 * inquery_value_lt() - check if value is less than another
 */
inline bool inquery_value_lt(const inquery_value *ctx, 
        const inquery_value *cmp)
{
    return inquery_value_cmp(ctx, cmp) < 0;
}


/*
 * inquery_value_lteq() - check if value is less than or equal to another
 */
inline bool inquery_value_lteq(const inquery_value *ctx,
        const inquery_value *cmp)
{
    return inquery_value_cmp(ctx, cmp) <= 0;
}


/*
 * inquery_value_eq() - check if value is equal to another
 */
inline bool inquery_value_eq(const inquery_value *ctx,
        const inquery_value *cmp)
{
    return !inquery_value_cmp(ctx, cmp);
}


/*
 * inquery_value_gteq() - check if value is greater than or equal to another
 */
inline bool inquery_value_gteq(const inquery_value *ctx,
        const inquery_value *cmp)
{
    return inquery_value_cmp(ctx, cmp) >= 0;
}


/*
 * inquery_value_gt() - check if value is greater than another
 */
inline bool inquery_value_gt(const inquery_value *ctx,
        const inquery_value *cmp)
{
    return inquery_value_cmp(ctx, cmp) > 0;
}


/*
 * inquery_value_nil() - check if value is nil
 */
extern bool inquery_value_nil(const inquery_value *ctx);


/*
 * inquery_value_int() - unbox integer value
 */
extern int64_t inquery_value_int(const inquery_value *ctx);


/*
 * inquery_value_real() - unbox real value
 */
extern double inquery_value_real(const inquery_value *ctx);


/*
 * inquery_value_text() - unbox text value
 */
extern inquery_string *inquery_value_text(const inquery_value *ctx);


/*
 * inquery_value_string() - get string representation of value
 */
extern inquery_string *inquery_value_string(const inquery_value *ctx);


/*******************************************************************************
 * ATTRIBUTE
 */


typedef inquery_object inquery_attribute;

#define inquery_attribute_smart inquery_object_smart

extern inquery_attribute *inquery_attribute_new(const inquery_string *key, 
         const inquery_value *val);

inline inquery_attribute *inquery_attribute_new_nil(const inquery_string *key)
{
    inquery_value_smart *val = inquery_value_new();
    return inquery_attribute_new(key, val);
}

inline inquery_attribute *inquery_attribute_new_int(const inquery_string *key,
        int64_t val)
{
    inquery_value_smart *v = inquery_value_new_int(val);
    return inquery_attribute_new(key, v);
}

inline inquery_attribute *inquery_attribute_new_real(const inquery_string *key,
        double val)
{
    inquery_value_smart *v = inquery_value_new_real(val);
    return inquery_attribute_new(key, v);
}

inline inquery_attribute *inquery_attribute_new_text(const inquery_string *key,
        inquery_string *val)
{
    inquery_value_smart *v = inquery_value_new_text(val);
    return inquery_attribute_new(key, v);
}

inline inquery_attribute *inquery_attribute_copy(const inquery_attribute *ctx)
{
    return inquery_object_copy(ctx);
}

inline void inquery_attribute_free(inquery_attribute **ctx)
{
    inquery_object_free(ctx);
}

extern inquery_string *inquery_attribute_key(const inquery_attribute *ctx);

extern inquery_value *inquery_attribute_value(const inquery_attribute *ctx);

extern enum inquery_value_type inquery_attribute_type(
        const inquery_attribute *ctx);

extern int inquery_attribute_cmp(const inquery_attribute *ctx,
        const inquery_attribute *cmp);

inline bool inquery_attribute_lt(const inquery_attribute *ctx, 
        const inquery_attribute *cmp)
{
    return inquery_attribute_cmp(ctx, cmp) < 0;
}

inline bool inquery_attribute_lteq(const inquery_attribute *ctx,
        const inquery_attribute *cmp)
{
    return inquery_attribute_cmp(ctx, cmp) <= 0;
}

inline bool inquery_attribute_eq(const inquery_attribute *ctx,
        const inquery_attribute *cmp)
{
    return !inquery_attribute_cmp(ctx, cmp);
}

inline bool inquery_attribute_gteq(const inquery_attribute *ctx,
        const inquery_attribute *cmp)
{
    return inquery_value_cmp(ctx, cmp) >= 0;
}

inline bool inquery_attribute_gt(const inquery_attribute *ctx,
        const inquery_attribute *cmp)
{
    return inquery_attribute_cmp(ctx, cmp) > 0;
}

extern bool inquery_attribute_nil(const inquery_attribute *ctx);

extern int64_t inquery_attribute_int(const inquery_attribute *ctx);

extern double inquery_attribute_real(const inquery_attribute *ctx);

extern inquery_string *inquery_attribute_text(const inquery_attribute *ctx);

extern inquery_string *inquery_attribute_string(const inquery_attribute *ctx);

extern inquery_string *inquery_attribute_json(const inquery_attribute *ctx);


#endif /* INQUERY_CORE_HEADER_INCLUDED */

