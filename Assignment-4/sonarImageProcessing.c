#include <stdio.h>
#include <stdlib.h>
#define MAX_VAL 255

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int** generateMatrix(int size) {
    int** matrix = calloc(size, sizeof(int*));

    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        exit(0);
    }

    for (int i = 0; i < size; i++) {
        *(matrix + i) = calloc(size, sizeof(int));

        if (matrix + i == NULL) {
            for (int k = 0; k > i; k++) {
                free(matrix + k);
            }
            printf("Memory allocation failed\n");
            exit(0);
        }

        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = rand() % (MAX_VAL + 1);
        }
    }
    return matrix;
}

void rotateMatrix(int size, int** matrix) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            swap(*(matrix + i) + j, *(matrix + j) + i);
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size / 2; j++) {
            swap(*(matrix + i) + j, *(matrix + i) + (size - j - 1));
        }
    }
}

int calculate3x3NeighborsAverage(int i, int j, int size, int** matrix) {
    int validNeighbors = 0;
    int currentSum = 0;
    for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (x >= 0 && y >= 0 && x < size && y < size) {
                currentSum += *(*(matrix + x) + y);
                validNeighbors++;
            }
        }
    }
    return currentSum / validNeighbors;
}

void applySmoothing(int size, int** matrix) {
    int* curr = calloc(size, sizeof(int));
    int* prev = calloc(size, sizeof(int));

    for (int i = 0; i <= size; i++) {
        for (int j = 0; j < size; j++) {
            *(prev + j) = *(curr + j);
            *(curr + j) = calculate3x3NeighborsAverage(i, j, size, matrix);
        }
        if (i >= 1) {
            for (int j = 0; j < size; j++) {
                *(*(matrix + (i - 1)) + j) = *(prev + j);
            }
        }
    }
}

void displayMatrix(int size, int** matrix) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d, ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

void cleanUp(int size, int** matrix) {
    for (int i = 0; i < size; i++) {
        free(*(matrix + i));
    }
    free(matrix);
}

int main() {
    int size;
    printf("Enter the Size of the matrix: ");
    scanf("%d", &size);

    int** matrix = generateMatrix(size);

    printf("Generated the matrix\n");
    displayMatrix(size, matrix);
    printf("\n");

    printf("rotating the matrix\n");
    rotateMatrix(size, matrix);
    displayMatrix(size, matrix);
    printf("\n");

    printf("smoothing the matrix:\n");
    applySmoothing(size, matrix);
    displayMatrix(size, matrix);

    cleanUp(size, matrix);
    return 0;
}
