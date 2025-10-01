#include <stdio.h>
#include "stack.h"

void initIntStack(IntStack *s) { 
    s->top = -1; 
}

void pushInt(IntStack *s, int value) {
    if (s->top < MAX - 1) s->data[++(s->top)] = value;
    else printf("Stack overflow!\n");
}

int popInt(IntStack *s) {
    if (s->top >= 0) return s->data[(s->top)--];
    printf("Stack underflow!\n");
    return 0;
}

int peekInt(IntStack *s) {
    return (s->top >= 0) ? s->data[s->top] : 0; 
}

int isEmptyInt(IntStack *s) { 
    return s->top == -1; 
}

void initCharStack(CharStack *s) { 
    s->top = -1; 
}

void pushChar(CharStack *s, char value) {
    if (s->top < MAX - 1) s->data[++(s->top)] = value;
    else printf("Stack overflow!\n");
}

char popChar(CharStack *s) {
    if (s->top >= 0) return s->data[(s->top)--];
    printf("Stack underflow!\n");
    return '\0';
}

char peekChar(CharStack *s) { 
    return (s->top >= 0) ? s->data[s->top] : '\0'; 
}

int isEmptyChar(CharStack *s) {
    return s->top == -1; 
}