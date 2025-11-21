#include "commands.h"

LRUCache* createCache(int capacity) {
    if (capacity < MIN_CAPACITY || capacity > MAX_CAPACITY) {
        printf("Capacity out of bounds. Capacity should be in [%d, %d], but got %d.\n",
               MIN_CAPACITY, MAX_CAPACITY, capacity);
        return NULL;
    }

    LRUCache* cache = malloc(sizeof(LRUCache));
    if (cache == NULL) {
        printf("Cannot allocate Memory, try again later...");
        return NULL;
    }

    cache->map = initHashMap();
    cache->q = initQueue(capacity);
    cache->capacity = capacity;

    if (cache->map == NULL || cache->q == NULL) {
        return NULL;
    }

    return cache;
}

char* get(LRUCache* cache, int key) {
    DoublyLinkedList* node = dequeue(cache->q, cache->map[key]);
    if (node == NULL) return "NULL";
    node = enqueue(cache->q, node);
    return node->data;
}

void put(LRUCache* cache, int key, char* data) {
    DoublyLinkedList* node;
    if (cache->map[key] == NULL) {
        node = createNode(key, data);
        cache->map[key] = node;

        if (cache->q->capacity == cache->q->size) {
            DoublyLinkedList* tail = cache->q->head->prev;
            cache->map[tail->key] = NULL;
        }

        enqueue(cache->q, node);
    } else {
        node = dequeue(cache->q, cache->map[key]);
        modifyNode(node, key, data);
        enqueue(cache->q, node);
    }
}

void freeCache(LRUCache* cache) {
    if (cache == NULL) return;
    freeQueue(cache->q);
    freeMap(cache->map);
    free(cache);
}