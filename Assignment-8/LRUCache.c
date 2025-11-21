#include "lib/commands.h"
#include "lib/userInput.h"

void menu() {
    char line[MAX_CHAR_LENGTH];
    char* args[3];
    LRUCache* cache = NULL;

    while (fgets(line, sizeof(line), stdin)) {
        parseInput(line, args);

        if (args[0] == NULL) continue;

        if (strcmp(args[0], "createCache") == 0) {
            if (!args[1]) {
                printf("Missing capacity.\n");
                continue;
            }

            if (cache != NULL) {
                printf("Cache already initialized.\n");
                continue;
            }

            int size = (int)strtol(args[1], NULL, 10);
            cache = createCache(size);

        } else if (strcmp(args[0], "get") == 0) {
            if (!cache) {
                printf("Cache not created yet.\n");
                continue;
            }

            if (!args[1]) {
                printf("Missing key.\n");
                continue;
            }

            int key = (int)strtol(args[1], NULL, 10);

            if (key < MIN_CAPACITY || key > MAX_CAPACITY) {
                printf("Error: key=%d, out of bound, should be in [%d, %d].\n", key, MIN_CAPACITY, MAX_CAPACITY);
                continue;
            }

            char* result = get(cache, key);
            if (result) {
                printf("%s\n", result);
            } else {
                printf("NULL\n");
            }
        } else if (strcmp(args[0], "put") == 0) {
            if (!cache) {
                printf("Cache not created yet.\n");
                continue;
            }

            if (!args[1] || !args[2]) {
                printf("Usage: put <key> <data>\n");
                continue;
            }

            int key = (int)strtol(args[1], NULL, 10);

            if (key < MIN_CAPACITY || key > MAX_CAPACITY) {
                printf("Error: key=%d, out of bound, should be in [%d, %d].\n", key, MIN_CAPACITY, MAX_CAPACITY);
                continue;
            }

            char* data = args[2];

            put(cache, key, data);
        } else if (strcmp(args[0], "exit") == 0) {
            freeCache(cache);
            break;
        } else {
            printf("Not a valid option\n");
        }
    }
}

int main() {
    menu();
    return 0;
}