#include "../lib/core/core.h"
#include "suite.h"


/*
 * sample_int() - create sample integer field
 */
static inquery_field *sample_int(void)
{
    return inquery_field_new_int("int", 555);
}


/*
 * sample_real() - create sample real field
 */
static inquery_field *sample_real(void)
{
    return inquery_field_new_real("real", -666.66);
}


/*
 * sample_text() - create sample text field
 */
static inquery_field *sample_text(void)
{
    return inquery_field_new_text("text", "test");
}


/*
 * new_1() - test case #1 for inquery_record_new()
 */
static void new_1(void)
{
    printf("inquery_record new() creates a new record");

    inquery_field_smart *ifld = sample_int();
    inquery_field_smart *rfld = sample_real();
    inquery_field_smart *tfld = sample_text();

    const inquery_field *fld[] = {
        ifld,
        rfld,
        tfld
    };

    size_t len = sizeof fld / sizeof *fld;
    inquery_record_smart *rec = inquery_record_new(fld, len);
    inquery_require (inquery_record_len(rec) == len);

    inquery_field_smart *fld1 = inquery_record_get(rec, 1);
    inquery_field_smart *fld2 = inquery_record_get(rec, 2);
    inquery_field_smart *fld3 = inquery_record_get(rec, 3);

    inquery_require (inquery_field_eq(fld1, ifld));
    inquery_require (inquery_field_eq(fld2, rfld));
    inquery_require (inquery_field_eq(fld3, tfld));

    printf("...OK\n");
}


/*
 * copy_1() - test case #1 for inquery_record_copy()
 */
static void copy_1(void)
{
    printf("inquery_record_copy() creates a copy of an existing record");

    inquery_field_smart *ifld = sample_int();
    inquery_field_smart *rfld = sample_real();
    inquery_field_smart *tfld = sample_text();

    const inquery_field *fld[] = {
        ifld,
        rfld,
        tfld
    };

    size_t len = sizeof fld / sizeof *fld;
    inquery_record_smart *ctx = inquery_record_new(fld, len);
    inquery_record_smart *cp = inquery_record_copy(ctx);
    inquery_require (inquery_record_len(cp) == len);

    inquery_field_smart *fld1 = inquery_record_get(cp, 1);
    inquery_field_smart *fld2 = inquery_record_get(cp, 2);
    inquery_field_smart *fld3 = inquery_record_get(cp, 3);

    inquery_require (inquery_field_eq(fld1, ifld));
    inquery_require (inquery_field_eq(fld2, rfld));
    inquery_require (inquery_field_eq(fld3, tfld));

    printf("...OK\n");
}


/*
 * set_1() - test case #1 for inquery_record_set()
 */
static void set_1(void)
{
    printf("inquery_record_set() updates a record field");

    inquery_field_smart *ifld = sample_int();
    inquery_field_smart *rfld = sample_real();
    inquery_field_smart *tfld = sample_text();

    const inquery_field *fld[] = {
        ifld,
        ifld,
        tfld
    };

    size_t len = sizeof fld / sizeof *fld;
    inquery_record_smart *ctx = inquery_record_new(fld, len);
    inquery_record_set(&ctx, 2, rfld);

    inquery_field_smart *fld1 = inquery_record_get(ctx, 1);
    inquery_field_smart *fld2 = inquery_record_get(ctx, 2);
    inquery_field_smart *fld3 = inquery_record_get(ctx, 3);

    inquery_require (inquery_field_eq(fld1, ifld));
    inquery_require (inquery_field_eq(fld2, rfld));
    inquery_require (inquery_field_eq(fld3, tfld));

    printf("...OK\n");
}


/*
 * json_1() - test case #1 for inquery_record_json()
 */
static void json_1(void)
{
    printf("inquery_record_json() correctly represents a record");

    inquery_field_smart *ifld = sample_int();
    inquery_field_smart *rfld = sample_real();
    inquery_field_smart *tfld = sample_text();

    const inquery_field *fld[] = {
        ifld,
        rfld,
        tfld
    };

    size_t len = sizeof fld / sizeof *fld;
    inquery_record_smart *ctx = inquery_record_new(fld, len);
    inquery_string_smart *json = inquery_record_json(ctx);

    inquery_require (inquery_string_eq (json,
            "{\"int\":555,\"real\":-666.660000,\"text\":\"test\"}"));

    printf("...OK\n");
}


/*
 * inquery_test_suite_record() - record interface test suite
 */
extern void inquery_test_suite_record(void)
{
    printf("===============================================================\n");
    printf("Starting record interface test suite...\n\n");

    new_1();
    copy_1();
    set_1();
    json_1();

    printf("\n");
}

