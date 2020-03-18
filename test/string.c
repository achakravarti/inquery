#include <string.h>
#include "../lib/core/core.h"
#include "suite.h"


/*
 * new_empty_1() - test case #1 for inquery_string_new_empty()
 */
static void new_empty_1(void)
{
    printf("inquery_string_new_empty() can create an empty string...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_require (test && !*test);

    printf("OK\n");
}


/*
 * new_1() - test case #1 for inquery_string_new()
 */
static void new_1(void)
{
    printf("inquery_string_new() can create an ASCII string...");

    const inquery_string *expect = "Hello, world!";
    inquery_string_smart *test = inquery_string_new(expect);
    inquery_require (test && !strcmp(test, expect));

    printf("OK\n");
}


/*
 * new_2() - test case #2 for inquery_string_new()
 */
static void new_2(void)
{
    printf("inquery_string_new() can create a Unicode string...");

    const inquery_string *expect = "Привет, мир!";
    inquery_string_smart *test = inquery_string_new(expect);
    inquery_require (test && !strcmp(test, expect));

    printf("OK\n");
}


/*
 * copy_1() - test case #1 for inquery_string_copy()
 */
static void copy_1(void)
{
    printf("inquery_string_copy() can copy an empty string...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_string_smart *copy = inquery_string_copy(test);
    inquery_require (copy && !*copy);

    printf("OK\n");
}


/*
 * copy_2() - test case #2 for inquery_string_copy()
 */
static void copy_2(void)
{
    printf("inquery_string_copy() can copy an ASCII string...");

    const inquery_string *expect = "Hello, world!";
    inquery_string_smart *test = inquery_string_new(expect);
    inquery_string_smart *copy = inquery_string_copy(test);
    inquery_require (test && !strcmp(copy, expect));

    printf("OK\n");
}


/*
 * copy_3() - test case #3 for inquery_string_copy()
 */
static void copy_3(void)
{
    printf("inquery_string_copy() can copy a Unicode string...");

    const inquery_string *expect = "Привет, мир!";
    inquery_string_smart *test = inquery_string_new(expect);
    inquery_string_smart *copy = inquery_string_copy(test);
    inquery_require (test && !strcmp(copy, expect));

    printf("OK\n");
}


/*
 * len_1() - test case #1 for inquery_string_len()
 */
static void len_1(void)
{
    printf("inquery_string_len() reports 0 for a null string...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_require (inquery_string_len(test) == 0);

    printf("OK\n");
}


/*
 * len_2() - test case #2 for inquery_string_len()
 */
static void len_2(void)
{
    printf("inquery_string_len() reports the length of an ASCII string...");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_len(test) == 13);

    printf("OK\n");
}


/*
 * len_3() - test case #3 for inquery_string_len()
 */
static void len_3(void)
{
    printf("inquery_string_len() reports the length of a Unicode string...");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_len(test) == 12);

    printf("OK\n");
}


/*
 * sz_1() - test case #1 for inquery_string_sz()
 */
static void sz_1(void)
{
    printf("inquery_string_sz() reports 1 for a null string...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_require (inquery_string_sz(test) == 1);

    printf("OK\n");
}


/*
 * sz_2() - test case #2 for inquery_string_sz()
 */
static void sz_2(void)
{
    printf("inquery_string_sz() reports the size of an ASCII string...");

    const inquery_string *sample = "Hello, world!";
    inquery_string_smart *test = inquery_string_new(sample);
    inquery_require (inquery_string_sz(test) == strlen(sample) + 1);

    printf("OK\n");
}


/*
 * sz_3() - test case #3 for inquery_string_sz()
 */
static void sz_3(void)
{
    printf("inquery_string_sz() reports the size of a Unicode string...");

    const inquery_string *sample = "Привет, мир!";
    inquery_string_smart *test = inquery_string_new(sample);
    inquery_require (inquery_string_sz(test) == strlen(sample) + 1);

    printf("OK\n");
}


/*
 * cmp_1() - test case #1 for inquery_string_cmp()
 */
static void cmp_1(void)
{
    printf("inquery_string_cmp() detects two equal null strings...");

    inquery_string_smart *lhs = inquery_string_new_empty();
    inquery_string_smart *rhs = inquery_string_new_empty();
    inquery_require (!inquery_string_cmp(lhs, rhs));

    printf("OK\n");
}


/*
 * cmp_2() - test case #2 for inquery_string_cmp()
 */
static void cmp_2(void)
{
    printf("inquery_string_cmp() detects two equal ASCII strings...");

    inquery_string_smart *lhs = inquery_string_new("Hello, world!");
    inquery_string_smart *rhs = inquery_string_new("Hello, world!");
    inquery_require (!inquery_string_cmp(lhs, rhs));

    printf("OK\n");
}


/*
 * cmp_3() - test case #3 for inquery_string_cmp()
 */
static void cmp_3(void)
{
    printf("inquery_string_cmp() detects two equal Unicode strings...");

    inquery_string_smart *lhs = inquery_string_new("Привет, мир!");
    inquery_string_smart *rhs = inquery_string_new("Привет, мир!");
    inquery_require (!inquery_string_cmp(lhs, rhs));

    printf("OK\n");
}


/*
 * cmp_4() - test case #4 for inquery_string_cmp()
 */
static void cmp_4(void)
{
    printf("inquery_string_cmp() detects two unequal ASCII strings...");

    inquery_string_smart *lhs = inquery_string_new("Hello, world!");
    inquery_string_smart *rhs = inquery_string_new("Goodbye, moon?");
    inquery_require (inquery_string_cmp(lhs, rhs));

    printf("OK\n");
}


/*
 * cmp_5() - test case #5 for inquery_string_cmp()
 */
static void cmp_5(void)
{
    printf("inquery_string_cmp() detects two unequal Unicode strings...");

    inquery_string_smart *lhs = inquery_string_new("Привет, мир!");
    inquery_string_smart *rhs = inquery_string_new("До свидания, луна?");
    inquery_require (inquery_string_cmp(lhs, rhs));

    printf("OK\n");
}


/*
 * cmp_6() - test case #6 for inquery_string_cmp()
 */
static void cmp_6(void)
{
    printf("inquery_string_cmp() detects a lexicographically smaller ASCII"
            " string...");

    inquery_string_smart *lhs = inquery_string_new("Goodbye, moon?");
    inquery_string_smart *rhs = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_cmp(lhs, rhs) < 0);

    printf("OK\n");
}


/*
 * cmp_7() - test case #7 for inquery_string_cmp()
 */
static void cmp_7(void)
{
    printf("inquery_string_cmp() detects a lexicographically smaller Unicode"
            " string...");

    inquery_string_smart *lhs = inquery_string_new("До свидания, луна?");
    inquery_string_smart *rhs = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_cmp(lhs, rhs) < 0);

    printf("OK\n");
}


