#ifndef IPC_UTILS_H
#define IPC_UTILS_H
#define FILE_NAME "data.txt"

#define SEM_P1_DONE "/sem_p1_done"
#define SEM_P2_DONE "/sem_p2_done"

#define MAX_SIZE 1024
#define FTOK_FILE "mqfile"
#define FTOK_ID 65

#define SHM_KEY 12345

int* readInput(int* size);
void displayArray(const char* message, int n, int* arr);
void bubbleSort(int n, int* arr);

#endif