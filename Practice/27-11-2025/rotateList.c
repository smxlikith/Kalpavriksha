#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};
typedef struct ListNode ListNode;

ListNode* rotateRight(ListNode* head, int k) {
    if (head == NULL) {
        return NULL;
    }
    ListNode* tail = head;
    int size = 1;
    for (; tail->next != NULL; size++, tail = tail->next);
    k %= size;
    tail->next = head;
    for (int i = 0; i < size - k; i++) {
        tail = tail->next;
    }
    head = tail->next;
    tail->next = NULL;
    return head;
}