#include "memBlock.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Block* createBlock(int index, char* data, Block* prev, Block* next) {
    Block* b = malloc(sizeof(Block));
    if (b == NULL) return NULL;
    b->prev = NULL;
    b->next = NULL;
    b->currSize = 0;
    b->data = data;
    b->index = index;
    if (b->data == NULL) return NULL;
    return b;
}

char** initVirtualDisk(int numberOfBlocks) {
    char** memory = malloc(sizeof(char*) * numberOfBlocks);
    if (memory == NULL) {
        return NULL;
    }
    for (int i = 0; i < numberOfBlocks; i++) {
        memory[i] = malloc(BLOCK_SIZE);
        if (memory[i] == NULL) {
            return NULL;
        }
    }
    return memory;
}

Block* initMemoryBlocks(int numberOfBlocks, char** memoryBlocks) {
    Block* head = NULL;
    Block* curr = NULL;
    Block* prev = head;
    for (int i = 0; i < numberOfBlocks; i++) {
        if (head == NULL) {
            head = createBlock(i, memoryBlocks[i], prev, NULL);
            if (head == NULL) {
                return NULL;
            }
            prev = head;
            continue;
        }
        curr = createBlock(i, memoryBlocks[i], prev, NULL);
        if (curr == NULL) {
            return NULL;
        }
        curr->prev = prev;
        prev->next = curr;
        prev = curr;
    }
    prev->next = head;
    head->prev = prev;
    return head;
}

void display(Block* head) {
    if (head == NULL) return;
    Block* curr = head;
    do {
        printf("%p, %p(%d), %p\n", curr->prev, curr, curr->index, curr->next);
        curr = curr->next;
    } while (curr != head);
}

Block* allocateBlocks(Block** freeBlocksList, unsigned int size) {
    int numberOfBlocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    Block *head = *freeBlocksList, *curr = head, *tail;

    if (numberOfBlocks == 1 && curr == curr->next) {
        *freeBlocksList = NULL;
        return curr;
    }

    while (numberOfBlocks-- && curr != curr->next) {
        curr = curr->next;
        if (curr == head) {
            break;
        }
    }

    if (numberOfBlocks > 0) {
        return NULL;
    }

    tail = curr->prev;
    tail->next = head;

    curr->prev = head->prev;
    head->prev->next = curr;

    head->prev = tail;

    if (*freeBlocksList == curr) {
        *freeBlocksList = NULL;
    } else {
        *freeBlocksList = curr;
    }
    return head;
}

void deallocateBlocks(Block** freeBlocksList, Block* allocatedBlocks) {
    if (allocatedBlocks == NULL) {
        return;
    }
    if (*freeBlocksList == NULL) {
        *freeBlocksList = allocatedBlocks;
        return;
    }

    Block *curr, *head = allocatedBlocks, *tail = allocatedBlocks->prev;

    curr = head;
    do {
        curr->currSize = 0;
    } while (curr != head);

    curr = *freeBlocksList;
    head->prev = curr->prev;
    curr->prev->next = head;

    curr->prev = tail;
    tail->next = curr;

    *freeBlocksList = head;
}

void freeBlocks(Block* head) {
    Block* curr = head;
    do {
        free(curr->data);
        curr = curr->next;
        free(curr->prev);
    } while (curr->next != head);
    free(curr->data);
    free(curr);
}
