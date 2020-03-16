#include <string.h>
#include "../lib/core/core.h"
#include "suite.h"


static void test_new_empty_1(void)
{
    printf("inquery_string_new_empty() can create an empty string...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_require (test && !*test);

    printf("OK\n");
}


static void test_new_1(void)
{
    printf("inquery_string_new() can create an ASCII string...");

    const inquery_string *expect = "Hello, world!";
    inquery_string_smart *test = inquery_string_new(expect);
    inquery_require (test && !strcmp(test, expect));

    printf("OK\n");
}


static void test_new_2(void)
{
    printf("inquery_string_new() can create a Unicode string...");

    const inquery_string *expect = "Привет, мир!";
    inquery_string_smart *test = inquery_string_new(expect);
    inquery_require (test && !strcmp(test, expect));

    printf("OK\n");
}

static void test_copy_1(void)
{
    printf("inquery_string_copy() can copy an empty string...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_string_smart *copy = inquery_string_copy(test);
    inquery_require (copy && !*copy);

    printf("OK\n");
}


static void test_copy_2(void)
{
    printf("inquery_string_copy() can copy an ASCII string...");

    const inquery_string *expect = "Hello, world!";
    inquery_string_smart *test = inquery_string_new(expect);
    inquery_string_smart *copy = inquery_string_copy(test);
    inquery_require (test && !strcmp(copy, expect));

    printf("OK\n");
}


static void test_copy_3(void)
{
    printf("inquery_string_copy() can copy a Unicode string...");

    const inquery_string *expect = "Привет, мир!";
    inquery_string_smart *test = inquery_string_new(expect);
    inquery_string_smart *copy = inquery_string_copy(test);
    inquery_require (test && !strcmp(copy, expect));

    printf("OK\n");
}


static void test_len_1(void)
{
    printf("inquery_string_len() reports 0 for a null string...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_require (inquery_string_len(test) == 0);

    printf("OK\n");
}


static void test_len_2(void)
{
    printf("inquery_string_len() reports the length of an ASCII string...");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_len(test) == 13);

    printf("OK\n");
}


static void test_len_3(void)
{
    printf("inquery_string_len() reports the length of a Unicode string...");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_len(test) == 12);

    printf("OK\n");
}


static void test_sz_1(void)
{
    printf("inquery_string_sz() reports 1 for a null string...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_require (inquery_string_sz(test) == 1);

    printf("OK\n");
}


static void test_sz_2(void)
{
    printf("inquery_string_sz() reports the size of an ASCII string...");

    const inquery_string *sample = "Hello, world!";
    inquery_string_smart *test = inquery_string_new(sample);
    inquery_require (inquery_string_sz(test) == strlen(sample) + 1);

    printf("OK\n");
}


static void test_sz_3(void)
{
    printf("inquery_string_sz() reports the size of a Unicode string...");

    const inquery_string *sample = "Привет, мир!";
    inquery_string_smart *test = inquery_string_new(sample);
    inquery_require (inquery_string_sz(test) == strlen(sample) + 1);

    printf("OK\n");
}


static void test_cmp_1(void)
{
    printf("inquery_string_cmp() detects two equal null strings...");

    inquery_string_smart *lhs = inquery_string_new_empty();
    inquery_string_smart *rhs = inquery_string_new_empty();
    inquery_require (!inquery_string_cmp(lhs, rhs));

    printf("OK\n");
}


static void test_cmp_2(void)
{
    printf("inquery_string_cmp() detects two equal ASCII strings...");

    inquery_string_smart *lhs = inquery_string_new("Hello, world!");
    inquery_string_smart *rhs = inquery_string_new("Hello, world!");
    inquery_require (!inquery_string_cmp(lhs, rhs));

    printf("OK\n");
}


static void test_cmp_3(void)
{
    printf("inquery_string_cmp() detects two equal Unicode strings...");

    inquery_string_smart *lhs = inquery_string_new("Привет, мир!");
    inquery_string_smart *rhs = inquery_string_new("Привет, мир!");
    inquery_require (!inquery_string_cmp(lhs, rhs));

    printf("OK\n");
}

static void test_cmp_4(void)
{
    printf("inquery_string_cmp() detects two unequal ASCII strings...");

    inquery_string_smart *lhs = inquery_string_new("Hello, world!");
    inquery_string_smart *rhs = inquery_string_new("Goodbye, moon?");
    inquery_require (inquery_string_cmp(lhs, rhs));

    printf("OK\n");;
}


static void test_cmp_5(void)
{
    printf("inquery_string_cmp() detects two unequal Unicode strings...");

    inquery_string_smart *lhs = inquery_string_new("Привет, мир!");
    inquery_string_smart *rhs = inquery_string_new("До свидания, луна?");
    inquery_require (inquery_string_cmp(lhs, rhs));

    printf("OK\n");;
}


static void test_cmp_6(void)
{
    printf("inquery_string_cmp() detects a lexicographically smaller ASCII"
            " string...");

    inquery_string_smart *lhs = inquery_string_new("Goodbye, moon?");
    inquery_string_smart *rhs = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_cmp(lhs, rhs) < 0);

    printf("OK\n");
}


static void test_cmp_7(void)
{
    printf("inquery_string_cmp() detects a lexicographically smaller Unicode"
            " string...");

    inquery_string_smart *lhs = inquery_string_new("До свидания, луна?");
    inquery_string_smart *rhs = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_cmp(lhs, rhs) < 0);

    printf("OK\n");;
}


