#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "../../lib/ipcUtils.h"

typedef struct {
    long type;
    int data[MAX_SIZE];
} Message;

int main() {
    int n;
    int* arr = readInput(&n);

    displayArray("Before Sorting: ", n, arr);

    key_t key = ftok(FTOK_FILE, FTOK_ID);

    if (key == -1) {
        printf("Error: ftok\n");
        exit(1);
    }

    int msgId = msgget(key, 0666 | IPC_CREAT);
    if (msgId == -1) {
        printf("Error: msgget\n");
        exit(1);
    }

    Message msg;

    msg.type = 1;
    msg.data[0] = n;
    msgsnd(msgId, &msg, sizeof(int), 0);

    memcpy(msg.data, arr, n * sizeof(int));
    msgsnd(msgId, &msg, n * sizeof(int), 0);

    free(arr);

    msgrcv(msgId, &msg, n * sizeof(int), 2, 0);

    displayArray("After Sorting: ", n, msg.data);

    msgctl(msgId, IPC_RMID, NULL);
    return 0;
}