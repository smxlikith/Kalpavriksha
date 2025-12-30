#ifndef QUEUE_H
#define QUEUE_H
#include "processTypes.h"

typedef struct {
    ProcessNode* head;
    ProcessNode* tail;
} Queue;

Queue* initQueue();
void enqueue(Queue* queue, PCB* process);
PCB* dequeue(Queue* queue);
void freeQueue(Queue* queue);

#endif