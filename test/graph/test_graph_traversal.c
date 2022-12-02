#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "graph/traversal.h"

#include "graph/testconf.h"

int
init_graph_traversal_suite(void)
{
    return 0;
}

int
cleanup_graph_traversal_suite(void)
{
    return 0;
}

void test_directed_graph_bfs(void) {
    /*
     *                  +---+
     *                  | 0 |
     *                  +---+
     *                   \|/
     *         +----------+------------+
     *        \|/                     \|/
     *       +---+                   +---+
     *       | 1 |                   | 2 |
     *       +---+                   +---+
     *         |                      \|/
     *   +-----+------+          +-----+-----+
     *  \|/          \|/        \|/         \|/
     * +---+       +---+       +---+       +---+
     * | 3 |       | 4 |       | 5 |       | 6 |
     * +---+       +---+       +---+       +---+
     *               |                       |
     *               |                       |
     *               |                       |
     *               |         +---+         |
     *               +-------->| 7 |<---------
     *                         +---+
     */
    graph_t graph;

    // Adjacency matrix graph implementation returns neighbors in
    // numerical sorted order. We depend on that for the test
    graph_init(&graph, 8, DIRECTED_GRAPH_ADJ_MATRIX);
    vertex_t expected_bfs[] = {0, 1, 2, 3, 4, 5, 6, 7};

    graph_edge_add(graph, (edge_t) {0, 1}, NULL);
    graph_edge_add(graph, (edge_t) {0, 2}, NULL);

    graph_edge_add(graph, (edge_t) {1, 3}, NULL);
    graph_edge_add(graph, (edge_t) {1, 4}, NULL);
    graph_edge_add(graph, (edge_t) {2, 5}, NULL);
    graph_edge_add(graph, (edge_t) {2, 6}, NULL);

    graph_edge_add(graph, (edge_t) {4, 7}, NULL);
    graph_edge_add(graph, (edge_t) {6, 7}, NULL);

    list_t traversal = bfs(graph, 0);

    CU_ASSERT_EQUAL(list_length(traversal), 8);

    for (int i = 0; i < list_length(traversal); i++) {
        CU_ASSERT_EQUAL(list_get(traversal, i), expected_bfs[i]);
    }
}


void test_undirected_graph_bfs(void) {
    /*
     *                  +---+
     *                  | 0 |
     *                  +---+
     *                    |
     *         +----------+------------+
     *         |                       |
     *       +---+                   +---+
     *       | 1 |                   | 2 |
     *       +---+                   +---+
     *         |                       |
     *   +-----+------+          +-----+-----+
     *   |            |          |           |
     * +---+       +---+       +---+       +---+
     * | 3 |       | 4 |       | 5 |       | 6 |
     * +---+       +---+       +---+       +---+
     *               |                       |
     *               |                       |
     *               |                       |
     *               |         +---+         |
     *               +---------| 7 |----------
     *                         +---+
     */
    graph_t graph;

    // Adjacency matrix graph implementation returns neighbors in
    // numerical sorted order. We depend on that for the test
    graph_init(&graph, 8, UNDIRECTED_GRAPH_ADJ_MATRIX);
    vertex_t expected_bfs[] = {0, 1, 2, 3, 4, 5, 6, 7};

    graph_edge_add(graph, (edge_t) {0, 1}, NULL);
    graph_edge_add(graph, (edge_t) {0, 2}, NULL);

    graph_edge_add(graph, (edge_t) {1, 3}, NULL);
    graph_edge_add(graph, (edge_t) {1, 4}, NULL);
    graph_edge_add(graph, (edge_t) {2, 5}, NULL);
    graph_edge_add(graph, (edge_t) {2, 6}, NULL);

    graph_edge_add(graph, (edge_t) {4, 7}, NULL);
    graph_edge_add(graph, (edge_t) {6, 7}, NULL);

    list_t traversal = bfs(graph, 0);

    CU_ASSERT_EQUAL(list_length(traversal), 8);

    for (int i = 0; i < list_length(traversal); i++) {
        CU_ASSERT_EQUAL(list_get(traversal, i), expected_bfs[i]);
    }
}
void test_directed_graph_dfs(void) {
    /*
     *                  +---+
     *                  | 0 |
     *                  +---+
     *                   \|/
     *         +----------+------------+
     *        \|/                     \|/
     *       +---+                   +---+
     *       | 1 |                   | 2 |
     *       +---+                   +---+
     *         |                      \|/
     *   +-----+------+          +-----+-----+
     *  \|/          \|/        \|/         \|/
     * +---+       +---+       +---+       +---+
     * | 3 |       | 4 |       | 5 |       | 6 |
     * +---+       +---+       +---+       +---+
     *               |                       |
     *               |                       |
     *               |                       |
     *               |         +---+         |
     *               +-------->| 7 |<---------
     *                         +---+
     */
    graph_t graph;

    // Adjacency list graph implementation returns neighbors in
    // reverse order in which vertices are added. DFS iterative
    // implementation uses a stack and reverses again this order. We
    // relay on that for the test
    graph_init(&graph, 8, DIRECTED_GRAPH_ADJ_LIST);
    vertex_t expected_dfs[] = {0, 1, 2, 3, 4, 6, 7, 5};

    graph_edge_add(graph, (edge_t) {0, 1}, NULL);
    graph_edge_add(graph, (edge_t) {0, 6}, NULL);

    graph_edge_add(graph, (edge_t) {1, 2}, NULL);
    graph_edge_add(graph, (edge_t) {1, 3}, NULL);
    graph_edge_add(graph, (edge_t) {6, 7}, NULL);
    graph_edge_add(graph, (edge_t) {6, 5}, NULL);

    graph_edge_add(graph, (edge_t) {3, 4}, NULL);
    graph_edge_add(graph, (edge_t) {5, 4}, NULL);

    list_t traversal = dfs(graph, 0);

    CU_ASSERT_EQUAL(list_length(traversal), 8);

    for (int i = 0; i < list_length(traversal); i++) {
        CU_ASSERT_EQUAL(list_get(traversal, i), expected_dfs[i]);
    }
}


