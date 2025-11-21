#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoublyLinkedList DoublyLinkedList;
struct DoublyLinkedList {
    int key;
    char* data;
    DoublyLinkedList* prev;
    DoublyLinkedList* next;
};

typedef struct {
    DoublyLinkedList* head;
    int capacity;
    int size;
} Queue;

Queue* initQueue(int capacity);
DoublyLinkedList* enqueue(Queue* q, DoublyLinkedList* node);
DoublyLinkedList* dequeue(Queue* q, DoublyLinkedList* node);
void freeQueue(Queue* q);

DoublyLinkedList* createNode(int key, const char* data);
DoublyLinkedList* modifyNode(DoublyLinkedList* node, int key, const char* data);

void display(Queue* q);

#endif