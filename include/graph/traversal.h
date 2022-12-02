/**
 * @file traversal.h
 * @brief Graph traversal algorithms
 */
#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "libds.h"

/** Breadth-first search graph traversal algorithm */
list_t bfs(graph_t graph, vertex_t root);

/** Depth-first search graph traversal algorithm */
list_t dfs(graph_t graph, vertex_t root);

#endif /* TRAVERSAL_H */
