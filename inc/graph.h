#include <stdio.h>
#include <stdlib.h>
#include "limits.h"
#include "queue.h"
#include "workingset_heap.h"

#define MAX_GRAPH_SIZE 20

typedef struct {
    int adjecency[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
    int size;
    int visited[MAX_GRAPH_SIZE];
} Graph;

void dijkstra(Graph* graph, int start) {
    int distance[MAX_GRAPH_SIZE];
    int visited[MAX_GRAPH_SIZE];
    int count, min, u, v;

    for (int i = 0; i < graph->size; i++) {
        distance[i] = INF;
        visited[i] = 0;
    }

    distance[start] = 0;

    for (count = 0; count < graph->size; count++) {
        
        min = INF;
        u = -1;

        for (int i = 0; i < graph->size; i++) {
            if (!visited[i] && distance[i] < min) {
                min = distance[i];
                u = i;
            }
        }

        if (u == -1) {
            break;
        }
        
        visited[u] = 1;

        for (v = 0; v < graph->size; v++) {
            int weight = graph->adjecency[u][v];
            if (weight > 0 && weight != INF && !visited[v]) {
                 if (distance[u] + weight < distance[v]) {
                     distance[v] = distance[u] + weight;
                 }
            }
        }
    }

    printf("\nShortest distance from vertex %d:\n", start);

    for (int i = 0; i < graph->size; i++) {
        if (distance[i] == INF) {
            printf("%d -> %d = No Path\n", start, i);
        } else {
            printf("%d -> %d = %d\n", start, i, distance[i]);
        }
    }
}

/**
 * @brief Run Dijkstra's using the working-set heap
 */
void dijkstra_ws(Graph* graph, int start) {
    WorkingSetHeap_TypeDef wsHeap;
    initWorkingSetHeap(&wsHeap);
    
    int distance[MAX_GRAPH_SIZE];
    for (int i = 0; i < graph->size; i++) {
        distance[i] = INF;
    }

    distance[start] = 0;
    wsHeapInsert(&wsHeap, start, 0);

    HeapNode_TypeDef u_node;
    
    while (!isWsHeapEmpty(&wsHeap)) {
        
        if (wsHeapDeleteMin(&wsHeap, &u_node) != 0) {
            break; 
        }
        
        int u = u_node.item;
        
        if (u_node.priority > distance[u]) {
            continue;
        }
        
        for (int v = 0; v < graph->size; v++) {
            int weight = graph->adjecency[u][v];
            
            if (weight > 0 && weight != INF) {
                int newDist = distance[u] + weight;
                
                if (newDist < distance[v]) {
                    distance[v] = newDist;
                    wsHeapInsert(&wsHeap, v, newDist);
                }
            }
        }
    }
    
    printf("\nDijkstra's results starting from %d:\n", start);
    for (int i = 0; i < graph->size; i++) {
        if (distance[i] == INF) {
            printf("%d -> %d = No Path\n", start, i);
        } else {
            printf("%d -> %d = %d\n", start, i, distance[i]);
        }
    }
}