/*
 * cmp_8() - test case #8 for inquery_string_cmp()
 */
static void cmp_8(void)
{
    printf("inquery_string_cmp() detects a lexicographically greater ASCII"
            "string...");

    inquery_string_smart *lhs = inquery_string_new("Goodbye, moon?");
    inquery_string_smart *rhs = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_cmp(rhs, lhs) > 0);

    printf("OK\n");
}


/*
 * cmp_9() - test case #9 for inquery_string_cmp()
 */
static void cmp_9(void)
{
    printf("inquery_string_cmp() detects a lexicographically greater Unicode"
            " string...");

    inquery_string_smart *lhs = inquery_string_new("До свидания, луна?");
    inquery_string_smart *rhs = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_cmp(rhs, lhs) > 0);

    printf("OK\n");
}


/*
 * add_1() - test case #1 for inquery_string_add()
 */
static void add_1(void)
{
    printf("inquery_string_add() adds two null strings...");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_string_add(&test, "");
    inquery_require (!*test);

    printf("OK\n");
}


/*
 * add_2() - test case #2 for inquery_string_add()
 */
static void add_2(void)
{
    printf("inquery_string_add() adds two ASCII strings...");

    inquery_string_smart *test = inquery_string_new("Hello");
    inquery_string_add(&test, ", ");
    inquery_string_add(&test, "world");
    inquery_string_add(&test, "!");
    inquery_require (!strcmp(test, "Hello, world!"));

    printf("OK\n");
}


