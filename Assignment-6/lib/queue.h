#ifndef QUEUE_H
#define QUEUE_H
#include "fileSystem.h"

typedef struct {
    FileNode** queue;
    int maxSize;
    int currSize;
    int front;
    int back;
} Queue;

Queue* initQueue(int size);
Queue* resizeQueue(Queue* q, int size);
void enqueueQueue(Queue* q, FileNode* node);
FileNode* dequeueQueue(Queue* q);
void freeQueue(Queue* q);

#endif