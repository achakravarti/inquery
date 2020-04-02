#include "core.h"


/*
 * struct payload - object payload for record instance
 */
struct payload {
    inquery_field **fld;
    size_t len;
};


/*
 * payload_new() - create new record payload
 */
static struct payload *payload_new(const inquery_field **fld, size_t len)
{
    struct payload *ctx = inquery_heap_new(sizeof *ctx);
    ctx->len = len;

    size_t sz = sizeof *fld * len;
    ctx->fld = inquery_heap_new(sz);
   
    for (register size_t i = 0; i < len; i++)
        ctx->fld[i] = inquery_field_copy(fld[i]);

    return ctx;
}


/*
 * payload_copy() - copy callback for record object v-table
 */
static void *payload_copy(const void *ctx)
{
    const struct payload *src = (const struct payload *) ctx;
    return payload_new((const inquery_field **) src->fld, src->len);
}


/*
 * payload_free() - free callback for record object v-table
 */
static void payload_free(void *ctx)
{
    struct payload *hnd = (struct payload *) ctx;

    for (register size_t i = 0; i < hnd->len; i++)
        inquery_field_free(&hnd->fld[i]);

    inquery_heap_free((void **) &hnd->fld);
}


/*
 * inquery_record_new() - create new record
 */
extern inquery_record *inquery_record_new(const inquery_field **fld,
        size_t len)
{
    struct inquery_object_vtable vt = {
        .payload_copy = &payload_copy,
        .payload_free = &payload_free
    };

    inquery_assert (fld && *fld && len);
    return inquery_object_new(payload_new(fld, len), &vt);
}


/*
 * inquery_record_copy() - copy existing record
 */
extern inline inquery_record *inquery_record_copy(const inquery_record *ctx);


/*
 * inquery_record_free() - free existing record
 */
extern inline void inquery_record_free(inquery_record **ctx);


/*
 * inquery_record_len() - get record length
 */
extern size_t inquery_record_len(const inquery_record *ctx)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);
    return payload->len;
}


/*
 * inquery_record_get() - get record field
 */
extern inquery_field *inquery_record_get(const inquery_record *ctx,
        size_t col)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);

    inquery_assert (col && col <= payload->len);
    return inquery_field_copy(payload->fld[col - 1]);
}


/*
 * inquery_record_set() - set record field
 */
extern void inquery_record_set(inquery_record **ctx, size_t col,
        const inquery_field *val)
{
    inquery_assert (ctx && *ctx);
    struct payload *payload = inquery_object_payload_mutable(ctx);

    inquery_assert (col && col <= payload->len && val);
    inquery_field_free(&payload->fld[--col]);
    payload->fld[col] = inquery_field_copy(val);
}


/*
 * inquery_record_json() - represent record as JSON
 */
extern inquery_string *inquery_record_json(const inquery_record *ctx)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);

    inquery_string *json = inquery_string_new("{");
    inquery_string *fldjson;

    if (inquery_likely (payload->len)) {
        register size_t i = 0, end = payload->len - 1;
        for (; i < end; i++) {
            fldjson = inquery_field_json(payload->fld[i]);
            inquery_string_add(&json, fldjson);
            inquery_string_add(&json, ",");
            inquery_string_free(&fldjson);
        }

        fldjson = inquery_field_json(payload->fld[end]);
        inquery_string_add(&json, fldjson);
        inquery_string_free(&fldjson);
    }

    inquery_string_add(&json, "}");
    return json;
}

