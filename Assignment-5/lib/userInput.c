#include "userInput.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearInputBuffer() {
    int c;
    while (1) {
        c = getchar();
        if (c == '\n' || c == EOF)
            break;
    }
}

Status getInt(int* IN) {
    char buffer[MAX_CHAR_LENGTH];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return FAILURE;
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    char* endptr;
    long val = strtol(buffer, &endptr, 10);

    if (endptr == buffer) {
        printf("No valid integer input.\n");
        return FAILURE;
    }

    if (*endptr != '\0') {
        if (strlen(buffer) <= MAX_CHAR_LENGTH) {
            printf("Invalid input.\n");
        } else {
            printf("Input out of bounds.\n");
            clearInputBuffer();
        }
        return FAILURE;
    }

    *IN = (int)val;
    return SUCCESS;
}

Status getFloat(float* IN) {
    char buffer[MAX_CHAR_LENGTH];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return FAILURE;
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    char* endptr;
    float val = strtof(buffer, &endptr);

    if (endptr == buffer) {
        printf("No valid float input.\n");
        return FAILURE;
    }

    if (*endptr != '\0') {
        if (strlen(buffer) <= MAX_CHAR_LENGTH) {
            printf("Invalid input.\n");
        } else {
            printf("Input out of bounds.\n");
            clearInputBuffer();
        }
        return FAILURE;
    }

    *IN = val;
    return SUCCESS;
}

Status getString(char* IN) {
    if (fgets(IN, MAX_CHAR_LENGTH, stdin) == NULL) {
        return FAILURE;
    }

    if (strchr(IN, '\n') == NULL) {
        printf("Input was too long and was truncated!\n");
        clearInputBuffer();
        char choice[8];
        printf("Continue with the current String: \"%s\"? (Y/N)(Default: Y): ", IN);
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("Error reading input.\n");
            return FAILURE;
        }
        if (strchr(choice, '\n') == NULL) {
            clearInputBuffer();
        }
        if (choice[0] == 'N' || choice[0] == 'n') {
            return FAILURE;
        }
        return SUCCESS;
    }

    IN[strcspn(IN, "\n")] = '\0';

    if (strlen(IN) < MIN_CHAR_LENGTH) {
        printf("Invalid input, got empty string.\n");
        return FAILURE;
    }

    return SUCCESS;
}

void getProductId(int* IN) {
    while (1) {
        printf("Product ID: ");
        if (getInt(IN) == SUCCESS) {
            if (*IN >= MIN_PRODUCT_ID && *IN <= MAX_PRODUCT_ID) {
                break;
            }
            printf("Input out of range. ID must be %d <= ID <= %d, but got %d.\n", MIN_PRODUCT_ID, MAX_PRODUCT_ID, *IN);
        }
        printf("Invalid input, Try again...\n");
    }
}

void getProductName(char* IN) {
    while (1) {
        printf("Product Name: ");
        if (getString(IN) == SUCCESS) {
            break;
        }
    }
}

void getProductPrice(float* IN) {
    while (1) {
        printf("Product price: ");
        if (getFloat(IN) == SUCCESS) {
            if (*IN >= MIN_PRODUCT_PRICE && *IN <= MAX_PRODUCT_PRICE) {
                break;
            }
            printf("Input out of range. Price must be %.2f <= Price <= %.2f, but got %.2f.\n", MIN_PRODUCT_PRICE, MAX_PRODUCT_PRICE, *IN);
        }
        printf("Invalid Input, Try again...\n");
    }
}

void getProductQuantity(int* IN) {
    while (1) {
        printf("Product Quantity: ");
        if (getInt(IN) == SUCCESS) {
            if (*IN >= MIN_PRODUCT_QUANTITY && *IN <= MAX_PRODUCT_QUANTITY) {
                break;
            }
            printf("Input out of range. ID must be %d <= ID <= %d, but got %d.\n", MIN_PRODUCT_QUANTITY, MAX_PRODUCT_QUANTITY, *IN);
        }
        printf("Invalid Input, Try again...\n");
    }
}