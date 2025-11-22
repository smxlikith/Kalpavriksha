
#include "userInput.h"

void clearInputBuffer() {
    int c;
    while (1) {
        c = getchar();
        if (c == '\n' || c == EOF)
            break;
    }
}

char* readInput() {
    static char input[MAX_CHAR_LENGTH];

    if (fgets(input, MAX_CHAR_LENGTH, stdin) == NULL) {
        return NULL;
    }

    if (strchr(input, '\n') == NULL) {
        printf("Input was too long. Please enter a shorter command.\n");
        clearInputBuffer();
        return NULL;
    }

    input[strcspn(input, "\n")] = '\0';
    return input;
}

void tokenizeInput(char* input, char* args[]) {
    int count = 0;
    char* token = strtok(input, " ");
    while (token != NULL && count < MAX_ARGS - 1) {
        int len = strlen(token);
        if ((token[0] == '"' && token[len - 1] == '"') ||
            (token[0] == '\'' && token[len - 1] == '\'')) {
            token[len - 1] = '\0';
            token++;
        }

        args[count++] = token;
        token = strtok(NULL, " ");
    }
    args[count] = NULL;
}

void getUserInput(char* args[], FileNode* cwd) {
    printf("%s> ", cwd->name);
    char* input = readInput();
    if (input == NULL || strlen(input) == 0) {
        return;
    }
    tokenizeInput(input, args);
}