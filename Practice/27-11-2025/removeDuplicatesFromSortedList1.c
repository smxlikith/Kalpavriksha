#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};
typedef struct ListNode ListNode;

ListNode* deleteDuplicates(ListNode* head) {
    ListNode *curr = head, *temp = NULL;
    while (curr != NULL) {
        temp = curr->next;
        while (temp != NULL && temp->val == curr->val) {
            temp = temp->next;
        }
        curr->next = temp;
        curr = temp;
    }
    return head;
}