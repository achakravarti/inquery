#include <string.h>
#include <inttypes.h>
#include "core.h"


struct payload {
    inquery_string *key;
    inquery_value *val;
};


static struct payload *payload_new(const inquery_string *key, 
        const inquery_value *val)
{
    struct payload *ctx = inquery_heap_new(sizeof *ctx);

    ctx->key = inquery_string_copy(key);
    ctx->val = inquery_value_copy(val);

    return ctx;
}


static void *payload_copy(const void *ctx)
{
    const struct payload *src = (const struct payload *) ctx;
    return payload_new(src->key, src->val);
}


static void payload_free(void *ctx)
{
    struct payload *hnd = (struct payload *) ctx;
    inquery_string_free(&hnd->key);
    inquery_value_free(&hnd->val);
}


static inquery_string *from_int(int64_t val)
{
    size_t len = snprintf(NULL, 0, "%"PRId64, val) + 1;
    inquery_string *str = inquery_heap_new(sizeof *str * len);
    (void) snprintf(str, len, "%"PRId64, val);

    return str;
}


static inquery_string *from_real(double val)
{
    size_t len = snprintf(NULL, 0, "%lf", val) + 1;
    inquery_string *str = inquery_heap_new(sizeof *str * len);
    snprintf(str, len, "%lf", val);

    return str;
}


extern inquery_attribute *inquery_attribute_new(const inquery_string *key, 
         const inquery_value *val)
{
    struct inquery_object_vtable vt = {
            .payload_copy = &payload_copy,
            .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(key, val), &vt);
}


extern inline inquery_attribute *inquery_attribute_copy(
        const inquery_attribute *ctx);


extern inline void inquery_attribute_free(inquery_attribute **ctx);


inquery_string *inquery_attribute_key(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_string_copy(payload->key);
}


inquery_value *inquery_attribute_value(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_copy(payload->val);
}


bool inquery_attribute_nil(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_nil(payload->val);
}

enum inquery_value_type inquery_attribute_type(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_type(payload->val);
}


inquery_string *inquery_attribute_json(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);

    inquery_string *json = inquery_string_new("\"");
    inquery_string_add(&json, payload->key);
    inquery_string_add(&json, "\":");

    switch (inquery_value_type(payload->val)) {
        case INQUERY_VALUE_TYPE_NIL: {
            inquery_string_add(&json, "(nil)");
        } break;

        case INQUERY_VALUE_TYPE_INT: {
            inquery_string_smart *str = from_int(inquery_value_int(
                    payload->val));
            inquery_string_add(&json, str);
        } break;

        case INQUERY_VALUE_TYPE_REAL: {
            inquery_string_smart *str = from_real(inquery_value_real(
                    payload->val));
            inquery_string_add(&json, str);
        } break;

        default: {
            inquery_string_add(&json, inquery_value_text(payload->val));
        } break;
    }

    return json;
}

