#include <string.h>
#include "core.h"


struct payload {
    enum inquery_value_type type;
    size_t size;
    void *value;
};


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


static void *payload_copy(const void *ctx)
{
    const struct payload *src = (const struct payload *) ctx;
    return payload_new(src->type, src->size, src->value);
}


static void payload_free(void *ctx)
{
    struct payload *hnd = (struct payload *) ctx;
    inquery_heap_free(&hnd->value);
}


extern inquery_value *inquery_value_new_int(uint64_t val)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_INT, 
            sizeof (uint64_t), &val), &vt);
}


extern inquery_value *inquery_value_new_int_nil(void)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_INT, 
            sizeof (uint64_t), NULL), &vt);
}


extern inquery_value *inquery_value_new_real(double val)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_REAL, 
            sizeof (double), &val), &vt);
}


extern inquery_value *inquery_value_new_real_nil(void)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_REAL, 
            sizeof (double), NULL), &vt);
}


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


extern inquery_value *inquery_value_new_text_nil(void)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(INQUERY_VALUE_TYPE_TEXT, 0, NULL),
            &vt);
}


extern inline inquery_value *inquery_value_copy(const inquery_value *ctx);


extern inline void inquery_value_free(inquery_value **ctx);


extern bool inquery_value_nil(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return !payload->value;
}


extern enum inquery_value_type inquery_value_type(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return payload->type;
}


extern uint64_t inquery_value_int(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    inquery_assert (payload->type == INQUERY_VALUE_TYPE_INT);

    return *((uint64_t *) payload->value);
}


extern double inquery_value_real(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    inquery_assert (payload->type == INQUERY_VALUE_TYPE_REAL);

    return *((double *) payload->value);
}


extern inquery_string *inquery_value_text(const inquery_value *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    inquery_assert (payload->type == INQUERY_VALUE_TYPE_TEXT);

    return inquery_string_copy((inquery_string *) payload->value);
}

