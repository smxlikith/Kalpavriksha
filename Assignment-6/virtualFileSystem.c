#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/commands.h"
#include "lib/userInput.h"

void handleFunction(VFSObj* vfs, char** args) {
    int argc = 0;
    for (int i = 0; args[i] != NULL; i++, argc++);
    if (strcmp(args[0], "create") == 0) {
        createFile(vfs, args[1]);
    } else if (strcmp(args[0], "write") == 0) {
        if (argc < 3) {
            printf("Error: 'write' command requires a filename and data to write.\n");
            return;
        }
        writeFile(vfs, args[1], args[2]);
    } else if (strcmp(args[0], "read") == 0) {
        if (argc < 2) {
            printf("Error: 'read' command requires a filename to read from.\n");
            return;
        }
        readFile(vfs, args[1]);
        printf("\n");
    } else if (strcmp(args[0], "delete") == 0) {
        if (argc < 2) {
            printf("Error: 'delete' command requires a filename to delete.\n");
            return;
        }
        deleteFile(vfs, args[1]);
    } else if (strcmp(args[0], "mkdir") == 0) {
        if (argc < 2) {
            printf("Error: 'mkdir' command requires a directory name to create.\n");
            return;
        }
        mkdir(vfs, args[1]);
    } else if (strcmp(args[0], "rmdir") == 0) {
        if (argc < 2) {
            printf("Error: 'rmdir' command requires a directory name to remove.\n");
            return;
        }
        rmdir(vfs, args[1]);
    } else if (strcmp(args[0], "cd") == 0) {
        if (argc < 2) {
            printf("Error: 'cd' command requires a directory to change to.\n");
            return;
        }
        cd(vfs, args[1]);
    } else if (strcmp(args[0], "pwd") == 0) {
        pwd(*vfs->cwd, 0);
        printf("\n");
    } else if (strcmp(args[0], "ls") == 0) {
        ls(vfs, argc > 1 ? args[1] : "");
    } else if (strcmp(args[0], "df") == 0) {
        df(vfs);
    } else if (strcmp(args[0], "exit") == 0) {
        exitVFS(vfs);
    } else {
        printf("Error: Unknown command '%s'. Please check the syntax.\n", args[0]);
    }
}

void commandLine(VFSObj* vfs) {
    char* args[MAX_ARGS] = {0};
    getUserInput(args, *vfs->cwd);
    if (args[0] == NULL) return;
    handleFunction(vfs, args);
}

VFSObj* initializeVFSObject(char** virtualDisk, Block** freeBlocksList, FileNode* root, FileNode** cwd, int totalBlocks) {
    VFSObj* obj = malloc(sizeof(VFSObj));
    if (obj == NULL) {
        printf("Unable to allocate memory, try again later...\n");
    }

    obj->cwd = cwd;
    obj->root = root;
    obj->freeBlocksList = freeBlocksList;
    obj->virtualDisk = virtualDisk;
    obj->totalBlocks = totalBlocks;

    return obj;
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

    VFSObj* vfs = initializeVFSObject(virtualDisk, &freeBlocksList, root, &cwd, numberOfBlocks);

    while (true) {
        commandLine(vfs);
    }
    return 0;
}