/*
 * add_3() - test case #3 for inquery_string_add()
 */
static void add_3(void)
{
    printf("inquery_string_add() adds two Unicode strings...");

    const inquery_string *expect = "До свидания, луна?";
    inquery_string_smart *test = inquery_string_new("До свидания");
    inquery_string_add(&test, ", ");
    inquery_string_add(&test, "луна");
    inquery_string_add(&test, "?");
    inquery_require (!strcmp(test, expect));

    printf("OK\n");
}


/*
 * find_1() - test case #1 for inquery_string_find()
 */
static void find_1(void)
{
    printf("inquery_string_find() can find a null string");

    inquery_string_smart *test = inquery_string_new_empty();
    inquery_require (inquery_string_find(test, "") == 1);

    printf("...OK\n");
}


/*
 * find_2() - test case #2 for inquery_string_find()
 */
static void find_2(void)
{
    printf("inquery_string_find() can find an ASCII string with 1 character");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_find(test, "w") == 8);

    printf("...OK\n");
}


/*
 * find_3() - test case #3 for inquery_string_find()
 */
static void find_3(void)
{
    printf("inquery_string_find() can find a Unicode string with 1 character");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_find(test, "м") == 9);

    printf("...OK\n");
}


/*
 * find_4() - test case #4 for inquery_string_find()
 */
static void find_4(void)
{
    printf("inquery_string_find() can find an ASCII string");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_find(test, "world") == 8);

    printf("...OK\n");
}


/*
 * find_5() - test case #5 for inquery_string_find()
 */
static void find_5(void)
{
    printf("inquery_string_find() can find a Unicode string");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_find(test, "мир") == 9);

    printf("...OK\n");
}


/*
 * find_6() - test case #5 for inquery_string_find()
 */
static void find_6(void)
{
    printf("inquery_string_find() can detect the absence of an ASCII string"
            " with 1 character");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_find(test, "h") == 0);

    printf("...OK\n");
}


/*
 * find_7() - test case #5 for inquery_string_find()
 */
static void find_7(void)
{
    printf("inquery_string_find() can detect the absence of a Unicode string"
            " with 1 character");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_require (inquery_string_find(test, "л") == 0);

    printf("...OK\n");
}


/*
 * find_8() - test case #8 for inquery_string_find()
 */
static void find_8(void)
{
    printf("inquery_string_find() can detect the absence of an ASCII string");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_require (inquery_string_find(test, "moon") == 0);

    printf("...OK\n");
}


/*
 * find_9() - test case #9 for inquery_string_find()
 */
static void find_9(void)
{
    printf("inquery_string_find() can detect the absence of a Unicode string");

    inquery_string_smart *test = inquery_string_new("Привет, мир!"); 
    inquery_require (inquery_string_find(test, "луна") == 0);

    printf("...OK\n");
}


/*
 * replace_first_1() - test case #1 for inquery_string_replace_first()
 */
static void replace_first_1(void)
{
    printf("inquery_string_replace_first() replaces an ASCII character with a"
            " null character");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_replace_first(&test, "!", "");
    inquery_require (!strcmp(test, "Hello, world"));

    printf("...OK\n");
}


/*
 * replace_first_2() - test case #2 for inquery_string_replace_first()
 */
static void replace_first_2(void)
{
    printf("inquery_string_replace_first() replaces a Unicode character with a"
            " null character");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_string_replace_first(&test, "т", "");
    inquery_require (!strcmp(test, "Приве, мир!"));

    printf("...OK\n");
}


/*
 * replace_first_3() - test case #3 for inquery_string_replace_first()
 */
