#include "../lib/core/core.h"
#include "suite.h"


/*
 * new_l() - test case for inquery_value_new()
 */
static void new_1(void)
{
    printf("inquery_value_new() creates a new nil value...");

    inquery_value_smart *test = inquery_value_new();
    inquery_require (inquery_value_nil(test));

    printf("OK\n");
}


/*
 * new_int_1() - test case for inquery_value_new_int()
 */
static void new_int_1(void)
{
    printf("inquery_value_new_int() creates a new boxed integer value...");

    inquery_value_smart *test = inquery_value_new_int(-555);
    inquery_require (inquery_value_int(test) == -555);

    printf("OK\n");
}


/*
 * new_real_1() - test case for inquery_value_new_real()
 */
static void new_real_1(void)
{
    printf("inquery_value_new_int() creates a new boxed real value...");

    inquery_value_smart *test = inquery_value_new_real(-555.555);
    inquery_require (inquery_value_real(test) == -555.555);

    printf("OK\n");
}


/*
 * new_text_1() - test case for inquery_value_new_text()
 */
static void new_text_1(void)
{
    printf("inquery_value_new_text() creates a new boxed text value...");

    inquery_value_smart *test = inquery_value_new_text("Hello, world!");
    inquery_string_smart *check = inquery_value_text(test);
    inquery_require (inquery_string_eq(check, "Hello, world!"));

    printf("OK\n");
}


extern void inquery_test_suite_value(void)
{
    printf("===============================================================\n");
    printf("Starting value interface test suite...\n\n");

    new_1();
    new_int_1();
    new_real_1();
    new_text_1();

    printf("\n");
}


