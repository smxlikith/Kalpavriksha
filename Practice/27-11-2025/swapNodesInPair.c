#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode ListNode;

ListNode* swapPairs(ListNode* head) {
    if (head == NULL) {
        return NULL;
    }

    ListNode* p1 = head;
    ListNode* p2 = head->next;
    ListNode* prev = NULL;

    if (p2 == NULL) {
        return head;
    }

    head = p2;

    while (p1 != NULL && p2 != NULL) {
        p1->next = p2->next;
        p2->next = p1;

        if (prev != NULL) {
            prev->next = p2;
        }
        prev = p1;

        p1 = p1->next;
        if (p1 != NULL) {
            p2 = p1->next;
        }
    }

    return head;
}