static void replace_first_3(void)
{
    printf("inquery_string_replace_first() replaces only the first instance in an"
            " ASCII string");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_replace_first(&test, "l", "y");
    inquery_require (!strcmp(test, "Heylo, world!"));
    
    printf("...OK\n");
}


/*
 * replace_first_4() - test case #4 for inquery_string_replace_first()
 */
static void replace_first_4(void)
{
    printf("inquery_string_replace_first() replaces only the first instance in a"
            " Unicode string");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_string_replace_first(&test, "р", "r");
    inquery_require (!strcmp(test, "Пrивет, мир!"));
    
    printf("...OK\n");
}


/*
 * replace_first_5() - test case #5 for inquery_string_replace_first()
 */
static void replace_first_5(void)
{
    printf("inquery_string_replace_first() replaces an ASCII substring");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_replace_first(&test, "world", "moon");
    inquery_require (!strcmp(test, "Hello, moon!"));

    printf("...OK\n");
}


/*
 * replace_first_6() - test case #6 for inquery_string_replace_first()
 */
static void replace_first_6(void)
{
    printf("inquery_string_replace_first() replaces a Unicode substring");

    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_string_replace_first(&test, "Привет", "До свидания");
    inquery_require (!strcmp(test, "До свидания, мир!"));
    
    printf("...OK\n");
}


/*
 * replace_first_7() - test case #7 for inquery_string_replace_first()
 */
static void replace_first_7(void)
{
    printf("inquery_string_replace_first() replaces an entire ASCII string");

    const inquery_string *expect = "Goodbye, moon?";
    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_replace_first(&test, "Hello, world!", expect);
    inquery_require (!strcmp(test, expect));

    printf("...OK\n");
}


/*
 * replace_first_8() - test case #8 for inquery_string_replace_first()
 */
static void replace_first_8(void)
{
    printf("inquery_string_replace_first() replaces an entire Unicode string");

    const inquery_string *expect = "До свидания, луна?";
    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_string_replace_first(&test, "Привет, мир!", expect);
    inquery_require (!strcmp(test, expect));
    
    printf("...OK\n");
}


/*
 * replace_first_9() - test case #9 for inquery_string_replace_first()
 */
static void replace_first_9(void)
{
    printf("inquery_string_replace_first() has no effect if @ctx, @what, and"
            "@with are all the same");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_smart *what = inquery_string_new("Hello, world!");
    inquery_string_smart *with = inquery_string_new("Hello, world!");
    inquery_string_replace_first(&test, what, with);
    inquery_require (!strcmp(test, what));
    
    printf("...OK\n");
}


/*
 * replace_first_10() - test case #10 for inquery_string_replace_first()
 */
static void replace_first_10(void)
{
    printf("inquery_string_replace_first() can replace the first instance of"
            " the same sequence of characters");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_smart *expect = inquery_string_new("Helllo, world!");
    inquery_string_replace_first(&test, "l", "ll");
    inquery_require (!inquery_string_cmp(test, expect));

    printf("...OK\n");
}


/*
 * replace_1() - test case #1 for inquery_string_replace()
 */
static void replace_1(void)
{
    printf("inquery_string_replace() replaces an ASCII character with a null"
            " character");
    
    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_replace(&test, "!", "");
    inquery_require (!strcmp(test, "Hello, world"));
    
    printf("...OK\n");
}


/*
 * replace_2() - test case #2 for inquery_string_replace()
 */
static void replace_2(void)
{
    printf("inquery_string_replace() replaces a Unicode character with a null"
            " character");
    
    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_string_replace(&test, "т", "");
    inquery_require (!strcmp(test, "Приве, мир!"));
    
    printf("...OK\n");
}


/*
 * replace_3() - test case #3 for inquery_string_replace()
 */
static void replace_3(void)
{
    printf("inquery_string_replace() replaces all the instances in an ASCII"
            " string");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_replace(&test, "l", "y");
    inquery_require (!strcmp(test, "Heyyo, woryd!"));
    
    printf("...OK\n");
}


