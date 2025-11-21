#include "queue.h"

Queue* initQueue(int capacity) {
    Queue* q = malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Unable to Allocate memory, Try again later...\n");
        return NULL;
    }
    q->capacity = capacity;
    return q;
}

DoublyLinkedList* enqueue(Queue* q, DoublyLinkedList* node) {
    DoublyLinkedList* head = q->head;

    if (head == NULL) {
        q->head = node;
        q->size = 1;
        return node;
    }

    if (q->size == q->capacity) {
        if (head->next == head) {
            q->head = node;
        } else {
            head = head->prev;

            node->next = head->next;
            node->prev = head->prev;

            head->next->prev = node;
            head->prev->next = node;

            q->head = node;
        }
        free(head);
        return node;
    }

    node->prev = head->prev;
    node->next = head;

    head->prev->next = node;
    head->prev = node;

    q->head = node;
    q->size++;
    return node;
}

DoublyLinkedList* dequeue(Queue* q, DoublyLinkedList* node) {
    if (node == NULL) return NULL;
    if (node == q->head) {
        if (node == node->next) {
            q->head = NULL;
            q->size = 0;
            return node;
        }
        q->head = node->next;
    }
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->prev = node;
    node->next = node;
    q->size--;
    return node;
}

void freeQueue(Queue* q) {
    if (!q || !q->head) {
        return;
    }

    DoublyLinkedList* curr = q->head;
    DoublyLinkedList* next;

    do {
        next = curr->next;
        free(curr);
        curr = next;
    } while (curr != q->head);

    free(q);
}

DoublyLinkedList* createNode(int key, const char* data) {
    DoublyLinkedList* node = malloc(sizeof(DoublyLinkedList));
    if (!node) {
        printf("Unable to allocate memory for node.\n");
        return NULL;
    }

    node->key = key;

    node->data = malloc(strlen(data) + 1);

    if (!node->data) {
        printf("Unable to allocate memory for node data.\n");
        free(node);
        return NULL;
    }

    strcpy(node->data, data);

    node->prev = node;
    node->next = node;

    return node;
}

DoublyLinkedList* modifyNode(DoublyLinkedList* node, int key, const char* data) {
    if (!node) return NULL;

    node->key = key;

    free(node->data);

    node->data = malloc(strlen(data) + 1);
    if (!node->data) {
        printf("Unable to allocate memory for updated data.\n");
        node->data = NULL;
        return NULL;
    }
    strcpy(node->data, data);

    return node;
}

void display(Queue* q) {
    DoublyLinkedList *head = q->head, *curr = q->head;
    if (head == NULL) {
        printf("(empty)\n");
        return;
    }
    do {
        printf("<-%d(%s)->", curr->key, curr->data);
        curr = curr->next;
    } while (curr != head);
    printf("\n");
}