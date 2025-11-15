#include "performanceAnalyzer.h"

Heap* initHeap(Team** teams, Role role) {
    Heap* heap = malloc(sizeof(Heap));
    Player** players = malloc(teamCount * sizeof(Player*));

    heap->heap = players;
    heap->size = teamCount;

    for (int i = 0; i < teamCount; i++) {
        players[i] = teams[i]->Players[role];
    }

    heapify(heap);
    return heap;
}

void heapify(Heap* heap) {
    int size = heap->size;
    Player** players = heap->heap;

    for (int i = size / 2 - 1; i >= 0; i--) {
        int k = i;
        Player* curr = players[k];
        bool isHeap = false;
        while (!isHeap && (2 * k + 1) < size) {
            int j = 2 * k + 1;
            if (j + 1 < size && players[j]->performanceIndex < players[j + 1]->performanceIndex) {
                j = j + 1;
            }

            if (curr->performanceIndex >= players[j]->performanceIndex) {
                isHeap = true;
            } else {
                players[k] = players[j];
                k = j;
            }
        }
        players[k] = curr;
    }
    heap->heap = players;
}

Player* push(Heap* heap, Player* player) {
    Player** players = heap->heap;
    int size = heap->size;

    if (size == teamCount) {
        printf("HEAP IS FULL, cannot Push a new Player.\n");
        return NULL;
    }

    players[size] = player;
    size += 1;

    int k = heap->size;
    while (k > 0) {
        int parentIdx = (k - 1) / 2;
        if (players[k]->performanceIndex > players[parentIdx]->performanceIndex) {
            Player* temp = players[k];
            players[k] = players[parentIdx];
            players[parentIdx] = temp;
            k = parentIdx;
        } else {
            break;
        }
    }

    heap->heap = players;
    heap->size = size;

    return player;
}

Player* pop(Heap* heap) {
    if (heap->size == 0) {
        return NULL;
    }

    Player** players = heap->heap;
    int size = heap->size;

    Player* root = players[0];

    players[0] = players[--size];
    heap->heap = players;
    heap->size = size;

    heapify(heap);

    return root;
}
