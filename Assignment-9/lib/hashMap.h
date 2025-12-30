#ifndef HASH_MAP_H
#define HASH_MAP_H
#include "processTypes.h"
#define MAX_PID 100

typedef struct HashNode HashNode;

struct HashNode {
    PCB* process;
    HashNode* next;
};

typedef struct HashHead HashHead;

struct HashHead {
    HashNode* head;
    HashNode* tail;
};

typedef struct HashMap HashMap;

struct HashMap {
    HashHead** map;
};

HashMap* initHashMap();
void putToMap(int pid, PCB* process, HashMap* map);
PCB* getFromMap(int pid, HashMap* map);
void deleteFromMap(int pid, HashMap* map);
void freeMap(HashMap* map);

#endif