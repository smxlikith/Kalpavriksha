#include <stdio.h>
#include <stdlib.h>

#include "lib/product.h"

void runInventoryMenu(int* currentSize, Product** inventory) {
    int choice;
    printf("\n========= INVENTORY MENU =========");
    printf("\n1. Add New Product\n2. View All Products\n3. Update Quantity\n4. Search Product by ID\n5. Search Product by Name\n6. Search Product by Price Range\n7. Delete Product\n8. Exit\n");
    printf("Enter your choice: ");
    if (getInt(&choice) == SUCCESS) {
        printf("\n");
        switch (choice) {
            case 1:
                addNewProduct(currentSize, inventory);
                break;
            case 2:
                viewAllProducts(currentSize, inventory);
                break;
            case 3:
                updateQuantity(currentSize, inventory);
                break;
            case 4:
                searchProductById(currentSize, inventory);
                break;
            case 5:
                searchProductByName(currentSize, inventory);
                break;
            case 6:
                searchProductByPriceRange(currentSize, inventory);
                break;
            case 7:
                deleteProduct(currentSize, inventory);
                break;
            case 8:
                free(*inventory);
                exit(0);
            default:
                printf("Invalid Choice, Try Again...\n");
                break;
        }
    } else {
        printf("Invalid Input, Try Again...\n");
    }
    printf("\n");
}

int main() {
    int currentInventorySize = 0;
    Product* inventory = NULL;
    init(&currentInventorySize, &inventory);
    viewAllProducts(&currentInventorySize, &inventory);
    while (1) {
        runInventoryMenu(&currentInventorySize, &inventory);
    }
}