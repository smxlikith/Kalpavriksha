#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../lib/ipcUtils.h"

void writeToFile(int* arr, int n) {
    FILE* file = fopen(FILE_NAME, "w");
    if (!file) {
        exit(0);
    }

    fprintf(file, "%d\n", n);

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

int* readFromFile(int* size) {
    FILE* file = fopen(FILE_NAME, "r");

    if (!file) {
        exit(0);
    }

    fscanf(file, "%d", size);

    int* array = malloc((*size) * sizeof(int));
    if (!array) {
        exit(0);
    }

    for (int i = 0; i < *size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);

    return array;
}

int main() {
    int n;

    sem_t* semP1Done = sem_open(SEM_P1_DONE, O_CREAT, 0666, 0);
    sem_t* semP2Done = sem_open(SEM_P2_DONE, O_CREAT, 0666, 0);

    if (semP1Done == SEM_FAILED || semP2Done == SEM_FAILED) {
        printf("sem_open");
        return 1;
    }

    int* arr = readInput(&n);
    displayArray("Before Sorting: ", n, arr);

    writeToFile(arr, n);
    free(arr);

    sem_post(semP1Done);

    sem_wait(semP2Done);

    arr = readFromFile(&n);
    displayArray("After Sorting: ", n, arr);
    free(arr);

    sem_close(semP1Done);
    sem_close(semP2Done);
    sem_unlink(SEM_P1_DONE);
    sem_unlink(SEM_P2_DONE);

    return 0;
}