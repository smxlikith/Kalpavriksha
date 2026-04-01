#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode ListNode;

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == NULL && l2 == NULL) {
        return NULL;
    }

    if (l1 == NULL) {
        return l2;
    }

    if (l2 == NULL) {
        return l1;
    }

    ListNode *head = NULL, *curr = NULL;

    head = l1->val < l2->val ? l1 : l2;
    if (head == l1) {
        l1 = l1->next;
    } else {
        l2 = l2->next;
    }
    curr = head;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            curr->next = l1;
            curr = curr->next;
            l1 = l1->next;
        } else {
            curr->next = l2;
            curr = curr->next;
            l2 = l2->next;
        }
    }
    if (l1 != NULL) {
        curr->next = l1;
    } else {
        curr->next = l2;
    }
    return head;
}