void test_undirected_graph_dfs(void) {
    /*
     *                  +---+
     *                  | 0 |
     *                  +---+
     *                    |
     *         +----------+------------+
     *         |                       |
     *       +---+                   +---+
     *       | 1 |                   | 6 |
     *       +---+                   +---+
     *         |                       |
     *   +-----+------+          +-----+-----+
     *   |            |          |           |
     * +---+       +---+       +---+       +---+
     * | 2 |       | 3 |       | 7 |       | 5 |
     * +---+       +---+       +---+       +---+
     *               |                       |
     *               |                       |
     *               |                       |
     *               |         +---+         |
     *               +---------| 4 |----------
     *                         +---+
     */
    graph_t graph;

    // Adjacency list graph implementation returns neighbors in
    // reverse order in which vertices are added. DFS iterative
    // implementation uses a stack and reverses again this order. We
    // relay on that for the test
    graph_init(&graph, 8, UNDIRECTED_GRAPH_ADJ_LIST);
    vertex_t expected_dfs[] = {0, 1, 2, 3, 4, 5, 6, 7};

    graph_edge_add(graph, (edge_t) {0, 1}, NULL);
    graph_edge_add(graph, (edge_t) {0, 6}, NULL);

    graph_edge_add(graph, (edge_t) {1, 2}, NULL);
    graph_edge_add(graph, (edge_t) {1, 3}, NULL);
    graph_edge_add(graph, (edge_t) {6, 7}, NULL);
    graph_edge_add(graph, (edge_t) {6, 5}, NULL);

    graph_edge_add(graph, (edge_t) {3, 4}, NULL);
    graph_edge_add(graph, (edge_t) {5, 4}, NULL);

    list_t traversal = dfs(graph, 0);

    CU_ASSERT_EQUAL(list_length(traversal), 8);

    for (int i = 0; i < list_length(traversal); i++) {
        CU_ASSERT_EQUAL(list_get(traversal, i), expected_dfs[i]);
    }
}


static CU_TestInfo graph_traversal_tests[] = {
    {"graph directed BFS", test_directed_graph_bfs},
    {"graph undirected BFS", test_undirected_graph_bfs},
    {"graph directed DFS", test_directed_graph_dfs},
    {"graph undirected DFS", test_undirected_graph_dfs},

    CU_TEST_INFO_NULL
};

CU_TestInfo *
get_graph_traversal_tests(void)
{
    return graph_traversal_tests;
}
