#include "hashMap.h"

DoublyLinkedList** initHashMap() {
    DoublyLinkedList** map = malloc(MAX_CAPACITY * sizeof(DoublyLinkedList*));
    if (map == NULL) {
        printf("Unable to Allocate Memory, Try again Later...");
        return NULL;
    }

    for (int i = 0; i < MAX_CAPACITY; i++) {
        map[i] = NULL;
    }

    return map;
}

void freeMap(DoublyLinkedList** map) {
    free(map);
}