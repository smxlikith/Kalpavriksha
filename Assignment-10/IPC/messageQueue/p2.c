#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include "../../lib/ipcUtils.h"

typedef struct {
    long type;
    int data[MAX_SIZE];
} Message;

int main() {
    key_t key = ftok(FTOK_FILE, FTOK_ID);

    if (key == -1) {
        printf("Error: ftok");
        return 1;
    }

    int msgId = msgget(key, 0666);

    while ((msgId = msgget(key, 0666)) == -1) {
        sleep(1);
    }

    Message msg;

    msgrcv(msgId, &msg, sizeof(int), 1, 0);
    int n = msg.data[0];

    msgrcv(msgId, &msg, n * sizeof(int), 1, 0);

    bubbleSort(n, msg.data);

    msg.type = 2;
    msgsnd(msgId, &msg, n * sizeof(int), 0);

    return 0;
}