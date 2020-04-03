#include "../lib/core/core.h"
#include "suite.h"


static inquery_record *sample_record(void)
{
    inquery_field_smart *ifld = inquery_field_new_int("int", 555);
    inquery_field_smart *rfld = inquery_field_new_real("real", -666.66);
    inquery_field_smart *tfld = inquery_field_new_text("text", "Hello, world!");

    const inquery_field *fld[] = {
        ifld, rfld, tfld
    };

    return inquery_record_new(fld, sizeof fld / sizeof *fld);
}


static void new_1(void)
{
    printf("inquery_table_new() creates a new table");

    inquery_record_smart *r1 = sample_record();
    inquery_record_smart *r2 = sample_record();

    const inquery_record *rec[] = {
        r1, r2
    };

    inquery_table_smart *ctx = inquery_table_new(2, rec);
    inquery_require (inquery_table_len(ctx) == 2);

    inquery_field_smart *ifld = inquery_table_field(ctx, 1 ,1);
    inquery_string_smart *key = inquery_field_key(ifld);
    inquery_require (inquery_string_eq(key, "int"));
    inquery_require (inquery_field_int(ifld) == 555);

    printf("...OK\n");
}


/*
 * inquery_test_suite_table() - table interface test suite
 */
extern void inquery_test_suite_table(void)
{
    printf("===============================================================\n");
    printf("Starting table interface test suite...\n\n");

    new_1();

    printf("\n");
}