static void test_cmp_8(void)
{
    printf("inquery_string_cmp() detects a lexicographically greater ASCII"
            "string...");

    inquery_string_smart *lhs = inquery_string_new("Goodbye, moon?");
    inquery_string_smart *rhs = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_cmp(rhs, lhs) > 0);

    printf("OK\n");;
}


static void test_cmp_9(void)
{
    printf("inquery_string_cmp() detects a lexicographically greater Unicode"
            " string...");

    inquery_string_smart *lhs = inquery_string_new("До свидания, луна?");
    inquery_string_smart *rhs = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_cmp(rhs, lhs) > 0);

    printf("OK\n");;
}


static void test_add_1(void)
{
    printf("inquery_string_add() adds two null strings...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_string_add(&test, "");
    inquery_require (!*test);

    printf("OK\n");;
}


static void test_add_2(void)
{
    printf("inquery_string_add() adds two ASCII strings...");

    inquery_string_smart *test = inquery_string_new("Hello");
    inquery_string_add(&test, ", ");
    inquery_string_add(&test, "world");
    inquery_string_add(&test, "!");
    inquery_require (!strcmp(test, "Hello, world!"));

    printf("OK\n");;
}


static void test_add_3(void)
{
    printf("inquery_string_add() adds two Unicode strings...");

    const inquery_string *expect = "До свидания, луна?";
    inquery_string_smart *test = inquery_string_new("До свидания");
    inquery_string_add(&test, ", ");
    inquery_string_add(&test, "луна");
    inquery_string_add(&test, "?");
    inquery_require (!strcmp(test, expect));

    printf("OK\n");;
}


static void test_find_1(void)
{
    printf("inquery_string_find() can find a null string");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_require (inquery_string_find(test, "") == 1);

    printf("...OK\n");
}


static void test_find_2(void)
{
    printf("inquery_string_find() can find an ASCII string with 1 character");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_find(test, "w") == 8);

    printf("...OK\n");
}


static void test_find_3(void)
{
    printf("inquery_string_find() can find a Unicode string with 1 character");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_find(test, "м") == 9);

    printf("...OK\n");
}


static void test_find_4(void)
{
    printf("inquery_string_find() can find an ASCII string");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_find(test, "world") == 8);

    printf("...OK\n");
}


static void test_find_5(void)
{
    printf("inquery_string_find() can find a Unicode string");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_find(test, "мир") == 9);

    printf("...OK\n");
}



static void test_find_6(void)
{
    printf("inquery_string_find() can detect the absence of an ASCII string"
            " with 1 character");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_find(test, "h") == 0);

    printf("...OK\n");
}


static void test_find_7(void)
{
    printf("inquery_string_find() can detect the absence of a Unicode string"
            " with 1 character");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_find(test, "л") == 0);

    printf("...OK\n");
}


static void test_find_8(void)
{
    printf("inquery_string_find() can detect the absence of an ASCII string");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_find(test, "moon") == 0);

    printf("...OK\n");
}


static void test_find_9(void)
{
    printf("inquery_string_find() can detect the absence of a Unicode string");

    inquery_string_smart *test = inquery_string_new("Привет, мир!"); 
    inquery_require (inquery_string_find(test, "луна") == 0);

    printf("...OK\n");
}

extern void inquery_test_suite_string(void)
{
    printf("===============================================================\n");
    printf("Starting string interface test suite...\n\n");

    test_new_empty_1();
    test_new_1();
    test_new_2();

    test_copy_1();
    test_copy_2();
    test_copy_3();

    test_len_1();
    test_len_2();
    test_len_3();

    test_sz_1();
    test_sz_2();
    test_sz_3();

    test_cmp_1();
    test_cmp_2();
    test_cmp_3();
    test_cmp_4();
    test_cmp_5();
    test_cmp_6();
    test_cmp_7();
    test_cmp_8();
    test_cmp_9();

    test_add_1();
    test_add_2();
    test_add_3();

    test_find_1();
    test_find_2();
    test_find_3();
    test_find_4();
    test_find_5();
    test_find_6();
    test_find_7();
    test_find_8();
    test_find_9();

    printf("\n");
}

