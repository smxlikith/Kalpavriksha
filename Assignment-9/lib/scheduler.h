#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "queue.h"

typedef struct {
    Queue* readyQueue;
    Queue* waitingQueue;
    Queue* terminatedQueue;
    KILLNode* killList;
    int timer;
    int currentProcessTimer;
    PCB* runningProcess;
} Scheduler;

Scheduler* initScheduler(int n, PCB** processes, KILLNode* killList);
void killProcess(Scheduler* scheduler);
void updateWaitingQueue(Scheduler* scheduler);
void freeScheduler(Scheduler* scheduler);

#endif