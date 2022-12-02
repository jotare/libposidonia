#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "graph/testconf.h"


int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_TestInfo
        *graph_traversal_tests = get_graph_traversal_tests();

    CU_SuiteInfo suites[] = {
        {"graph traversal", init_graph_traversal_suite, cleanup_graph_traversal_suite, NULL, NULL, graph_traversal_tests},
        CU_SUITE_INFO_NULL
    };

    if (CU_register_suites(suites) != CUE_SUCCESS) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
