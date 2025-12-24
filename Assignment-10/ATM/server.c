#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./lib/common.h"

pthread_mutex_t accountMutex;

int readAccountBalance() {
    FILE* file = fopen(ACCOUNT_FILE, "r");
    int balance = 0;

    if (file != NULL) {
        fscanf(file, "%d", &balance);
        fclose(file);
    }

    return balance;
}

void writeAccountBalance(int balance) {
    FILE* file = fopen(ACCOUNT_FILE, "w");
    fprintf(file, "%d", balance);
    fclose(file);
}

void processTransaction(const TransactionRequest* request, TransactionResponse* response) {
    pthread_mutex_lock(&accountMutex);

    int balance = readAccountBalance();

    if (request->operation == OP_WITHDRAW) {
        if (request->amount > balance) {
            response->status = 0;
            sprintf(response->message, "Withdrawal failed: Insufficient balance");
        } else {
            balance -= request->amount;
            writeAccountBalance(balance);
            response->status = 1;
            sprintf(response->message, "Withdrawal successful");
        }
    } else if (request->operation == OP_DEPOSIT) {
        balance += request->amount;
        writeAccountBalance(balance);
        response->status = 1;
        sprintf(response->message, "Deposit successful");
    } else if (request->operation == OP_DISPLAY) {
        response->status = 1;
        sprintf(response->message, "Balance retrieved");
    } else {
        response->status = 0;
        sprintf(response->message, "Invalid operation");
    }

    response->currentBalance = balance;

    pthread_mutex_unlock(&accountMutex);
}

void* handleClient(void* arg) {
    int clientSocket = *(int*)arg;
    free(arg);

    TransactionRequest request;
    TransactionResponse response;

    while (1) {
        int bytesRead = recv(clientSocket, &request, sizeof(request), 0);

        if (bytesRead <= 0 || request.operation == OP_EXIT) {
            break;
        }

        processTransaction(&request, &response);

        send(clientSocket, &response, sizeof(response), 0);
    }

    close(clientSocket);
    return NULL;
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t addressLength = sizeof(clientAddress);

    pthread_mutex_init(&accountMutex, NULL);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);

    printf("Server running on port %d\n", SERVER_PORT);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &addressLength);

        pthread_t threadId;
        int* socketPtr = malloc(sizeof(int));
        *socketPtr = clientSocket;

        pthread_create(&threadId, NULL, handleClient, socketPtr);

        pthread_detach(threadId);
    }

    close(serverSocket);
    pthread_mutex_destroy(&accountMutex);
    return 0;
}