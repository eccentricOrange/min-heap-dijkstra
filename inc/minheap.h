#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdio.h>
#include <stdlib.h>

#define MIN_HEAP_CAPACITY 256 // Max size for any single heap

typedef struct {
    int item;
    int priority;
} HeapNode_TypeDef;

typedef struct {
    HeapNode_TypeDef nodes[MIN_HEAP_CAPACITY];
    int size;
} MinHeap_TypeDef;

/**
 * @brief Initialise the min-heap
 */
void initMinHeap(MinHeap_TypeDef* h) {
    h->size = 0;
}

/**
 * @brief Check if heap is empty
 */
int isMinHeapEmpty(MinHeap_TypeDef* h) {
    return h->size == 0;
}

/**
 * @brief Check if heap is full
 */
int isMinHeapFull(MinHeap_TypeDef* h) {
    return h->size >= MIN_HEAP_CAPACITY;
}

/**
 * @brief Swap two heap nodes
 */
void heapSwap(HeapNode_TypeDef* a, HeapNode_TypeDef* b) {
    HeapNode_TypeDef temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Helper to maintain heap property after insertion
 */
void heapifyUp(MinHeap_TypeDef* h, int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    
    if (h->nodes[index].priority < h->nodes[parent].priority) {
        heapSwap(&h->nodes[index], &h->nodes[parent]);
        heapifyUp(h, parent);
    }
}

/**
 * @brief Helper to maintain heap property after deletion
 */
void heapifyDown(MinHeap_TypeDef* h, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < h->size && h->nodes[left].priority < h->nodes[smallest].priority) {
        smallest = left;
    }
    if (right < h->size && h->nodes[right].priority < h->nodes[smallest].priority) {
        smallest = right;
    }

    if (smallest != index) {
        heapSwap(&h->nodes[index], &h->nodes[smallest]);
        heapifyDown(h, smallest);
    }
}

/**
 * @brief Add an element to the min-heap.
 * @return 0 if successful, -1 otherwise
 */
int heapPush(MinHeap_TypeDef* h, int item, int priority) {
    if (isMinHeapFull(h)) {
        printf("MIN_HEAP OVERFLOW!\n");
        return -1;
    }
    
    HeapNode_TypeDef node = {item, priority};
    h->nodes[h->size] = node;
    heapifyUp(h, h->size);
    h->size++;
    return 0;
}

/**
 * @brief Remove the minimum element from the heap.
 * @return 0 if successful, -1 otherwise
 */
int heapPopMin(MinHeap_TypeDef* h, HeapNode_TypeDef* minNode) {
    if (isMinHeapEmpty(h)) {
        printf("MIN_HEAP UNDERFLOW!\n");
        return -1;
    }
    
    *minNode = h->nodes[0];
    h->nodes[0] = h->nodes[h->size - 1];
    h->size--;
    
    heapifyDown(h, 0);
    return 0;
}

/**
 * @brief Get the minimum element without removing it.
 * @return 0 if successful, -1 otherwise
 */
int heapPeekMin(MinHeap_TypeDef* h, HeapNode_TypeDef* minNode) {
    if (isMinHeapEmpty(h)) {
        return -1;
    }
    *minNode = h->nodes[0];
    return 0;
}

/**
 * @brief Merge h_src into h_dest.
 * @details This is a simple, inefficient merge for demonstration.
 * @return 0 if successful, -1 if h_dest would overflow
 */
int heapMerge(MinHeap_TypeDef* h_dest, MinHeap_TypeDef* h_src) {
    if (h_dest->size + h_src->size > MIN_HEAP_CAPACITY) {
        printf("MIN_HEAP MERGE OVERFLOW!\n");
        return -1;
    }
    
    for (int i = 0; i < h_src->size; i++) {
        h_dest->nodes[h_dest->size + i] = h_src->nodes[i];
    }
    h_dest->size += h_src->size;
    
    // Re-heapify the destination heap (inefficient, but simple)
    // A better heap (Fibonacci) would do this in O(1).
    for (int i = (h_dest->size / 2) - 1; i >= 0; i--) {
        heapifyDown(h_dest, i);
    }
    
    initMinHeap(h_src); // Empty the source
    return 0;
}

#endif // MINHEAP_H
