#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "constraints.h"
#include "status.h"

void clearInputBuffer();

Status getInt(int* IN);
Status getString(char* IN);
Status getFloat(float* IN);

void getProductId(int* IN);
void getProductName(char* IN);
void getProductPrice(float* IN);
void getProductQuantity(int* IN);
#endif