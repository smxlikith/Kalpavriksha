#ifndef STACK_H
#define STACK_H

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} IntStack;

void initIntStack(IntStack *s);
void pushInt(IntStack *s, int value);
int popInt(IntStack *s);
int peekInt(IntStack *s);
int isEmptyInt(IntStack *s);

typedef struct {
    char data[MAX];
    int top;
} CharStack;

void initCharStack(CharStack *s);
void pushChar(CharStack *s, char value);
char popChar(CharStack *s);
char peekChar(CharStack *s);
int isEmptyChar(CharStack *s);

#endif