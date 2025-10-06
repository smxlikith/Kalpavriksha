#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"


typedef enum{
    ADDITION = 1,
    SUBSTRACTION = 1,
    DIVISION = 2,
    MULTIPLICATION = 2,
    INVALID = -1,
} Precedence;

Precedence precedence(char c) {
    switch(c){
        case '+': return ADDITION;
        case '-': return SUBSTRACTION;
        case '*': return MULTIPLICATION;
        case '/': return DIVISION;
        default: return INVALID;
    }
}

int Calculator(const char s[]) {
    IntStack nums;
    CharStack ops;
    initIntStack(&nums);
    initCharStack(&ops);

    int size = strlen(s);
    for(int i=0; i<size; i++){
        if(s[i]!=' '){
            if(isdigit((unsigned char)s[i])) {
                int num = 0;
                while(i<size && isdigit(s[i])) {
                    num = num*10 + (s[i]-'0');
                    i++;
                }
                i--;
                pushInt(&nums, num);
            } else if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/') {
                while(!isEmptyChar(&ops) && precedence(peekChar(&ops)) >= precedence(s[i])) {
                    char op = popChar(&ops);
                    int a = popInt(&nums);
                    int b = popInt(&nums);
                    switch(op){
                        case '+': pushInt(&nums,b+a); break;
                        case '-': pushInt(&nums,b-a); break;
                        case '*': pushInt(&nums,b*a); break;
                        case '/':
                            if(a==0){ printf("Division by zero.\n"); return -1; }
                            pushInt(&nums,b/a); break;
                    }
                }
                pushChar(&ops, s[i]);
            } else {
                printf("%c : Invalid Input\n", s[i]);
                return -1;
            }           
        }
    }

    while(!isEmptyChar(&ops)) {
        char op = popChar(&ops);
        int a = popInt(&nums);
        int b = popInt(&nums);
        switch(op){
            case '+': pushInt(&nums,b+a); break;
            case '-': pushInt(&nums,b-a); break;
            case '*': pushInt(&nums,b*a); break;
            case '/':
                if(a==0){ printf("Division by zero.\n"); return -1; }
                pushInt(&nums,b/a); break;
        }
    }

    return popInt(&nums);
}

int main(int argc, char *argv[]) {
    if(argc>1){
        int result = Calculator(argv[1]);
		printf("%d\n", result);
    } else {
        printf("No Input String Provided. Try again with an Input String.\n");
    }
    return 0;
}