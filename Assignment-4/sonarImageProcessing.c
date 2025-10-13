#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int** generateMatrix(int size) {
    int** matrix = calloc(size, sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = calloc(size, sizeof(int));
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 256;
        }
    }
    return matrix;
}

void rotateMatrix(int size, int** matrix) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            swap(&matrix[i][j], &matrix[j][i]);
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size / 2; j++) {
            swap(&matrix[i][j], &matrix[i][size - j - 1]);
        }
    }
}

int smoothing3x3(int i, int j, int size, int** matrix) {
    int validNeighbors = 0;
    int currentSum = 0;
    for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (x >= 0 && y >= 0 && x < size && y < size) {
                currentSum += matrix[x][y];
                validNeighbors++;
            }
        }
    }
    return currentSum / validNeighbors;
}

int** applySmoothing(int size, int** matrix) {
    int** smoothedMatrix = calloc(size, sizeof(int*));

    for (int i = 0; i < size; i++) {
        smoothedMatrix[i] = calloc(size, sizeof(int));
        for (int j = 0; j < size; j++) {
            smoothedMatrix[i][j] = smoothing3x3(i, j, size, matrix);
        }
    }
    return smoothedMatrix;
}

void display(int size, int** matrix) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d, ", matrix[i][j]);
        }
        printf("\n");
    }
}

void cleanUp(int size, int** matrix) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int size;
    printf("Enter the Size of the matrix: ");
    scanf("%d", &size);

    int** matrix = generateMatrix(size);

    printf("Generated the matrix\n");
    display(size, matrix);
    printf("\n");

    printf("rotating the matrix\n");
    rotateMatrix(size, matrix);
    display(size, matrix);
    printf("\n");

    printf("smoothing the matrix\n");
    int** smoothedMatrix = applySmoothing(size, matrix);
    display(size, smoothedMatrix);

    cleanUp(size, smoothedMatrix);
    cleanUp(size, matrix);
    return 0;
}
