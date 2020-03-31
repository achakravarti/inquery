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


extern inquery_attribute *inquery_attribute_new(const inquery_string *key, 
         const inquery_value *val)
{
    struct inquery_object_vtable vt = {
            .payload_copy = &payload_copy,
            .payload_free = &payload_free
    };

    return inquery_object_new(payload_new(key, val), &vt);
}


extern inline inquery_attribute *inquery_attribute_new_nil(
        const inquery_string *key);


extern inline inquery_attribute *inquery_attribute_new_int(
        const inquery_string *key, int64_t val);


extern inline inquery_attribute *inquery_attribute_new_real(
        const inquery_string *key, double val);


extern inline inquery_attribute *inquery_attribute_new_text(
        const inquery_string *key, inquery_string *val);


extern inline inquery_attribute *inquery_attribute_copy(
        const inquery_attribute *ctx);


extern inline void inquery_attribute_free(inquery_attribute **ctx);


extern inquery_string *inquery_attribute_key(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_string_copy(payload->key);
}


extern inquery_value *inquery_attribute_value(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_copy(payload->val);
}


extern enum inquery_value_type inquery_attribute_type(
        const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_type(payload->val);
}


extern int inquery_attribute_cmp(const inquery_attribute *ctx,
        const inquery_attribute *cmp)
{
    inquery_assert (ctx && cmp);
    inquery_assert (inquery_attribute_type(ctx) && inquery_attribute_type(cmp));
    inquery_assert (inquery_attribute_type(ctx) == inquery_attribute_type(cmp));

    const struct payload *ctxl = inquery_object_payload(ctx);
    const struct payload *cmpl = inquery_object_payload(cmp);
    inquery_assert (inquery_string_eq(ctxl->key, cmpl->key));

    return inquery_value_cmp(ctxl->val, cmpl->val);
}


extern inline bool inquery_attribute_lt(const inquery_attribute *ctx, 
        const inquery_attribute *cmp);


extern inline bool inquery_attribute_lteq(const inquery_attribute *ctx,
        const inquery_attribute *cmp);


extern inline bool inquery_attribute_eq(const inquery_attribute *ctx,
        const inquery_attribute *cmp);


extern inline bool inquery_attribute_gteq(const inquery_attribute *ctx,
        const inquery_attribute *cmp);


extern inline bool inquery_attribute_gt(const inquery_attribute *ctx,
        const inquery_attribute *cmp);


extern bool inquery_attribute_nil(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_nil(payload->val);
}


extern int64_t inquery_attribute_int(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_int(payload->val);
}


extern double inquery_attribute_real(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_real(payload->val);
}


extern inquery_string *inquery_attribute_text(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);
    return inquery_value_text(payload->val);
}


extern inquery_string *inquery_attribute_string(const inquery_attribute *ctx)
{
    const struct payload *payload = inquery_object_payload(ctx);

    inquery_string *str = inquery_string_new(payload->key);
    inquery_string_add(&str, " = ");
    
    inquery_string_smart *val = inquery_value_string(payload->val);
    inquery_string_add(&str, val);

    return str;
}


extern inquery_string *inquery_attribute_json(const inquery_attribute *ctx)
{
    inquery_assert (ctx);

    const struct payload *payload = inquery_object_payload(ctx);

    inquery_string *json = inquery_string_new("\"");
    inquery_string_add(&json, payload->key);
    inquery_string_add(&json, "\":");

    switch (inquery_value_type(payload->val)) {
        case INQUERY_VALUE_TYPE_INT: {
            inquery_string_smart *str = inquery_value_string(payload->val);
            inquery_string_add(&json, str);
        } break;

        case INQUERY_VALUE_TYPE_REAL: {
            inquery_string_smart *str = inquery_value_string(payload->val);
            inquery_string_add(&json, str);
        } break;

        default: {
            inquery_string_smart *str = inquery_value_string(payload->val);
            inquery_string_add(&json, "\"");
            inquery_string_add(&json, str);
            inquery_string_add(&json, "\"");
        } break;
    }

    return json;
}

