#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};
typedef struct ListNode ListNode;

struct ListNode* deleteDuplicates(struct ListNode* head) {
    ListNode *curr = head, *prev = NULL, *temp = NULL;
    while (curr != NULL) {
        temp = curr->next;
        while (temp != NULL && temp->val == curr->val) {
            temp = temp->next;
        }
        if (curr->next != temp) {
            if (curr == head) {
                head = temp;
            }
            if (prev != NULL) {
                prev->next = temp;
            }
        } else {
            prev = curr;
        }
        curr->next = temp;
        curr = temp;
    }
    return head;
}