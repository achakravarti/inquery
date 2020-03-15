#include "../lib/core/core.h"
#include "suite.h"


/*
 * test_new() - inquery_heap_new() test case
 */
static void test_new(void)
{
    printf("inquery_heap_new() dynamically allocates memory on the heap...");

    int *bfr = inquery_heap_new(sizeof *bfr);
    *bfr = 555;

    inquery_require (*bfr == 555);
    inquery_heap_free((void **) &bfr);

    printf("OK\n");
}


/*
 * test_resize() - inquery_heap_resize() test case
 */
static void test_resize(void)
{
    printf("inquery_heap_resize() resizes an existing heap memory buffer...");

    int *bfr = inquery_heap_new(sizeof *bfr);
    *bfr = 555;
    inquery_require (*bfr == 555);

    inquery_heap_resize((void **) &bfr, sizeof *bfr * 2);
    inquery_require (*bfr == 555);

    bfr[1] = 666;
    inquery_require (bfr[1] == 666);
    inquery_heap_free((void **) &bfr);
    
    printf("OK\n");
}


/*
 * test_free() - inquery_heap_free() test case
 */
static void test_free(void)
{
    printf("inquery_heap_free() releases an existing heap memory buffer...");

    int *bfr = inquery_heap_new(sizeof *bfr);
    inquery_require (bfr);

    inquery_heap_free((void **) &bfr);
    inquery_require (!bfr);
    
    printf("OK\n");
}

   
/*
 * inquery_test_suite_heap() - heap memory interface test suite
 */
extern void inquery_test_suite_heap(void)
{
    printf("===============================================================\n");
    printf("Starting heap interface test suite...\n\n");

    test_new();
    test_resize();
    test_free();

    printf("\n");
}

