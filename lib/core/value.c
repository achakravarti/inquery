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
    } else {
        ctx->value = NULL;
    };

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
 * inquery_value_new_int() - create new integer value
 */
extern inquery_value *inquery_value_new_int(int64_t val)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_INT, 
            sizeof (int64_t), &val), &vt);
}


/*
 * inquery_value_new_int_nil() - create new nil integer value
 */
extern inquery_value *inquery_value_new_int_nil(void)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_INT, 
            sizeof (int64_t), NULL), &vt);
}


/*
 * inquery_value_new_real() - create new real value
 */
extern inquery_value *inquery_value_new_real(double val)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_REAL, 
            sizeof (double), &val), &vt);
}


/*
 * inquery_value_new_real_nil() - create new nil real value
 */
extern inquery_value *inquery_value_new_real_nil(void)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_REAL, 
            sizeof (double), NULL), &vt);
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
 * inquery_value_new_text_nil() - create new nil text value
 */
extern inquery_value *inquery_value_new_text_nil(void)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_TEXT, 0, NULL),
            &vt);
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
 * inquery_value_nil() - check if value is nil
 */
extern bool inquery_value_nil(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return !payload->value;
}


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
 * inquery_value_string() - unbox string value
 */
extern inquery_string *inquery_value_text(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    inquery_assert (payload->type == INQUERY_VALUE_TYPE_TEXT);

    return inquery_string_copy((inquery_string *) payload->value);
}

