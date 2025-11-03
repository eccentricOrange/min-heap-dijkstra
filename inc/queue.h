#include <stdio.h>
#include <stdlib.h>

#define QUEUE_LENGTH 20

typedef struct {
    int data[QUEUE_LENGTH];
    int front;
    int rear;
} Queue_TypeDef;

/**
 * @brief Initialise the queue
 * @details Set both pointers to -1.
 */
void initQueue(Queue_TypeDef* queue) {
    queue->front = -1;
    queue->rear = -1;
}

/**
 * @brief Check if queue is empty
 * @param queue Pointer to the Queue
 * @return 1 if empty, 0 if not empty
 */
int isQueueEmpty(Queue_TypeDef* queue) {
    if (queue->front == -1 || queue->front > queue->rear) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Check if queue is full
 * @param queue Pointer to the Queue
 * @return 1 if full, 0 if not full
 */
int isQueueFull(Queue_TypeDef* queue) {
    if (queue->rear >= QUEUE_LENGTH - 1) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Attempt to add an element to the queue.
 * @param queue Pointer to the Queue.
 * @param element Data to be added.
 * @return 0 if successful, -1 otherwise
 */
int enqueue(Queue_TypeDef* queue, int element) {

    if (isQueueFull(queue)) {
        printf("QUEUE OVERFLOW!\n");
        return -1;
    }

    // printf("Enqueuing %d.\n", element);

    if (queue->front == -1 && queue->rear == -1) {
        queue->front = 0;
        queue->rear = 0;
        queue->data[0] = element;
        return 0;
    }


    queue->rear++;
    queue->data[queue->rear] = element;
    return 0;
    
}

/**
 * @brief Attempt to remove an element from the queue.
 * @param queue Pointer to the Queue.
 * @param element Pointer to the data to be removed.
 * @return 0 if successful, -1 otherwise
 */
int dequeue(Queue_TypeDef* queue, int* element) {

    if (isQueueEmpty(queue)) {
        printf("QUEUE UNDERFLOW!\n");
        return -1;
    }

    if (queue->front == queue->rear) {
        *element = queue->data[queue->front];
        // printf("Dequeued %d.\n", *element);
        initQueue(queue);
        return 0;
    }

    *element = queue->data[queue->front++];
    // printf("Dequeued %d.\n", *element);
    return 0;
}

/**
 * @brief Get the number of elements currently in the queue
 * @param queue Pointer to the Queue.
 * @return The number of elements.
 */
int getNumberOfElements(Queue_TypeDef* queue) {
    
    if (isQueueEmpty(queue)) {
        return 0;
    }

    return (queue->rear - queue->front) + 1;
    
}

/**
 * @brief Print out all elements in the queue.
 * @param queue Pointer to the Queue.
 * @return 0 if successful (queu had elements), -1 otherwise (queue was empty)
 */
int printQueue(Queue_TypeDef* queue) {

    if (isQueueEmpty(queue)) {
        printf("QUEUE EMPTY!\n");
        return -1;
    }

    printf("\n[Length %d] QUEUE:\n", getNumberOfElements(queue));

    for (int i = queue->front; i < queue->rear + 1; i++) {
        printf("\t[%d] %d\n", i, queue->data[i]);
    }

    printf("\n");
    return 0;

}