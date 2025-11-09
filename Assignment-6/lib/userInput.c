
#include "userInput.h"

void clearInputBuffer() {
    int c;
    while (1) {
        c = getchar();
        if (c == '\n' || c == EOF)
            break;
    }
}

char** getUserInput(int* size, FileNode* cwd) {
    int currArgs = 1;
    char* input = malloc(MAX_CHAR_LENGTH);
    char** args = malloc(currArgs * sizeof(char*));
    char** temp;

    if (args == NULL || input == NULL) {
        printf("Memory Allocation Failed.\n");
        exit(1);
    }

    printf("%s>", cwd->name);

    if (fgets(input, MAX_CHAR_LENGTH, stdin) == NULL) {
        return NULL;
    }

    if (strchr(input, '\n') == NULL) {
        printf("Input was too long. Please enter a shorter command.\n");
        clearInputBuffer();
        return NULL;
    }

    input[strcspn(input, "\n")] = '\0';

    int N = strlen(input);
    if (N == 0) {
        return NULL;
    }
    int i = 0, j = 0;
    char* arg = malloc(MAX_CHAR_LENGTH);

    while (i < N) {
        while (i < N && input[i] == ' ') {
            i++;
        }

        if (i == N) break;

        if (input[i] == '\'' || input[i] == '"') {
            char quote = input[i];
            i++;
            j = 0;

            while (i < N && input[i] != quote) {
                arg[j++] = input[i++];
            }

            if (i == N || input[i] != quote) {
                printf("Error: Incomplete quotes. Please ensure that quotes are properly closed.\n");
                free(arg);
                return NULL;
            }

            i++;
            arg[j] = '\0';
            args[currArgs - 1] = strdup(arg);
        } else {
            j = 0;
            while (i < N && input[i] != ' ' && input[i] != '\'' && input[i] != '"') {
                arg[j++] = input[i++];
            }
            arg[j] = '\0';
            args[currArgs - 1] = strdup(arg);
        }

        currArgs++;
        temp = realloc(args, currArgs * sizeof(char*));
        if (temp == NULL) {
            printf("Memory Allocation Failed.\n");
            exit(1);
        }
        args = temp;
    }

    args[currArgs - 1] = NULL;
    *size = currArgs - 1;
    free(arg);
    return args;
}