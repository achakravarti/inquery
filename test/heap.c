#include "../lib/core/core.h"
#include "suite.h"


/*
 * test_new() - inq_heap_new() test case
 */
static void test_new(void)
{
    printf("inq_heap_new() dynamically allocates memory on the heap...");

    int *bfr = inq_heap_new(sizeof *bfr);
    *bfr = 555;

    inq_require (*bfr == 555);
    inq_heap_free((void **) &bfr);

    printf("OK\n");
}


/*
 * test_resize() - inq_heap_resize() test case
 */
static void test_resize(void)
{
    printf("inq_heap_resize() resizes an existing heap memory buffer...");

    int *bfr = inq_heap_new(sizeof *bfr);
    *bfr = 555;
    inq_require (*bfr == 555);

    inq_heap_resize((void **) &bfr, sizeof *bfr * 2);
    inq_require (*bfr == 555);

    bfr[1] = 666;
    inq_require (bfr[1] == 666);
    
    printf("OK\n");
}


/*
 * test_free() - inq_heap_free() test case
 */
static void test_free(void)
{
    printf("inq_heap_free() releases an existing heap memory buffer...");

    int *bfr = inq_heap_new(sizeof *bfr);
    inq_require (bfr);

    inq_heap_free((void **) &bfr);
    inq_require (!bfr);
    
    printf("OK\n");
}


/*
 * inq_test_suite_heap() - heap memory interface test suite
 */
extern void inq_test_suite_heap(void)
{
    printf("===============================================================\n");
    printf("Starting heap interface test suite...\n\n");

    test_new();
    test_resize();
    test_free();

    printf("\n");
}

