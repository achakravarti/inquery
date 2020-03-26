#include <float.h>
#include <math.h>
#include <string.h>
#include "core.h"


/*
 * struct payload - object payload for value instance
 */
struct payload {
    enum inquery_value_type type;
    size_t size;
    void *value;
};


/*
 * payload_new() - create new payload for value instance
 */
static struct payload *payload_new(enum inquery_value_type type, size_t sz,
        const void *val)
{
    struct payload *ctx = inquery_heap_new(sizeof *ctx);

    ctx->type = type;
    ctx->size = sz;

    if (inquery_likely (val)) {
        ctx->value = inquery_heap_new(sz);
        memcpy(ctx->value, val, sz);
    } else
        ctx->value = NULL;

    return ctx;
}


/*
 * payload_copy() - copy callback function for value v-table
 */
static void *payload_copy(const void *ctx)
{
    const struct payload *src = (const struct payload *) ctx;
    return payload_new(src->type, src->size, src->value);
}


/*
 * payload_free() - free callback function for value v-table
 */
static void payload_free(void *ctx)
{
    struct payload *hnd = (struct payload *) ctx;
    inquery_heap_free(&hnd->value);
}


/*
 * vtable_init() - initialise payload v-table
 */
static void vtable_init(struct inquery_object_vtable *ctx)
{
    ctx->payload_copy = &payload_copy;
    ctx->payload_free = &payload_free;
}


/*
 * cmp_int() - compare two integer values
 */
static inline int cmp_int(int64_t lhs, int64_t rhs)
{
    if (lhs == rhs)
        return 0;

    if (lhs < rhs)
        return -1;

    return 1;
}


/*
 * cmp_real() - compare two real values
 */
static inline int cmp_real(double a, double b)
{
    /* https://stackoverflow.com/questions/17333 */

    if (fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON))
        return 0;

    if ((b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON))
        return -1;

    return 1;
}


/*
 * inquery_value_nil() - check if value is nil
 */
extern inquery_value *inquery_value_new(void)
{
    struct inquery_object_vtable vt;
    vtable_init(&vt);

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_NIL, 0, NULL), 
                &vt);
}


/*
 * inquery_value_new_int() - create new integer value
 */
extern inquery_value *inquery_value_new_int(int64_t val)
{
    struct inquery_object_vtable vt;
    vtable_init(&vt);

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_INT, 
            sizeof (int64_t), &val), &vt);
}


/*
 * inquery_value_new_real() - create new real value
 */
extern inquery_value *inquery_value_new_real(double val)
{
    struct inquery_object_vtable vt;
    vtable_init(&vt);

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_REAL, 
            sizeof (double), &val), &vt);
}


/*
 * inquery_value_new_text() - create new text value
 */
extern inquery_value *inquery_value_new_text(const inquery_string *val)
{
    inquery_assert (val);

    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_TEXT, 
            inquery_string_sz(val), val), &vt);
}


/*
 * inquery_value_copy() - create copy of existing value
 */
extern inline inquery_value *inquery_value_copy(const inquery_value *ctx);


/*
 * inquery_value_free() - free value from heap
 */
extern inline void inquery_value_free(inquery_value **ctx);


/*
 * inquery_value_type() - get value type
 */
extern enum inquery_value_type inquery_value_type(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return payload->type;
}


/*
 * inquery_value_cmp() - comnpare two values
 */
extern int inquery_value_cmp(const inquery_value *ctx, 
        const inquery_value *cmp)
{
    inquery_assert (ctx && cmp);
    inquery_assert (inquery_value_type(ctx) && inquery_value_type(cmp));
    inquery_assert (inquery_value_type(ctx) == inquery_value_type(cmp));

    const struct payload *ctxl = inquery_object_payload(ctx);
    const struct payload *cmpl = inquery_object_payload(cmp);

    if (ctxl->type == INQUERY_VALUE_TYPE_INT)
        return cmp_int(*((int64_t *) ctxl->value), *((int64_t *) cmpl->value));

    if (ctxl->type == INQUERY_VALUE_TYPE_TEXT) {
        return inquery_string_cmp((inquery_string *) ctxl->value,
                (inquery_string *) cmpl->value);
    }

    return cmp_real(*((double *) ctxl->value), *((double *) cmpl->value));
}


/*
 * inquery_value_lt() - check if value is less than another
 */
extern inline bool inquery_value_lt(const inquery_value *ctx, 
        const inquery_value *cmp);


/*
 * inquery_value_lteq() - check if value is less than or equal to another
 */
extern inline bool inquery_value_lteq(const inquery_value *ctx,
        const inquery_value *cmp);


/*
 * inquery_value_eq() - check if value is equal to another
 */
extern inline bool inquery_value_eq(const inquery_value *ctx,
        const inquery_value *cmp);


/*
 * inquery_value_gteq() - check if value is greater than or equal to another
 */
extern inline bool inquery_value_gteq(const inquery_value *ctx,
        const inquery_value *cmp);


/*
 * inquery_value_gt() - check if value is greater than another
 */
extern inline bool inquery_value_gt(const inquery_value *ctx,
        const inquery_value *cmp);


/*
 * inquery_value_nil() - check if value is nil
 */
extern bool inquery_value_nil(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return !payload->value;
}


/*
 * inquery_value_int() - unbox integer value
 */
extern int64_t inquery_value_int(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    inquery_assert (payload->type == INQUERY_VALUE_TYPE_INT);

    return *((int64_t *) payload->value);
}


/*
 * inquery_value_real() - unbox real value
 */
extern double inquery_value_real(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    inquery_assert (payload->type == INQUERY_VALUE_TYPE_REAL);

    return *((double *) payload->value);
}


/*
 * inquery_value_text() - unbox text value
 */
extern inquery_string *inquery_value_text(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    inquery_assert (payload->type == INQUERY_VALUE_TYPE_TEXT);

    return inquery_string_copy((inquery_string *) payload->value);
}

