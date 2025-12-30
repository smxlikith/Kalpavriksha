#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "../../lib/ipcUtils.h"

int main() {
    int n;
    int* arr = readInput(&n);

    displayArray("Before Sorting: ", n, arr);

    int shmId = shmget(SHM_KEY, sizeof(int) * (n + 1), 0666 | IPC_CREAT);
    if (shmId == -1) {
        printf("Error: shmget\n");
        exit(1);
    }

    int* shm = (int*)shmat(shmId, NULL, 0);
    if (shm == (void*)-1) {
        printf("Error: shmat\n");
        exit(1);
    }

    sem_t* semP1Done = sem_open(SEM_P1_DONE, O_CREAT, 0666, 0);
    sem_t* semP2Done = sem_open(SEM_P2_DONE, O_CREAT, 0666, 0);

    if (semP1Done == SEM_FAILED || semP2Done == SEM_FAILED) {
        printf("Error: sem_open\n");
        exit(1);
    }

    shm[0] = n;
    memcpy(&shm[1], arr, n * sizeof(int));
    free(arr);

    sem_post(semP1Done);

    sem_wait(semP2Done);

    n = shm[0];
    arr = malloc(n * sizeof(int));
    memcpy(arr, &shm[1], n * sizeof(int));

    displayArray("After Sorting: ", n, arr);

    free(arr);
    shmdt(shm);
    shmctl(shmId, IPC_RMID, NULL);

    sem_close(semP1Done);
    sem_close(semP2Done);
    sem_unlink(SEM_P1_DONE);
    sem_unlink(SEM_P2_DONE);

    return 0;
}