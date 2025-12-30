#include <stdio.h>
#include <stdlib.h>

int* readInput(int* size) {
    printf("Enter number of elements: ");
    scanf("%d", size);

    int* array = malloc((*size) * sizeof(int));
    if (!array) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter %d integers:\n", *size);
    for (int i = 0; i < *size; i++)
        scanf("%d", &array[i]);

    return array;
}

void displayArray(const char* message, int n, int* arr) {
    printf("%s", message);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void bubbleSort(int n, int* arr) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}