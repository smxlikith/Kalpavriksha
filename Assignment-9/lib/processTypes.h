
#ifndef PROCESS_TYPES_H
#define PROCESS_TYPES_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    STATUS_OK,
    STATUS_KILLED
} ProcessStatus;

typedef struct {
    int PID;
    char* name;
    int arivalTime;
    int initialBurstTime;
    int burstTime;
    int ioStart;
    int ioDuration;
    int totalIoTime;
    int arrivalTime;
    int firstRunTime;
    int completionTime;
    ProcessStatus status;
} PCB;

typedef struct ProcessNode ProcessNode;

struct ProcessNode {
    PCB* process;
    ProcessNode* next;
};

typedef struct KILLNode KILLNode;

struct KILLNode {
    int pid;
    int time;
    KILLNode* next;
};

#endif