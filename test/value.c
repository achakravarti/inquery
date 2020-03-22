#include "../lib/core/core.h"
#include "suite.h"


/*
 * new_int() - test case for inquery_value_new_int()
 */
static void new_int(void)
{
    printf("inquery_value_new_int() creates a new boxed integer value...");

    inquery_value_smart *test = inquery_value_new_int(-555);
    inquery_require (inquery_value_int(test) == -555);

    printf("OK\n");
}


/*
 * new_int_nil() - test case for inquery_value_new_int_nil()
 */
static void new_int_nil(void)
{
    printf("inquery_value_new_int_nil() creates a new nil integer value...");

    inquery_value_smart *test = inquery_value_new_int_nil();
    inquery_require (inquery_value_nil(test));

    printf("OK\n");
}


/*
 * new_real() - test case for inquery_value_new_real()
 */
static void new_real(void)
{
    printf("inquery_value_new_int() creates a new boxed real value...");

    inquery_value_smart *test = inquery_value_new_real(-555.555);
    inquery_require (inquery_value_real(test) == -555.555);

    printf("OK\n");
}


/*
 * new_real_nil() - test case for inquery_value_new_real_nil()
 */
static void new_real_nil(void)
{
    printf("inquery_value_new_int() creates a new nil real value...");

    inquery_value_smart *test = inquery_value_new_real_nil();
    inquery_require (inquery_value_nil(test));

    printf("OK\n");
}


/*
 * new_text() - test case for inquery_value_new_text()
 */
static void new_text(void)
{
    printf("inquery_value_new_text() creates a new boxed text value...");

    inquery_value_smart *test = inquery_value_new_text("Hello, world!");
    inquery_string_smart *check = inquery_value_text(test);
    inquery_require (inquery_string_eq(check, "Hello, world!"));

    printf("OK\n");
}


/*
 * new_text_nil() - test case for inquery_value_new_text_nil()
 */
static void new_text_nil(void)
{
    printf("inquery_value_new_text_nil() creates a new nil text value...");

    inquery_value_smart *test = inquery_value_new_text_nil();
    inquery_require (inquery_value_nil(test));

    printf("OK\n");
}


extern void inquery_test_suite_value(void)
{
    printf("===============================================================\n");
    printf("Starting value interface test suite...\n\n");

    new_int();
    new_int_nil();

    new_real();
    new_real_nil();

    new_text();
    new_text_nil();

    printf("\n");
}


