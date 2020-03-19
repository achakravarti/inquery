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


/*
 * lt_1() - test case #1 for inquery_value_lt()
 */
static void lt_1(void)
{
    printf("inquery_value_lt() determines if an integer value is less than"
            " another");

    inquery_value_smart *lhs = inquery_value_new_int(-555);
    inquery_value_smart *rhs = inquery_value_new_int(666);
    inquery_require (inquery_value_lt(lhs, rhs));

    printf("...OK\n");
}


/*
 * lt_2() - test case #2 for inquery_value_lt()
 */
static void lt_2(void)
{
    printf("inquery_value_lt() determines if a real value is less than"
            " another");

    inquery_value_smart *lhs = inquery_value_new_real(-555.56);
    inquery_value_smart *rhs = inquery_value_new_real(-555.55);
    inquery_require (inquery_value_lt(lhs, rhs));

    printf("...OK\n");
}


/*
 * lt_3() - test case #3 for inquery_value_lt()
 */
static void lt_3(void)
{
    printf("inquery_value_lt() determines if a text value is less than"
            " another");

    inquery_value_smart *lhs = inquery_value_new_text("A man");
    inquery_value_smart *rhs = inquery_value_new_text("A woman");
    inquery_require (inquery_value_lt(lhs, rhs));

    printf("...OK\n");
}


/*
 * eq_1() - test case #1 for inquery_value_eq()
 */
static void eq_1(void)
{
    printf("inquery_value_eq() determines if an integer value is equal to"
            " another");

    inquery_value_smart *lhs = inquery_value_new_int(-555);
    inquery_value_smart *rhs = inquery_value_new_int(-555);
    inquery_require (inquery_value_eq(lhs, rhs));

    printf("...OK\n");
}


/*
 * eq_2() - test case #2 for inquery_value_eq()
 */
static void eq_2(void)
{
    printf("inquery_value_eq() determines if a real value is equal to another");
    
    inquery_value_smart *lhs = inquery_value_new_real(-555.55);
    inquery_value_smart *rhs = inquery_value_new_real(-555.55);
    inquery_require (inquery_value_eq(lhs, rhs));

    printf("...OK\n");
}


/*
 * eq_3() - test case #3 for inquery_value_eq()
 */
static void eq_3(void)
{
    printf("inquery_value_eq() determines if a text value is equal to another");
    
    inquery_value_smart *lhs = inquery_value_new_text("A man");
    inquery_value_smart *rhs = inquery_value_new_text("A man");
    inquery_require (inquery_value_eq(lhs, rhs));

    printf("...OK\n");
}


/*
 * gt_1() - test case #1 for inquery_value_gt()
 */
static void gt_1(void)
{
    printf("inquery_value_gt() determines if an integer value is greater than"
            " another");

    inquery_value_smart *lhs = inquery_value_new_int(555);
    inquery_value_smart *rhs = inquery_value_new_int(-666);
    inquery_require (inquery_value_gt(lhs, rhs));

    printf("...OK\n");
}


/*
 * gt_2() - test case #2 for inquery_value_gt()
 */
static void gt_2(void)
{
    printf("inquery_value_gt() determines if a real value is greater than"
            " another");

    inquery_value_smart *lhs = inquery_value_new_real(666.66);
    inquery_value_smart *rhs = inquery_value_new_real(555.65);
    inquery_require (inquery_value_gt(lhs, rhs));

    printf("...OK\n");
}


/*
 * gt_3() - test case #3 for inquery_value_gt()
 */
static void gt_3(void)
{
    printf("inquery_value_gt() determines if a text value is greater than"
            " another");

    inquery_value_smart *lhs = inquery_value_new_text("A woman");
    inquery_value_smart *rhs = inquery_value_new_text("A man");
    inquery_require (inquery_value_gt(lhs, rhs));

    printf("...OK\n");
}


extern void inquery_test_suite_value(void)
{
    printf("===============================================================\n");
    printf("Starting value interface test suite...\n\n");

    new_1();
    new_int_1();
    new_real_1();
    new_text_1();

    lt_1();
    lt_2();
    lt_3();

    eq_1();
    eq_2();
    eq_3();

    gt_1();
    gt_2();
    gt_3();

    printf("\n");
}


