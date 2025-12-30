#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./lib/common.h"

void clearInputBuffer() {
    while (getchar() != '\n');
}

int readInteger() {
    int value;
    while (scanf("%d", &value) != 1) {
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

int isValidChoice(OperationType choice) {
    return choice >= OP_WITHDRAW && choice <= OP_EXIT;
}

int isValidAmount(int amount) {
    return amount > 0 && amount <= MAX_AMOUNT;
}

void showMenu() {
    printf("\n1. Withdraw\n");
    printf("2. Deposit\n");
    printf("3. Display Balance\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
}

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    TransactionRequest request;
    TransactionResponse response;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    while (1) {
        showMenu();
        request.operation = readInteger();

        if (!isValidChoice(request.operation)) {
            continue;
        }

        if (request.operation == OP_EXIT) {
            send(clientSocket, &request, sizeof(request), 0);
            break;
        }

        request.amount = 0;

        if (request.operation == OP_WITHDRAW || request.operation == OP_DEPOSIT) {
            printf("Enter amount: ");
            request.amount = readInteger();
            if (!isValidAmount(request.amount)) {
                continue;
            }
        }

        send(clientSocket, &request, sizeof(request), 0);

        recv(clientSocket, &response, sizeof(response), 0);

        printf("%s\n", response.message);
        printf("Current Balance: %d\n", response.currentBalance);
    }

    close(clientSocket);
    return 0;
}