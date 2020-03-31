#include "suite.h"


int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    inquery_test_suite_heap();
    inquery_test_suite_string();
    inquery_test_suite_object();
    inquery_test_suite_value();
    inquery_test_suite_attribute();

    return 0;
}

