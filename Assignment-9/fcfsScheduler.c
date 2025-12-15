#include <unistd.h>

#include "lib/processesInput.h"
#include "lib/scheduler.h"

void runFCFS(Scheduler* scheduler) {
    while (1) {
        if (scheduler->killList && scheduler->killList->time == scheduler->timer) {
            killProcess(scheduler);
        }

        if (scheduler->runningProcess == NULL) {
            scheduler->runningProcess = dequeue(scheduler->readyQueue);
            scheduler->currentProcessTimer = 0;

            if (scheduler->runningProcess && scheduler->runningProcess->firstRunTime == -1) {
                scheduler->runningProcess->firstRunTime = scheduler->timer;
                printf("\nwait: %d\t %d\n", scheduler->runningProcess->firstRunTime, scheduler->timer);
            }
        }

        if (scheduler->runningProcess != NULL) {
            scheduler->runningProcess->burstTime--;
            scheduler->currentProcessTimer++;

            if (scheduler->runningProcess->ioDuration > 0 && scheduler->currentProcessTimer == scheduler->runningProcess->ioStart) {
                enqueue(scheduler->waitingQueue, scheduler->runningProcess);

                scheduler->runningProcess = NULL;
            }

            else if (scheduler->runningProcess->burstTime == 0) {
                scheduler->runningProcess->completionTime = scheduler->timer + 1;
                enqueue(scheduler->terminatedQueue, scheduler->runningProcess);
                scheduler->runningProcess = NULL;
            }
        }

        if (scheduler->runningProcess == NULL && scheduler->readyQueue->head == NULL && scheduler->waitingQueue->head == NULL) {
            break;
        }

        updateWaitingQueue(scheduler);

        sleep(1);
        scheduler->timer++;
    }
}

void displayResults(int n, PCB** processes) {
    printf("\n%-5s %-10s %-5s %-5s %-12s %-12s %-8s\n",
           "PID", "Name", "CPU", "IO", "Status", "Turnaround", "Waiting");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        PCB* p = processes[i];
        int turnaround = p->completionTime;
        int waiting = p->firstRunTime;
        if (p->status == STATUS_OK) {
            printf("%-5d %-10s %-5d %-5d %-12s %-12d %-8d\n", p->PID, p->name, p->initialBurstTime, p->totalIoTime, "OK", turnaround, waiting);
        } else {
            printf("%-5d %-10s %-5d %-5d KILLED at %-4d %-12s %-8s\n", p->PID, p->name, p->initialBurstTime, p->totalIoTime, p->completionTime, "-", "-");
        }
    }
}

int main() {
    int n;
    PCB** processes = NULL;
    KILLNode* killList = NULL;
    getProcessInfo(&n, &processes, &killList);

    Scheduler* scheduler = initScheduler(n, processes, killList);

    runFCFS(scheduler);

    displayResults(n, processes);
    freeScheduler(scheduler);

    for (int i = 0; i < n; i++) {
        free(processes[i]->name);
        free(processes[i]);
    }
    free(processes);

    return 0;
}