#include "../lib/core/core.h"
#include "suite.h"


/*
 * new_l() - test case for inquery_attribute_new()
 */
static void new_1(void)
{
    printf("inquery_attribute_new() creates a new nil attribute...");

    inquery_attribute_smart *test = inquery_attribute_new_nil("test");
    inquery_require (inquery_attribute_nil(test));

    printf("OK\n");
}


/*
 * new_int_1() - test case for inquery_attribute_new_int()
 */
static void new_int_1(void)
{
    printf("inquery_attribute_new_int() creates a new integer attribute...");

    inquery_attribute_smart *test = inquery_attribute_new_int("test", -555);
    inquery_require (inquery_attribute_int(test) == -555);

    printf("OK\n");
}


/*
 * new_real_1() - test case for inquery_attribute_new_real()
 */
static void new_real_1(void)
{
    printf("inquery_attribute_new_int() creates a new real attribute...");

    inquery_attribute_smart *test = inquery_attribute_new_real("test", 
            -555.555);
    inquery_require (inquery_attribute_real(test) == -555.555);

    printf("OK\n");
}


/*
 * new_text_1() - test case for inquery_attribute_new_text()
 */
static void new_text_1(void)
{
    printf("inquery_attribute_new_text() creates a new text attribute...");

    inquery_attribute_smart *test = inquery_attribute_new_text("test",
            "Hello, world!");
    inquery_string_smart *check = inquery_attribute_text(test);
    inquery_require (inquery_string_eq(check, "Hello, world!"));

    printf("OK\n");
}


/*
 * lt_1() - test case #1 for inquery_attribute_lt()
 */
static void lt_1(void)
{
    printf("inquery_attribute_lt() determines if an integer attribute is less"
           " than another");

    inquery_attribute_smart *lhs = inquery_attribute_new_int("test", -555);
    inquery_attribute_smart *rhs = inquery_attribute_new_int("test", 666);
    inquery_require (inquery_attribute_lt(lhs, rhs));

    printf("...OK\n");
}


/*
 * lt_2() - test case #2 for inquery_attribute_lt()
 */
static void lt_2(void)
{
    printf("inquery_attribute_lt() determines if a real attribute is less than"
            " another");

    inquery_attribute_smart *lhs = inquery_attribute_new_real("test", -555.56);
    inquery_attribute_smart *rhs = inquery_attribute_new_real("test", -555.55);
    inquery_require (inquery_attribute_lt(lhs, rhs));

    printf("...OK\n");
}


/*
 * lt_3() - test case #3 for inquery_attribute_lt()
 */
static void lt_3(void)
{
    printf("inquery_attribute_lt() determines if a text attribute is less than"
            " another");

    inquery_attribute_smart *lhs = inquery_attribute_new_text("test", "A man");
    inquery_attribute_smart *rhs = inquery_attribute_new_text("test", 
            "A woman");
    inquery_require (inquery_attribute_lt(lhs, rhs));

    printf("...OK\n");
}


/*
 * eq_1() - test case #1 for inquery_attribute_eq()
 */
static void eq_1(void)
{
    printf("inquery_attribute_eq() determines if an integer attribute is equal"
            " to another");

    inquery_attribute_smart *lhs = inquery_attribute_new_int("test", -555);
    inquery_attribute_smart *rhs = inquery_attribute_new_int("test", -555);
    inquery_require (inquery_attribute_eq(lhs, rhs));

    printf("...OK\n");
}


/*
 * eq_2() - test case #2 for inquery_attribute_eq()
 */
static void eq_2(void)
{
    printf("inquery_attribute_eq() determines if a real attribute is equal to"
            " another");
    
    inquery_attribute_smart *lhs = inquery_attribute_new_real("test", -555.55);
    inquery_attribute_smart *rhs = inquery_attribute_new_real("test", -555.55);
    inquery_require (inquery_attribute_eq(lhs, rhs));

    printf("...OK\n");
}


/*
 * eq_3() - test case #3 for inquery_attribute_eq()
 */
static void eq_3(void)
{
    printf("inquery_attribute_eq() determines if a text attribute is equal to"
            " another");
    
    inquery_attribute_smart *lhs = inquery_attribute_new_text("test", "A man");
    inquery_attribute_smart *rhs = inquery_attribute_new_text("test", "A man");
    inquery_require (inquery_attribute_eq(lhs, rhs));

    printf("...OK\n");
}


/*
 * gt_1() - test case #1 for inquery_attribute_gt()
 */
static void gt_1(void)
{
    printf("inquery_attribute_gt() determines if an integer attribute is"
            " greater than another");

    inquery_attribute_smart *lhs = inquery_attribute_new_int("test", 555);
    inquery_attribute_smart *rhs = inquery_attribute_new_int("test", -666);
    inquery_require (inquery_attribute_gt(lhs, rhs));

    printf("...OK\n");
}


/*
 * gt_2() - test case #2 for inquery_attribute_gt()
 */
static void gt_2(void)
{
    printf("inquery_attribute_gt() determines if a real attribute is greater"
            " than another");

    inquery_attribute_smart *lhs = inquery_attribute_new_real("test", 666.66);
    inquery_attribute_smart *rhs = inquery_attribute_new_real("test", 555.65);
    inquery_require (inquery_attribute_gt(lhs, rhs));

    printf("...OK\n");
}


/*
 * gt_3() - test case #3 for inquery_attribute_gt()
 */
static void gt_3(void)
{
    printf("inquery_attribute_gt() determines if a text attribute is greater"
            " than another");

    inquery_attribute_smart *lhs = inquery_attribute_new_text("test", 
            "A woman");
    inquery_attribute_smart *rhs = inquery_attribute_new_text("test", "A man");
    inquery_require (inquery_attribute_gt(lhs, rhs));

    printf("...OK\n");
}


/*
 * inquery_test_suite_attribute() - attribute interface test suite
 */
extern void inquery_test_suite_attribute(void)
{
    printf("===============================================================\n");
    printf("Starting attribute interface test suite...\n\n");

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

