#include "suite.h"


int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    inquery_test_suite_heap();
    inquery_test_suite_object();

    return 0;
}

