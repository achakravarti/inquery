#include "../lib/core/core.h"
#include "suite.h"


/*
 * struct payload - sample payload for testing
 */
struct payload {
    int x;
    int y;
};


/*
 * test_new() - inquery_object() test case
 */
static void test_new(void)
{
    printf("inquery_object_new() creates an object with a payload...");

    struct payload *p = inquery_heap_new(sizeof *p);
    p->x = 555;
    p->y = 666;

    struct inquery_object_vtable vt = { 
        .payload_copy = NULL, 
        .payload_free = NULL
    };

    inquery_object_smart *obj = inquery_object_new(p, &vt);
    inquery_require (obj);

    printf("OK\n");
}


/*
 * test_new_noload() - inquery_object_new_noload() test case
 */
static void test_new_noload(void)
{
    printf("inquery_object_new_noload() creates an object with no payload...");

    inquery_object_smart *obj = inquery_object_new_noload();
    
    inquery_require (obj);
    inquery_require (!inquery_object_payload(obj));

    printf("OK\n");
}


/*
 * test_free() - inquery_object_free() test case
 */
static void test_free(void)
{
    printf("inquery_object_free() releases an object...");
    
    inquery_object *obj = inquery_object_new_noload();
    inquery_require (obj);

    inquery_object_free(&obj);
    inquery_require (!obj);

    printf("OK\n");
}


/*
 * test_payload() - inquery_object_payload() test case
 */
static void test_payload(void)
{
    printf("inquery_object_payload() gets a handle to the payload...");

    struct payload *tmp = inquery_heap_new(sizeof *tmp);
    tmp->x = 555;
    tmp->y = 666;

    struct inquery_object_vtable vt = { 
        .payload_copy = NULL, 
        .payload_free = NULL
    };

    inquery_object_smart *obj = inquery_object_new(tmp, &vt);
    inquery_require (obj);

    const struct payload *p = inquery_object_payload(obj);
    inquery_require (p->x == 555);
    inquery_require (p->y == 666);

    printf("OK\n");
}


/*
 * test_payload_mutable() - inquery_object_payload_mutable() test case
 */
static void test_payload_mutable(void)
{
    printf("inquery_object_payload_mutable() gets a mutable handle to the"
            " payload...");

    struct payload *tmp = inquery_heap_new(sizeof *tmp);
    tmp->x = 555;
    tmp->y = 666;

    struct inquery_object_vtable vt = { 
        .payload_copy = NULL, 
        .payload_free = NULL
    };

    inquery_object_smart *obj = inquery_object_new(tmp, &vt);
    inquery_require (obj);

    struct payload *p = inquery_object_payload_mutable(&obj);
    p->x = 666;
    p->y = 555;
    
    inquery_require (p->x == 666);
    inquery_require (p->y == 555);

    printf("OK\n");
}


   
/*
 * inquery_test_suite_object() - object model interface test suite
 */
extern void inquery_test_suite_object(void)
{
    printf("===============================================================\n");
    printf("Starting object model interface test suite...\n\n");

    test_new();
    test_new_noload();
    test_free();
    test_payload();
    test_payload_mutable();

    printf("\n");
}

