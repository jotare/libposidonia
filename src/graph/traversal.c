#include <stdlib.h>

#include "graph/traversal.h"

/** Non-recursive implementation of BFS algorithm */
list_t bfs(graph_t graph, vertex_t root) {
    list_t traversal;
    queue_t queue;
    set_t explored;

    list_init(&traversal, 0, LINKED_LIST);
    queue_init(&queue, 0, DYNAMIC_QUEUE);
    set_init(&explored, graph_size(graph), BIT_VECTOR_SET);

    list_append(traversal, root);
    queue_enqueue(queue, root);
    set_insert(explored, root);

    while (!queue_is_empty(queue)) {
        vertex_t v = queue_dequeue(queue);
        int n_neighbors = graph_neighbors_count(graph, v);
        vertex_t *neighbors = malloc(n_neighbors * sizeof(vertex_t));
        if (neighbors == NULL) {
            list_clear(traversal);
            return traversal;
        }
        graph_neighbors(graph, v, &neighbors);

        for (int i = 0; i < n_neighbors; i++) {
            vertex_t w = neighbors[i];
            if (!set_member(explored, w)) {
                list_append(traversal, w);
                queue_enqueue(queue, w);
                set_insert(explored, w);
            }
        }

        free(neighbors);
    }

    return traversal;
}

/** Non-recursive implementation of DFS algorithm */
list_t dfs(graph_t graph, vertex_t root) {
    list_t traversal;
    stack_t stack;
    set_t explored;

    list_init(&traversal, 0, LINKED_LIST);
    stack_init(&stack, 0, DYNAMIC_STACK);
    set_init(&explored, graph_size(graph), BIT_VECTOR_SET);

    stack_push(stack, root);

    while (!stack_is_empty(stack)) {
        vertex_t v = stack_pop(stack);
        if (!set_member(explored, v)) {
            list_append(traversal, v);
            set_insert(explored, v);

            int n_neighbors = graph_neighbors_count(graph, v);
            vertex_t *neighbors = malloc(n_neighbors * sizeof(vertex_t));
            if (neighbors == NULL) {
                list_clear(traversal);
                return traversal;
            }
            graph_neighbors(graph, v, &neighbors);

            for (int i = 0; i < n_neighbors; i++) {
                vertex_t w = neighbors[i];
                stack_push(stack, w);
            }

            free(neighbors);
        }
    }

    return traversal;
}
