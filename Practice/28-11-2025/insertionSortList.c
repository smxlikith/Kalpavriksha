#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode ListNode;

ListNode* insertionSortList(ListNode* head) {
    if (head == NULL) {
        return NULL;
    }

    ListNode *sorted = head, *it = head->next, *curr, *prev, *temp;
    sorted->next = NULL;

    while (it != NULL) {
        prev = NULL;
        curr = sorted;
        while (curr != NULL && curr->val < it->val) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == sorted) {
            temp = it->next;
            it->next = sorted;
            sorted = it;
            it = temp;
        } else {
            temp = it->next;
            it->next = curr;
            prev->next = it;
            it = temp;
        }
    }

    return sorted;
}