#ifndef WORKINGSET_HEAP_H
#define WORKINGSET_HEAP_H

#include "minheap.h"
#include <stdlib.h>
#include "limits.h"

// We use 4 heaps. A real implementation would grow this list.
#define NUM_HEAPS 4
#define INF INT_MAX


typedef struct {
    MinHeap_TypeDef* heaps[NUM_HEAPS];
    int max_sizes[NUM_HEAPS];
} WorkingSetHeap_TypeDef;


/**
 * @brief Initialise the working-set heap
 */
void initWorkingSetHeap(WorkingSetHeap_TypeDef* wsHeap) {
    for (int i = 0; i < NUM_HEAPS; i++) {
        wsHeap->heaps[i] = (MinHeap_TypeDef*)malloc(sizeof(MinHeap_TypeDef));
        initMinHeap(wsHeap->heaps[i]);
    }
    
    // Max sizes: 2, 4, 16, 256 (doubly exponential 2^(2^i))
    // Capped by our MIN_HEAP_CAPACITY
    wsHeap->max_sizes[0] = 2;
    wsHeap->max_sizes[1] = 4;
    wsHeap->max_sizes[2] = 16;
    wsHeap->max_sizes[3] = 256; 
}

/**
 * @brief Check if all heaps are empty
 */
int isWsHeapEmpty(WorkingSetHeap_TypeDef* wsHeap) {
    for (int i = 0; i < NUM_HEAPS; i++) {
        if (!isMinHeapEmpty(wsHeap->heaps[i])) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Add an element to the working-set heap.
 * @details This is the "ripple-carry" insertion.
 * @return 0 if successful, -1 otherwise
 */
int wsHeapInsert(WorkingSetHeap_TypeDef* wsHeap, int item, int priority) {
    
    MinHeap_TypeDef* carryHeap = (MinHeap_TypeDef*)malloc(sizeof(MinHeap_TypeDef));
    if (carryHeap == NULL) return -1;
    
    initMinHeap(carryHeap);
    
    if (heapPush(carryHeap, item, priority) != 0) {
        free(carryHeap);
        return -1; 
    }

    for (int i = 0; i < NUM_HEAPS; i++) {
        if (wsHeap->heaps[i]->size + carryHeap->size <= wsHeap->max_sizes[i]) {
            
            if (heapMerge(wsHeap->heaps[i], carryHeap) != 0) {
                 printf("WS_HEAP MERGE FAILED!\n");
                 free(carryHeap);
                 return -1;
            }
            free(carryHeap);
            return 0; 
        } else {
            
            MinHeap_TypeDef* temp = wsHeap->heaps[i];
            wsHeap->heaps[i] = carryHeap;
            carryHeap = temp;
        }
    }
    
    printf("WS_HEAP OVERFLOW! FINAL CARRY FAILED.\n");
    free(carryHeap);
    return -1;
}

/**
 * @brief Remove the minimum element from the *entire* structure.
 * @return 0 if successful, -1 otherwise
 */
int wsHeapDeleteMin(WorkingSetHeap_TypeDef* wsHeap, HeapNode_TypeDef* minNode) {
    int bestPriority = INF;
    int bestHeapIndex = -1;

    // 1. Find which heap has the global minimum
    for (int i = 0; i < NUM_HEAPS; i++) {
        if (!isMinHeapEmpty(wsHeap->heaps[i])) {
            HeapNode_TypeDef currentMin;
            heapPeekMin(wsHeap->heaps[i], &currentMin);
            
            if (currentMin.priority < bestPriority) {
                bestPriority = currentMin.priority;
                bestHeapIndex = i;
            }
        }
    }
    
    if (bestHeapIndex == -1) {
        printf("WS_HEAP UNDERFLOW!\n");
        return -1;
    }
    
    // 2. Pop the item from *only that heap*
    // This is the key: the cost is O(log(size of H_i)),
    // not O(log(Total N)).
    return heapPopMin(wsHeap->heaps[bestHeapIndex], minNode);
}


#endif // WORKINGSET_HEAP_H
