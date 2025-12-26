#include "queue.h"

ProcessNode* createProcessNode(PCB* process) {
    ProcessNode* node = malloc(sizeof(ProcessNode));

    if (node == NULL) {
        printf("Unable to allocate memory, try again later...\n");
        exit(0);
    }

    node->process = process;
    node->next = NULL;
    return node;
}

Queue* initQueue() {
    Queue* queue = malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Unable to allocate memory, try again later...\n");
        exit(0);
    }
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void enqueue(Queue* queue, PCB* process) {
    ProcessNode* node = createProcessNode(process);
    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

PCB* dequeue(Queue* queue) {
    if (queue->head != NULL) {
        ProcessNode* head = queue->head;
        PCB* process = head->process;
        queue->head = head->next;

        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        free(head);
        return process;
    }
    return NULL;
}

void freeQueue(Queue* queue) {
    ProcessNode* head = queue->head;
    if (head == NULL) {
        return;
    }
    do {
        ProcessNode* next = head->next;
        free(head);
        head = next;
    } while (head != NULL);
    free(queue);
}
