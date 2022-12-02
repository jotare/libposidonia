#ifndef GRAPHS_TESTCONF_H
#define GRAPHS_TESTCONF_H

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

/**
 * @return Graph traversal test case array
 */
CU_TestInfo *get_graph_traversal_tests(void);

int init_graph_traversal_suite(void);
int cleanup_graph_traversal_suite(void);


#endif /* GRAPHS_TESTCONF_H */
