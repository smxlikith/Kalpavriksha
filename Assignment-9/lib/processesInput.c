#include "processesInput.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getProcessInfo(int* n, PCB*** processes, KILLNode** killList) {
    int nProcesses, nKills;
    char line[256];

    printf("Enter number of processes: ");
    scanf("%d", &nProcesses);
    getchar();

    *n = nProcesses;
    *processes = malloc(nProcesses * sizeof(PCB*));

    for (int i = 0; i < nProcesses; i++) {
        char name[256];

        (*processes)[i] = malloc(sizeof(PCB));

        printf("Enter process info (name pid burst io_start io_duration):\n");
        fgets(line, sizeof(line), stdin);

        sscanf(line, "%s %d %d %d %d",
               name,
               &(*processes)[i]->PID,
               &(*processes)[i]->initialBurstTime,
               &(*processes)[i]->ioStart,
               &(*processes)[i]->ioDuration);

        (*processes)[i]->name = malloc(strlen(name) + 1);
        strcpy((*processes)[i]->name, name);

        if ((*processes)[i]->ioDuration == 0) {
            (*processes)[i]->ioDuration = -1;
        }

        (*processes)[i]->arrivalTime = 0;
        (*processes)[i]->firstRunTime = -1;
        (*processes)[i]->burstTime = (*processes)[i]->initialBurstTime;
        (*processes)[i]->totalIoTime = ((*processes)[i]->ioDuration == -1) ? 0 : (*processes)[i]->ioDuration;
        (*processes)[i]->status = STATUS_OK;
        (*processes)[i]->completionTime = 0;
    }

    printf("Enter number of kill commands: ");
    scanf("%d", &nKills);
    getchar();

    *killList = NULL;

    for (int i = 0; i < nKills; i++) {
        char cmd[16];
        int pid, killTime;

        printf("Enter kill command (KILL -PID kill_time):\n");
        fgets(line, sizeof(line), stdin);

        sscanf(line, "%s %d %d", cmd, &pid, &killTime);

        KILLNode* node = malloc(sizeof(KILLNode));
        node->pid = pid;
        node->time = killTime;
        node->next = NULL;

        if (*killList == NULL || killTime < (*killList)->time) {
            node->next = *killList;
            *killList = node;
        } else {
            KILLNode* temp = *killList;

            while (temp->next != NULL &&
                   temp->next->time <= killTime) {
                temp = temp->next;
            }

            node->next = temp->next;
            temp->next = node;
        }
    }
}