/*
 * replace_4() - test case #4 for inquery_string_replace()
 */
static void replace_4(void)
{
    printf("inquery_string_replace() replaces all the instances in a Unicode"
            " string");
    
    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_string_replace(&test, "р", "r");
    inquery_require (!strcmp(test, "Пrивет, миr!"));
    
    printf("...OK\n");
}


/*
 * replace_5() - test case #5 for inquery_string_replace()
 */
static void replace_5(void)
{
    printf("inquery_string_replace() replaces an ASCII substring");
    
    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_replace(&test, "world", "moon");
    inquery_require (!strcmp(test, "Hello, moon!"));
    
    printf("...OK\n");
}


/*
 * replace_6() - test case #6 for inquery_string_replace()
 */
static void replace_6(void)
{
    printf("inquery_string_replace() replaces a Unicode substring");
    
    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_string_replace(&test, "Привет", "До свидания");
    inquery_require (!strcmp(test, "До свидания, мир!"));

    printf("...OK\n");
}


/*
 * replace_7() - test case #7 for inquery_string_replace()
 */
static void replace_7(void)
{
    printf("inquery_string_replace() replaces an entire ASCII string");
    
    const inquery_string *expect = "Goodbye, moon?";
    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_replace(&test, "Hello, world!", expect);
    inquery_require (!strcmp(test, expect));
    
    printf("...OK\n");
}


/*
 * replace_8() - test case #8 for inquery_string_replace()
 */
static void replace_8(void)
{
    printf("inquery_string_replace() replaces an entire Unicode string");
    
    const inquery_string *expect = "До свидания, луна?";
    inquery_string_smart *test = inquery_string_new("Привет, мир!");
    inquery_string_replace(&test, "Привет, мир!", expect);
    inquery_require (!strcmp(test, expect));

    printf("...OK\n");
}


/*
 * replace_9() - test case #9 for inquery_string_replace()
 */
static void replace_9(void)
{
    printf("inquery_string_replace() has no effect if @ctx, @what, and @with"
            " are all the same");

    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_smart *what = inquery_string_new("Hello, world!");
    inquery_string_smart *with = inquery_string_new("Hello, world!");
    inquery_string_replace(&test, what, with);
    inquery_require (!strcmp(test, what));
    
    printf("...OK\n");
}


/*
 * replace_10() - test case #10 for inquery_string_replace()
 */
static void replace_10(void)
{
    printf("inquery_string_replace() can replace all instance of the same"
            " sequence of characters");
    
    inquery_string_smart *test = inquery_string_new("Hello, world!");
    inquery_string_smart *expect = inquery_string_new("Hellllo, worlld!");
    inquery_string_replace(&test, "l", "ll");
    inquery_require (!inquery_string_cmp(test, expect));
    
    printf("...OK\n");
}


/*
 * inquery_test_suite_string() - string interface test suite
 */
extern void inquery_test_suite_string(void)
{
    printf("===============================================================\n");
    printf("Starting string interface test suite...\n\n");

    new_empty_1();
    new_1();
    new_2();

    copy_1();
    copy_2();
    copy_3();

    len_1();
    len_2();
    len_3();

    sz_1();
    sz_2();
    sz_3();

    cmp_1();
    cmp_2();
    cmp_3();
    cmp_4();
    cmp_5();
    cmp_6();
    cmp_7();
    cmp_8();
    cmp_9();

    add_1();
    add_2();
    add_3();

    find_1();
    find_2();
    find_3();
    find_4();
    find_5();
    find_6();
    find_7();
    find_8();
    find_9();

    replace_first_1();
    replace_first_2();
    replace_first_3();
    replace_first_4();
    replace_first_5();
    replace_first_6();
    replace_first_7();
    replace_first_8();
    replace_first_9();
    replace_first_10();

    replace_1();
    replace_2();
    replace_3();
    replace_4();
    replace_5();
    replace_6();
    replace_7();
    replace_8();
    replace_9();
    replace_10();

    printf("\n");
}

