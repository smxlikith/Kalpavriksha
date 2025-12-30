#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../lib/ipcUtils.h"

int* readFromFile(int* n) {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n);

    int* arr = malloc((*n) * sizeof(int));
    if (!arr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    return arr;
}

void writeToFile(int n, int* arr) {
    FILE* file = fopen(FILE_NAME, "w");
    fprintf(file, "%d\n", n);

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

int main() {
    int n;
    sem_t* semP1Done = sem_open(SEM_P1_DONE, 0);
    sem_t* semP2Done = sem_open(SEM_P2_DONE, 0);

    if (semP1Done == SEM_FAILED || semP2Done == SEM_FAILED) {
        printf("sem_open");
        return 1;
    }

    printf("p2: waiting for p1...\n");
    sem_wait(semP1Done);

    int* arr = readFromFile(&n);
    bubbleSort(n, arr);
    writeToFile(n, arr);
    free(arr);

    sem_post(semP2Done);

    sem_close(semP1Done);
    sem_close(semP2Done);

    return 0;
}