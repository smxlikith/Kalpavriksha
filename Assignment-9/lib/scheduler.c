#include "scheduler.h"

Scheduler* initScheduler(int n, PCB** processes, KILLNode* killList) {
    Scheduler* scheduler = (Scheduler*)malloc(sizeof(Scheduler));

    scheduler->readyQueue = initQueue();
    scheduler->waitingQueue = initQueue();
    scheduler->terminatedQueue = initQueue();
    scheduler->processesMap = initHashMap();

    scheduler->killList = killList;
    scheduler->timer = 0;
    scheduler->currentProcessTimer = 0;
    scheduler->runningProcess = NULL;

    for (int i = 0; i < n; i++) {
        enqueue(scheduler->readyQueue, processes[i]);
        putToMap(processes[i]->PID, processes[i], scheduler->processesMap);
    }

    return scheduler;
}

void killProcess(Scheduler* scheduler) {
    if (scheduler == NULL || scheduler->killList == NULL) {
        return;
    }

    int pid = scheduler->killList->pid;

    PCB* target = getFromMap(pid, scheduler->processesMap);
    if (target == NULL) {
        KILLNode* temp = scheduler->killList;
        scheduler->killList = scheduler->killList->next;
        free(temp);
        return;
    }

    if (scheduler->runningProcess &&
        scheduler->runningProcess->PID == pid) {
        scheduler->runningProcess->completionTime = scheduler->timer;
        scheduler->runningProcess->status = STATUS_KILLED;
        enqueue(scheduler->terminatedQueue, scheduler->runningProcess);
        scheduler->runningProcess = NULL;
    } else {
        ProcessNode* prev = NULL;
        ProcessNode* curr = scheduler->readyQueue->head;

        while (curr != NULL) {
            if (curr->process->PID == pid) {
                if (prev == NULL) {
                    scheduler->readyQueue->head = curr->next;
                } else {
                    prev->next = curr->next;
                }

                if (curr == scheduler->readyQueue->tail) {
                    scheduler->readyQueue->tail = prev;
                }

                curr->process->status = STATUS_KILLED;
                curr->process->completionTime = scheduler->timer;

                enqueue(scheduler->terminatedQueue, curr->process);
                free(curr);
                break;
            }

            prev = curr;
            curr = curr->next;
        }

        prev = NULL;
        curr = scheduler->waitingQueue->head;

        while (curr != NULL) {
            if (curr->process->PID == pid) {
                if (prev == NULL) {
                    scheduler->waitingQueue->head = curr->next;
                } else {
                    prev->next = curr->next;
                }

                if (curr == scheduler->waitingQueue->tail) {
                    scheduler->waitingQueue->tail = prev;
                }

                curr->process->status = STATUS_KILLED;
                curr->process->completionTime = scheduler->timer;

                enqueue(scheduler->terminatedQueue, curr->process);
                free(curr);
                break;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    deleteFromMap(pid, scheduler->processesMap);

    KILLNode* temp = scheduler->killList;
    scheduler->killList = scheduler->killList->next;
    free(temp);
}

void updateWaitingQueue(Scheduler* scheduler) {
    ProcessNode* prev = NULL;
    ProcessNode* curr = scheduler->waitingQueue->head;

    while (curr != NULL) {
        curr->process->ioDuration--;

        if (curr->process->ioDuration == 0) {
            enqueue(scheduler->readyQueue, curr->process);

            if (prev == NULL)
                scheduler->waitingQueue->head = curr->next;
            else
                prev->next = curr->next;

            if (curr == scheduler->waitingQueue->tail)
                scheduler->waitingQueue->tail = prev;

            ProcessNode* temp = curr;
            curr = curr->next;
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void freeScheduler(Scheduler* scheduler) {
    if (scheduler == NULL) {
        return;
    }

    freeQueue(scheduler->readyQueue);
    freeQueue(scheduler->waitingQueue);
    freeQueue(scheduler->terminatedQueue);
    freeMap(scheduler->processesMap);

    KILLNode* temp;
    while (scheduler->killList != NULL) {
        temp = scheduler->killList;
        scheduler->killList = scheduler->killList->next;
        free(temp);
    }

    free(scheduler);
}