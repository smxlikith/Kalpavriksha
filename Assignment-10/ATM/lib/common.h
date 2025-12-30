#ifndef COMMON_H
#define COMMON_H

#define SERVER_PORT 8080
#define ACCOUNT_FILE "account.txt"
#define MAX_AMOUNT 100000

typedef enum {
    OP_WITHDRAW = 1,
    OP_DEPOSIT,
    OP_DISPLAY,
    OP_EXIT
} OperationType;

typedef struct {
    OperationType operation;
    int amount;
} TransactionRequest;

typedef struct {
    int status;
    int currentBalance;
    char message[128];
} TransactionResponse;

#endif
