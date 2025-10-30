#include "product.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(int* size, Product** inventory) {
    int initialSize;
    while (true) {
        printf("Enter initial number of products: ");
        if (getInt(&initialSize) == SUCCESS) {
            if (initialSize >= MIN_INIT_PRODUCT && initialSize <= MAX_INIT_PRODUCT) {
                break;
            }
            printf("Input out of range. Initial size must be %d <= n <= %d, but got %d.\n", MIN_PRODUCT_ID, MAX_PRODUCT_ID, initialSize);
        }
        printf("Invalid input, Try again...\n");
    }

    for (int i = 0; i < initialSize; i++) {
        printf("\nEnter the details for product %d:\n", i + 1);
        addNewProduct(size, inventory);
        printf("\n");
    }
}

void displayProduct(Product p) {
    printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", p.id, p.name, p.price, p.quantity);
}

float matchString(char* s1, char* s2) {
    int matchCount = 0;
    int srcLength = strlen(s1);
    for (int i = 0; i < MAX_CHAR_LENGTH; i++) {
        if (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
            matchCount++;
            continue;
        }
        break;
    }
    return (float)matchCount / srcLength;
}

Status handleMemoryAllocation(int size, Product** inventory) {
    if (size <= 0) {
        free(*inventory);
        *inventory = NULL;
        return SUCCESS;
    }
    if (*inventory == NULL) {
        *inventory = calloc(size, sizeof(Product));
        if (*inventory == NULL) {
            printf("Unable to allocate memory at the moment, try again later.");
            return FAILURE;
        }
    } else {
        Product* tempPtr = realloc(*inventory, size * sizeof(Product));
        if (tempPtr == NULL) {
            printf("Unable to allocate memory at the moment, try again later.");
            return FAILURE;
        }
        *inventory = tempPtr;
    }
    return SUCCESS;
}

Status addNewProduct(int* currentSize, Product** inventory) {
    int ID;
    printf("Enter new product details:\n");
    if (handleMemoryAllocation(*currentSize + 1, inventory) == SUCCESS) {
        while (true) {
            getProductId(&ID);
            if (searchProductId(ID, currentSize, *inventory) == -1) {
                (*inventory)[*currentSize].id = ID;
                break;
            }
            printf("Product with ID %d already exists. Enter a unique ID.\n\n", ID);
        }
        getProductName((*inventory)[*currentSize].name);
        getProductPrice(&(*inventory)[*currentSize].price);
        getProductQuantity(&(*inventory)[*currentSize].quantity);
        *currentSize += 1;
        return SUCCESS;
    }
    return FAILURE;
};

void viewAllProducts(int* currentSize, Product* inventory) {
    printf("========= PRODUCT LIST =========\n");
    if (*currentSize == 0) {
        printf("No Products in Inventory.\n");
    }
    for (int i = 0; i < *currentSize; i++) {
        displayProduct(inventory[i]);
    }
}

int searchProductId(int ID, int* currentSize, Product* inventory) {
    for (int i = 0; i < *currentSize; i++) {
        if ((inventory)[i].id == ID) {
            return i;
        }
    }
    return -1;
}

Status searchProductById(int* currentSize, Product* inventory) {
    int ID, idx;
    printf("Enter Product ID to search:\n");
    getProductId(&ID);
    idx = searchProductId(ID, currentSize, inventory);
    if (idx != -1) {
        printf("Products Found:\n");
        displayProduct(inventory[idx]);
        return SUCCESS;
    }
    printf("No Product with ID %d.\n", ID);
    return FAILURE;
}

Status searchProductByName(int* currentSize, Product* inventory) {
    char name[MAX_CHAR_LENGTH];
    Status found = FAILURE;
    printf("Enter name to search (partial allowed):\n");
    getProductName(name);
    for (int i = 0; i < *currentSize; i++) {
        if (matchString(name, inventory[i].name) >= NAME_SEARCH_THRESHOLD) {
            if (found == FAILURE) {
                printf("Products Found:\n");
            }
            displayProduct(inventory[i]);
            found = SUCCESS;
        }
    }
    if (found == FAILURE) {
        printf("No matching product with name \"%s\"", name);
    }
    return found;
}

Status searchProductByPriceRange(int* currentSize, Product* inventory) {
    float minPrice, maxPrice;
    Status found = FAILURE;
    printf("Enter the Min Price: ");
    getFloat(&minPrice);
    printf("Enter the Max Price: ");
    getFloat(&maxPrice);

    for (int i = 0; i < *currentSize; i++) {
        float currentPrice = inventory[i].price;
        if (currentPrice >= minPrice && currentPrice <= maxPrice) {
            if (found == FAILURE) {
                printf("Products in price range:\n");
            }
            displayProduct(inventory[i]);
            found = SUCCESS;
        }
    }

    if (found == FAILURE) {
        printf("No matching product within the range [%.2f, %.2f]", minPrice, maxPrice);
    }
    return found;
}

Status updateQuantity(int* currentSize, Product** inventory) {
    int ID;
    printf("Enter Product ID to update quantity:\n");
    getProductId(&ID);
    for (int i = 0; i < *currentSize; i++) {
        if ((*inventory)[i].id == ID) {
            printf("\nEnter the New Quantity for the Item:\n");
            displayProduct((*inventory)[i]);
            printf("\n");
            getProductQuantity(&(*inventory)[i].quantity);
            printf("updated item successfully.");
            return SUCCESS;
        }
    }
    printf("No Product with ID %d.", ID);
    return FAILURE;
}

Status deleteProduct(int* currentSize, Product** inventory) {
    int ID, idx;
    printf("Enter Product ID to delete:\n");
    getProductId(&ID);
    idx = searchProductId(ID, currentSize, *inventory);
    if (idx != -1) {
        printf("Deleted the Following Item:");
        displayProduct((*inventory)[idx]);
        for (int i = idx, j = idx + 1; j < *currentSize; i++, j++) {
            (*inventory)[i] = (*inventory)[j];
        }
    } else {
        printf("No Product with ID %d.\n", ID);
        return FAILURE;
    }
    if (*currentSize == 1) {
        free(*inventory);
        *inventory = NULL;
    } else {
        if (handleMemoryAllocation(*currentSize - 1, inventory) == FAILURE) {
            printf("Error resizing inventory after deletion.\n");
            return FAILURE;
        };
    }
    *currentSize -= 1;
    return SUCCESS;
}
