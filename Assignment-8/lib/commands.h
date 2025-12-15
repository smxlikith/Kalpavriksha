#ifndef COMMANDS_H
#define COMMANDS_H
#include "hashMap.h"

typedef struct {
    DoublyLinkedList** map;
    Queue* q;
    int capacity;
} LRUCache;

LRUCache* createCache(int capacity);
char* get(LRUCache* cache, int key);
void put(LRUCache* cache, int key, char* data);
void freeCache(LRUCache* cache);

#endif