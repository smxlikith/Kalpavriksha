#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../../lib/ipcUtils.h"

int main() {
    int pipeToP2[2];
    int pipeToP1[2];

    if (pipe(pipeToP2) == -1 || pipe(pipeToP1) == -1) {
        printf("Error: pipe\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Error: fork\n");
        return 1;
    }

    if (pid == 0) {
        dup2(pipeToP2[0], STDIN_FILENO);
        dup2(pipeToP1[1], STDOUT_FILENO);

        close(pipeToP2[0]);
        close(pipeToP2[1]);
        close(pipeToP1[0]);
        close(pipeToP1[1]);

        execl("./out/p2", "p2", NULL);
        perror("execl");
        exit(1);
    }

    close(pipeToP2[0]);
    close(pipeToP1[1]);

    int n;
    int* arr = readInput(&n);

    displayArray("Before Sorting: ", n, arr);

    write(pipeToP2[1], &n, sizeof(int));
    write(pipeToP2[1], arr, n * sizeof(int));

    free(arr);

    read(pipeToP1[0], &n, sizeof(int));
    arr = malloc(n * sizeof(int));
    read(pipeToP1[0], arr, n * sizeof(int));

    displayArray("After Sorting: ", n, arr);

    free(arr);
    close(pipeToP2[1]);
    close(pipeToP1[0]);

    wait(NULL);
    return 0;
}