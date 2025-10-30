#ifndef USER_INPUT_H
#define USER_INPUT_H

typedef enum {
    FAILURE,
    SUCCESS
} Status;

#define CONTRAINTS_H

#define NAME_SEARCH_THRESHOLD 0.1

#define MIN_INIT_PRODUCT 1
#define MAX_INIT_PRODUCT 100

#define MIN_PRODUCT_ID 1
#define MAX_PRODUCT_ID 10000

#define MIN_CHAR_LENGTH 1
#define MAX_CHAR_LENGTH 50

#define MIN_PRODUCT_PRICE 0.0
#define MAX_PRODUCT_PRICE 100000.0

#define MIN_PRODUCT_QUANTITY 0
#define MAX_PRODUCT_QUANTITY 1000000

void clearInputBuffer();

Status getInt(int* IN);
Status getString(char* IN);
Status getFloat(float* IN);

void getProductId(int* IN);
void getProductName(char* IN);
void getProductPrice(float* IN);
void getProductQuantity(int* IN);
#endif