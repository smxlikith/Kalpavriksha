#ifndef PRODUCT_H
#define PRODUCT_H

#include "userInput.h"

typedef struct {
    int id;
    char name[MAX_CHAR_LENGTH];
    float price;
    int quantity;
} Product;

void init(int* size, Product** inventory);

Status handleMemoryAllocation(int size, Product** inventory);

Status addNewProduct(int* currentSize, Product** inventory);

void displayProduct(Product p);

float matchString(char* s1, char* s2);

void viewAllProducts(int* currentSize, Product* inventory);

Status searchProductById(int* currentSize, Product* inventory);

int searchProductId(int id, int* currentSize, Product* inventory);

Status searchProductByName(int* currentSize, Product* inventory);

Status searchProductByPriceRange(int* currentSize, Product* inventory);

Status updateQuantity(int* currentSize, Product** inventory);

Status deleteProduct(int* currentSize, Product** inventory);

#endif
