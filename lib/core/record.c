#include <string.h>
#include "core.h"


struct payload {
    inquery_attribute **attr;
    size_t len;
};


static struct payload *payload_new(const inquery_attribute **attr, size_t len)
{
    size_t sz = sizeof *attr * len;
    struct payload *ctx = inquery_heap_new(sz);

    ctx->len = len;
    memcpy(ctx->attr, attr, sz);

    return ctx;
}


static void *payload_copy(const void *ctx)
{
    const struct payload *src = (const struct payload *) ctx;
    return payload_new((const inquery_attribute **) src->attr, src->len);
}


static void payload_free(void *ctx)
{
    struct payload *hnd = (struct payload *) ctx;

    for (register size_t i = 0; i < hnd->len; i++)
        inquery_attribute_free(&hnd->attr[i]);

    inquery_heap_free((void **) hnd->attr);
}


extern inquery_record *inquery_record_new(const inquery_attribute **attr,
        size_t len)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    inquery_assert (attr && *attr && len);
    return inquery_object_new(payload_new(attr, len), &vt);
}


extern inline inquery_record *inquery_record_copy(const inquery_record *ctx);


extern inline void inquery_record_free(inquery_record **ctx);


extern inquery_attribute *inquery_record_get(const inquery_record *ctx,
        size_t col)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);

    inquery_assert (col && col <= payload->len);
    return inquery_attribute_copy(payload->attr[col - 1]);
}


extern void inquery_record_set(inquery_record **ctx, size_t col,
        const inquery_attribute *val)
{
    inquery_assert (ctx && *ctx);
    struct payload *payload = inquery_object_payload_mutable(ctx);

    inquery_assert (col && col <= payload->len && val);
    payload->attr[col - 1]  = inquery_attribute_copy(val);
}


extern size_t inquery_record_len(const inquery_record *ctx)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);
    return payload->len;
}


extern inquery_string *inquery_record_json(const inquery_record *ctx)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);

    inquery_string *json = inquery_string_new("{");

    if (inquery_likely (payload->len)) {
        register size_t i = 0, end = payload->len - 1;
        for (; i < end; i++) {
            inquery_string_add(&json, inquery_attribute_json(payload->attr[i]));
            inquery_string_add(&json, ",");
        }

        inquery_string_add(&json, inquery_attribute_json(payload->attr[end]));
    }

    inquery_string_add(&json, "}");
    return json;
}

