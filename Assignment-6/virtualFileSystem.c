#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/commands.h"
#include "lib/userInput.h"

void handleFunction(char** virtualDisk, Block** freeBlocksList, FileNode* root, FileNode** cwd, int totalBlocks, char** args) {
    int argc = 0;
    for (int i = 0; args[i] != NULL; i++, argc++);

    if (strcmp(args[0], "create") == 0) {
        createFile(root, *cwd, args[1]);
    } else if (strcmp(args[0], "write") == 0) {
        if (argc < 3) {
            printf("Error: 'write' command requires a filename and data to write.\n");
            return;
        }
        writeFile(root, *cwd, freeBlocksList, args[1], args[2]);
    } else if (strcmp(args[0], "read") == 0) {
        if (argc < 2) {
            printf("Error: 'read' command requires a filename to read from.\n");
            return;
        }
        readFile(root, *cwd, args[1]);
        printf("\n");
    } else if (strcmp(args[0], "delete") == 0) {
        if (argc < 2) {
            printf("Error: 'delete' command requires a filename to delete.\n");
            return;
        }
        deleteFile(root, *cwd, freeBlocksList, args[1]);
    } else if (strcmp(args[0], "mkdir") == 0) {
        if (argc < 2) {
            printf("Error: 'mkdir' command requires a directory name to create.\n");
            return;
        }
        mkdir(root, *cwd, args[1]);
    } else if (strcmp(args[0], "rmdir") == 0) {
        if (argc < 2) {
            printf("Error: 'rmdir' command requires a directory name to remove.\n");
            return;
        }
        rmdir(root, *cwd, args[1]);
    } else if (strcmp(args[0], "cd") == 0) {
        if (argc < 2) {
            printf("Error: 'cd' command requires a directory to change to.\n");
            return;
        }
        cd(root, cwd, args[1]);
    } else if (strcmp(args[0], "pwd") == 0) {
        pwd(*cwd, 0);
        printf("\n");
    } else if (strcmp(args[0], "ls") == 0) {
        ls(root, *cwd, argc > 1 ? args[1] : "");
    } else if (strcmp(args[0], "df") == 0) {
        df(totalBlocks, *freeBlocksList);
    } else if (strcmp(args[0], "exit") == 0) {
        printf("Memory released. Exiting program...\n");
        freeBlocks(*freeBlocksList);
        free(virtualDisk);
        exit(0);
    } else {
        printf("Error: Unknown command '%s'. Please check the syntax.\n", args[0]);
    }
}

void commandLine(char** virtualDisk, Block** freeBlocksList, FileNode* root, FileNode** cwd, int totalBlocks) {
    int argSize = 0;
    char** args = getUserInput(&argSize, *cwd);
    if (args == NULL) return;
    handleFunction(virtualDisk, freeBlocksList, root, cwd, totalBlocks, args);
    free(args);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error: You must provide exactly one argument, which is the number of blocks.\n");
        return 1;
    }

    int numberOfBlocks = atoi(argv[1]);

    if (numberOfBlocks <= 0) {
        printf("Error: The number of blocks must be a positive integer.\n");
        return 1;
    }

    printf("Compact VFS - ready. Type 'exit' to quit\n");

    char** virtualDisk = initVirtualDisk(numberOfBlocks);
    Block* freeBlocksList = initMemoryBlocks(numberOfBlocks, virtualDisk);
    FileNode* root = initFileSystem();
    FileNode* cwd = root;
    while (true) {
        commandLine(virtualDisk, &freeBlocksList, root, &cwd, numberOfBlocks);
    }
    return 0;
}