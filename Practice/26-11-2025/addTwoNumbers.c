#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode ListNode;

ListNode* createNode(int val) {
    ListNode* node = malloc(sizeof(ListNode));
    if (node == NULL) {
        exit(1);
    }

    node->val = val;
    node->next = NULL;

    return node;
}

void display(ListNode* h) {
    while (h != NULL) {
        printf("%d->", h->val);
        h = h->next;
    }
    printf("\n");
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == NULL && l2 == NULL) {
        return NULL;
    }

    if (l1 == NULL) {
        return l2;
    }

    if (l2 == NULL) {
        return l1;
    }

    ListNode* curr = l1;
    ListNode* prev = NULL;
    ListNode* temp = NULL;

    int sum = 0, carry = 0;

    while (curr != NULL) {
        sum = curr->val + carry;

        if (l2 != NULL) {
            sum += l2->val;
        }

        carry = sum / 10;
        curr->val = sum % 10;

        prev = curr;
        curr = curr->next;

        if (l2 != NULL) {
            l2 = l2->next;
        }

        if (curr == NULL) {
            curr = l2;
            if (l2 != NULL) {
                prev->next = curr;
            }
            l2 = NULL;
        }
    }

    if (carry != 0) {
        prev->next = createNode(carry);
    }

    return l1;
}