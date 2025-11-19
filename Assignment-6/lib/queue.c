#include "queue.h"

Queue* initQueue(int size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    q->queue = (FileNode**)malloc(sizeof(FileNode*) * size);
    if (!q->queue) {
        printf("Memory allocation failed!\n");
        free(q);
        return NULL;
    }
    q->currSize = 0;
    q->maxSize = size;
    q->front = 0;
    q->back = 0;
    return q;
}

Queue* resizeQueue(Queue* q, int newSize) {
    if (!q) {
        printf("Queue is not initialized!\n");
        return NULL;
    }

    FileNode** newQueue = (FileNode**)realloc(q->queue, sizeof(FileNode*) * newSize);
    if (!newQueue) {
        printf("Memory allocation failed during resize!\n");
        return NULL;
    }

    q->queue = newQueue;
    q->maxSize = newSize;
    return q;
}

void enqueueQueue(Queue* q, FileNode* node) {
    if (q->currSize == q->maxSize) {
        q = resizeQueue(q, q->maxSize * 2);
        if (!q) {
            printf("Failed to resize queue!\n");
            return;
        }
    }

    q->queue[q->back] = node;
    q->back = (q->back + 1) % q->maxSize;
    q->currSize++;
}

FileNode* dequeueQueue(Queue* q) {
    if (q->currSize == 0) {
        printf("Queue is empty!\n");
        return NULL;
    }

    FileNode* node = q->queue[q->front];
    q->front = (q->front + 1) % q->maxSize;
    q->currSize--;
    return node;
}

void freeQueue(Queue* q) {
    if (q) {
        if (q->queue) {
            free(q->queue);
        }
        free(q);
    }
}