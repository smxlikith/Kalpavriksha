#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../lib/ipcUtils.h"

int main() {
    int n;

    read(STDIN_FILENO, &n, sizeof(int));

    int* arr = malloc(n * sizeof(int));
    if (!arr) {
        printf("Error: malloc\n");
        return 1;
    }

    read(STDIN_FILENO, arr, n * sizeof(int));

    bubbleSort(n, arr);

    write(STDOUT_FILENO, &n, sizeof(int));
    write(STDOUT_FILENO, arr, n * sizeof(int));

    free(arr);
    return 0;
}
