#include "core.h"


/*
 * struct payload - object payload for table instance
 */
struct payload {
    size_t len;
    inquery_record **rec;
};


/*
 * payload_new() - create new table object payload
 */
static struct payload *payload_new(size_t len, const inquery_record **rec)
{
    struct payload *ctx = inquery_heap_new(sizeof *ctx);
    ctx->len = len;

    size_t sz = sizeof *rec * len;
    ctx->rec = inquery_heap_new(sz);

    if (rec) {
        for (register size_t i = 0; i < len; i++)
            ctx->rec[i] = inquery_record_copy(rec[i]);
    }

    return ctx;
}


/*
 * payload_copy() - copy callback for table object v-table
 */
static void *payload_copy(const void *ctx)
{
    const struct payload *src = (const struct payload *) ctx;
    return payload_new(src->len, (const inquery_record **) src->rec);
}


/*
 * payload_free() - free callback for table object v-table
 */
static void payload_free(void *ctx)
{
    struct payload *hnd = (struct payload *) ctx;

    for (register size_t i = 0; i < hnd->len; i++)
        inquery_record_free(&hnd->rec[i]);

    inquery_heap_free((void **) &hnd->rec);
}


/*
 * vtable_init() - initialise table object v-table
 */
static inline void vtable_init(struct inquery_object_vtable *ctx)
{
    ctx->payload_copy = &payload_copy;
    ctx->payload_free = &payload_free;
}


/*
 * inquery_table_new() - create new table
 */
extern inquery_table *inquery_table_new(size_t len, const inquery_record **rec)
{
    struct inquery_object_vtable vt;
    vtable_init(&vt);

    inquery_assert (len && rec && *rec);
    return inquery_object_new(payload_new(len, rec), &vt);
}


/*
 * inquery_table_new() - create new empty table
 */
extern inquery_table *inquery_table_new_empty(size_t len)
{
    struct inquery_object_vtable vt;
    vtable_init(&vt);

    inquery_assert (len);
    return inquery_object_new(payload_new(len, NULL), &vt);
}


/*
 * inquery_table_copy() - copy existing table
 */
extern inline inquery_table *inquery_table_copy(const inquery_table *ctx);


/*
 * inquery_table_free() - free existing table
 */
extern inline void inquery_table_free(inquery_table **ctx);


/*
 * inquery_table_len() - get table length
 */
extern size_t inquery_table_len(const inquery_table *ctx)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);
    return payload->len;
}


/*
 * inquery_table_record() - get table record
 */
extern inquery_record *inquery_table_record(const inquery_table *ctx, 
        size_t row)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);

    inquery_assert (row && row <= payload->len);
    return inquery_record_copy(payload->rec[row - 1]);
}


/*
 * inquery_table_record_set() - set table record
 */
extern void inquery_table_record_set(inquery_table **ctx, size_t row, 
        const inquery_record *val)
{
    inquery_assert (ctx && *ctx);
    struct payload *payload = inquery_object_payload_mutable(ctx);

    inquery_assert (val && row && row <= payload->len);
    inquery_record_free(&payload->rec[--row]);
    payload->rec[row] = inquery_record_copy(val); 
}


/*
 * inquery_table_field() - get table field
 */
extern inquery_field *inquery_table_field(const inquery_table *ctx, size_t row,
        size_t col)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);

    inquery_assert (row && row <= payload->len);
    inquery_record *rec = payload->rec[row - 1];

    inquery_assert (col && col <= inquery_record_len(rec));
    return inquery_record_get(rec, col);
}


/*
 * inquery_table_field_set() - set table field
 */
extern void inquery_table_field_set(inquery_table **ctx, size_t row, size_t col,
        const inquery_field *val)
{
    inquery_assert (ctx && *ctx);
    struct payload *payload = inquery_object_payload_mutable(ctx);

    inquery_assert (row && row <= payload->len);
    inquery_record *rec = payload->rec[--row];

    inquery_assert (val && col && col <= inquery_record_len(rec));
    inquery_record_set(&rec, col, val);
}


/*
 * inquery_table_json() - represent table as JSON
 */
extern inquery_string *inquery_table_json(const inquery_table *ctx)
{
    inquery_assert (ctx);
    const struct payload *payload = inquery_object_payload(ctx);

    inquery_string *json = inquery_string_new("[");
    inquery_string *recjson;

    if (inquery_likely (payload->len)) {
        register size_t i = 0, end = payload->len - 1;
        for (; i < end; i++) {
            recjson = inquery_record_json(payload->rec[i]);
            inquery_string_add(&json, recjson);
            inquery_string_add(&json, ",");
            inquery_string_free(&recjson);
        }

        recjson = inquery_record_json(payload->rec[end]);
        inquery_string_add(&json, recjson);
        inquery_string_free(&recjson);
    }

    inquery_string_add(&json, "]");
    return json;
}

