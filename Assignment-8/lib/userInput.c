#include "userInput.h"

void parseInput(char* line, char* args[3]) {
    for (int i = 0; i < 3; i++) args[i] = NULL;

    char* token = strtok(line, " \t\n");
    int index = 0;

    while (token != NULL && index < 3) {
        args[index++] = token;
        token = strtok(NULL, " \t\n");
    }
}