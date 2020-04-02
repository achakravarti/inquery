#include "core.h"


struct payload {
    size_t len;
    inquery_record **rec;
};


/*
 * inquery_table_new() - create new table
 */
extern inquery_table *inquery_table_new(size_t len, const inquery_record **rec)
{
}


/*
 * inquery_table_new() - create new empty table
 */
extern inquery_table *inquery_table_new_empty(size_t len)
{
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
}

