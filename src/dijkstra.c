#include "graph.h"
#include <time.h>

Graph test_case_2 = {
    .size = 5,
    .adjecency = {
        {0, 10, 0, 5, 0},
        {0,  0, 1, 2, 0},
        {0,  0, 0, 0, 4},
        {0,  3, 9, 0, 2},
        {7,  0, 6, 0, 0},
    }
};


int main() {
    clock_t start, end;
    double cpu_time_used;

    printf("--- Running Classic Dijkstra ---\n");
    start = clock();
    dijkstra(&test_case_2, 0);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Dijkstra (Classic) Time taken: %f us\n", cpu_time_used * 1e6);

    printf("\n\n--- Running Dijkstra with Working-Set Heap ---\n");
    start = clock();
    dijkstra_ws(&test_case_2, 0);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Dijkstra (WS Heap) Time taken: %f us\n", cpu_time_used * 1e6);

    return 0;
}
