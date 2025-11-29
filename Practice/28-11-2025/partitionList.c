#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};
typedef struct ListNode ListNode;

ListNode* partition(ListNode* head, int x) {
    if (head == NULL) return NULL;

    ListNode *p1h = NULL, *p2h = NULL;
    ListNode *p1 = NULL, *p2 = NULL;
    ListNode* curr = head;

    while (curr != NULL) {
        if (curr->val < x) {
            if (p1h == NULL) {
                p1h = curr;
                p1 = curr;
            } else {
                p1->next = curr;
                p1 = curr;
            }
        } else {
            if (p2h == NULL) {
                p2h = curr;
                p2 = curr;
            } else {
                p2->next = curr;
                p2 = curr;
            }
        }
        curr = curr->next;
    }

    if (p2 != NULL) {
        p2->next = NULL;
    }
    if (p1 != NULL) {
        p1->next = p2h;
    }

    return p1h == NULL ? p2h : p1h;
}