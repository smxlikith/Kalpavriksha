#include "hashMap.h"

#include <stdlib.h>

static int hash(int pid) {
    return pid % MAX_PID;
}

HashMap* initHashMap() {
    HashMap* map = malloc(sizeof(HashMap));
    map->map = calloc(MAX_PID, sizeof(HashHead*));
    return map;
}

void putToMap(int pid, PCB* process, HashMap* map) {
    int index = hash(pid);

    if (map->map[index] == NULL) {
        map->map[index] = malloc(sizeof(HashHead));
        map->map[index]->head = NULL;
        map->map[index]->tail = NULL;
    }

    HashNode* node = malloc(sizeof(HashNode));
    node->process = process;
    node->next = NULL;

    if (map->map[index]->tail == NULL) {
        map->map[index]->head = node;
        map->map[index]->tail = node;
    } else {
        map->map[index]->tail->next = node;
        map->map[index]->tail = node;
    }
}

PCB* getFromMap(int pid, HashMap* map) {
    int index = hash(pid);
    HashHead* bucket = map->map[index];

    if (bucket == NULL)
        return NULL;

    HashNode* curr = bucket->head;
    while (curr) {
        if (curr->process->PID == pid)
            return curr->process;
        curr = curr->next;
    }

    return NULL;
}

void deleteFromMap(int pid, HashMap* map) {
    int index = hash(pid);
    HashHead* bucket = map->map[index];

    if (bucket == NULL)
        return;

    HashNode* curr = bucket->head;
    HashNode* prev = NULL;

    while (curr) {
        if (curr->process->PID == pid) {
            if (prev == NULL)
                bucket->head = curr->next;
            else
                prev->next = curr->next;

            if (curr == bucket->tail)
                bucket->tail = prev;

            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void freeMap(HashMap* map) {
    for (int i = 0; i < MAX_PID; i++) {
        HashHead* bucket = map->map[i];
        if (bucket) {
            HashNode* curr = bucket->head;
            while (curr) {
                HashNode* temp = curr;
                curr = curr->next;
                free(temp);
            }
            free(bucket);
        }
    }
    free(map->map);
    free(map);
}