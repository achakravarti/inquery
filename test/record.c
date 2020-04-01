#include "../lib/core/core.h"
#include "suite.h"


static inquery_attribute *attrib_int(void)
{
    return inquery_attribute_new_int("int", 555);
}


static inquery_attribute *attrib_real(void)
{
    return inquery_attribute_new_real("real", -666.66);
}


static inquery_attribute *attrib_text(void)
{
    return inquery_attribute_new_text("text", "test");
}


static void new_1(void)
{
    printf("inquery_record new() creates a new record");

    inquery_attribute_smart *iattr = attrib_int();
    inquery_attribute_smart *rattr = attrib_real();
    inquery_attribute_smart *tattr = attrib_text();

    const inquery_attribute *attr[] = {
        iattr,
        rattr,
        tattr
    };

    size_t len = sizeof attr / sizeof *attr;
    inquery_record_smart *rec = inquery_record_new(attr, len);
    inquery_require (inquery_record_len(rec) == len);

    inquery_attribute_smart *attr1 = inquery_record_get(rec, 1);
    inquery_attribute_smart *attr2 = inquery_record_get(rec, 2);
    inquery_attribute_smart *attr3 = inquery_record_get(rec, 3);

    inquery_require (inquery_attribute_eq(attr1, iattr));
    inquery_require (inquery_attribute_eq(attr2, rattr));
    inquery_require (inquery_attribute_eq(attr3, tattr));

    printf("...OK\n");
}


static void copy_1(void)
{
    printf("inquery_record_copy() creates a copy of an existing record");

    inquery_attribute_smart *iattr = attrib_int();
    inquery_attribute_smart *rattr = attrib_real();
    inquery_attribute_smart *tattr = attrib_text();

    const inquery_attribute *attr[] = {
        iattr,
        rattr,
        tattr
    };

    size_t len = sizeof attr / sizeof *attr;
    inquery_record_smart *ctx = inquery_record_new(attr, len);
    inquery_record_smart *cp = inquery_record_copy(ctx);
    inquery_require (inquery_record_len(cp) == len);

    inquery_attribute_smart *attr1 = inquery_record_get(cp, 1);
    inquery_attribute_smart *attr2 = inquery_record_get(cp, 2);
    inquery_attribute_smart *attr3 = inquery_record_get(cp, 3);

    inquery_require (inquery_attribute_eq(attr1, iattr));
    inquery_require (inquery_attribute_eq(attr2, rattr));
    inquery_require (inquery_attribute_eq(attr3, tattr));

    printf("...OK\n");
}


static void set_1(void)
{
    printf("inquery_record_set() updates a record attribute");

    inquery_attribute_smart *iattr = attrib_int();
    inquery_attribute_smart *rattr = attrib_real();
    inquery_attribute_smart *tattr = attrib_text();

    const inquery_attribute *attr[] = {
        iattr,
        iattr,
        tattr
    };

    size_t len = sizeof attr / sizeof *attr;
    inquery_record_smart *ctx = inquery_record_new(attr, len);
    inquery_record_set(&ctx, 2, rattr);

    inquery_attribute_smart *attr1 = inquery_record_get(ctx, 1);
    inquery_attribute_smart *attr2 = inquery_record_get(ctx, 2);
    inquery_attribute_smart *attr3 = inquery_record_get(ctx, 3);

    inquery_require (inquery_attribute_eq(attr1, iattr));
    inquery_require (inquery_attribute_eq(attr2, rattr));
    inquery_require (inquery_attribute_eq(attr3, tattr));

    printf("...OK\n");
}


static void json_1(void)
{
    printf("inquery_record_json() correctly represents a record");

    inquery_attribute_smart *iattr = attrib_int();
    inquery_attribute_smart *rattr = attrib_real();
    inquery_attribute_smart *tattr = attrib_text();

    const inquery_attribute *attr[] = {
        iattr,
        rattr,
        tattr
    };

    size_t len = sizeof attr / sizeof *attr;
    inquery_record_smart *ctx = inquery_record_new(attr, len);
    inquery_string_smart *json = inquery_record_json(ctx);

    inquery_require (inquery_string_eq (json,
            "{\"int\":555,\"real\":-666.660000,\"text\":\"test\"}"));

    printf("...OK\n");
}


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

