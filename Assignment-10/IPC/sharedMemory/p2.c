
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "../../lib/ipcUtils.h"

int main() {
    sem_t* semP1Done = sem_open(SEM_P1_DONE, 0);
    sem_t* semP2Done = sem_open(SEM_P2_DONE, 0);

    while ((semP1Done = sem_open(SEM_P1_DONE, 0)) == SEM_FAILED) {
        sleep(1);
    }

    while ((semP2Done = sem_open(SEM_P2_DONE, 0)) == SEM_FAILED) {
        sleep(1);
    }

    sem_wait(semP1Done);

    int shmId = shmget(SHM_KEY, 0, 0666);
    if (shmId == -1) {
        printf("Error: shmget\n");
        return 1;
    }

    int* shm = (int*)shmat(shmId, NULL, 0);
    if (shm == (void*)-1) {
        printf("Error: shmat\n");
        return 1;
    }

    int n = shm[0];
    bubbleSort(n, &shm[1]);

    sem_post(semP2Done);

    shmdt(shm);
    sem_close(semP1Done);
    sem_close(semP2Done);

    return 0;
}