#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode ListNode;

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* slow = head;
    ListNode* fast = head;
    int sz = 0;
    while (slow != NULL && fast != NULL && fast->next != NULL) {
        sz += 2;
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast != NULL) {
        sz += 1;
    }

    if (n == sz) {
        return head->next;
    }
    slow = head;
    for (int i = 1; i < sz - n; i++) {
        slow = slow->next;
    }
    slow->next = slow->next->next;
    return head;
}