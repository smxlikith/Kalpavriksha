#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "queue.h"

#define MIN_CAPACITY 1
#define MAX_CAPACITY 1000

DoublyLinkedList** initHashMap();
void freeMap(DoublyLinkedList** map);

#endif