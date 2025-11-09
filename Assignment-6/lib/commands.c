#include "commands.h"

void createFile(FileNode* root, FileNode* cwd, char* path) {
    if (createFileNode(root, cwd, false, path) != NULL) {
        printf("File Successfully created\n");
    }
}

void writeFile(FileNode* root, FileNode* cwd, Block** freeBlocksList, char* path, char* data) {
    FileNode* file = getFileNodeByPath(root, cwd, path);
    if (file == NULL) {
        printf("Error: no such file: %s\n", path);
        return;
    }

    if (file->isDirectory) {
        printf("Error: cannot write to '%s', it is a directory\n", path);
        return;
    }

    int n = strlen(data);
    if (file->blocks == NULL) {
        file->blocks = allocateBlocks(freeBlocksList, n);
    }
    Block* block = file->blocks;
    for (int i = 0; i < n; i += BLOCK_SIZE) {
        size_t copySize = strlen(data + i) > BLOCK_SIZE ? BLOCK_SIZE : strlen(data + i);
        strncpy(block->data + block->currSize, data + i, copySize);
        block->currSize += copySize;
        block = block->next;
    }
}

void readFile(FileNode* root, FileNode* cwd, char* path) {
    FileNode* file = getFileNodeByPath(root, cwd, path);

    if (file == NULL) {
        printf("Error: no such file: %s\n", path);
        return;
    }

    if (file->isDirectory) {
        printf("Error: cannot read '%s', it is a directory\n", path);
        return;
    }

    if (file->blocks == NULL) {
        printf("(empty)\n");
        return;
    }

    Block* block = file->blocks;
    char data[BLOCK_SIZE];
    do {
        strncpy(data, block->data, block->currSize);
        data[block->currSize] = '\0';
        printf("%s", data);
        block = block->next;
    } while (block != file->blocks);
}

void deleteFile(FileNode* root, FileNode* cwd, Block** freeBlocksList, char* path) {
    FileNode* target = getFileNodeByPath(root, cwd, path);
    if (target == NULL) {
        printf("Error: failed to remove '%s': No such file or directory\n", path);
        return;
    }

    if (target == root) {
        printf("Error: cannot remove root '/'\n", path);
        return;
    }

    if (target->isDirectory) {
        printf("Error: failed to remove '%s': Not a file\n", path);
        return;
    }

    FileNode *parent = target->parent, *children = target->parent->children;

    if (target == target->next) {
        parent->children = NULL;
    } else {
        target->next->prev = target->prev;
        target->prev->next = target->next;
        parent->children = target->next;
    }
    deallocateBlocks(freeBlocksList, target->blocks);
    free(target);
}

void mkdir(FileNode* root, FileNode* cwd, char* path) {
    if (createFileNode(root, cwd, true, path) != NULL) {
        printf("File Successfully created\n");
    }
}

void rmdir(FileNode* root, FileNode* cwd, char* path) {
    FileNode* target = getFileNodeByPath(root, cwd, path);
    if (target == NULL) {
        printf("Error: failed to remove '%s': No such file or directory\n", path);
        return;
    }

    if (target == root) {
        printf("Error: cannot remove root '/'\n", path);
        return;
    }

    if (target == cwd) {
        printf("Error: cannot delete %s, it is the current working directory.\n", path);
        return;
    }

    if (!target->isDirectory) {
        printf("Error: failed to remove '%s': Not a directory\n", path);
        return;
    }

    if (target->children != NULL) {
        printf("Error: failed to remove '%s': Directory not empty\n", path);
        return;
    }
    FileNode *parent = target->parent, *children = target->parent->children;
    if (target == target->next) {
        parent->children = NULL;
    } else {
        target->next->prev = target->prev;
        target->prev->next = target->next;
        parent->children = target->next;
    }
    free(target->name);
    free(target);
}

void cd(FileNode* root, FileNode** cwd, char* path) {
    FileNode* target = getFileNodeByPath(root, *cwd, path);
    if (target == NULL) {
        printf("Error: no such file or directory: %s\n", path);
        return;
    }

    if (!target->isDirectory) {
        printf("cd: not a directory: %s\n", path);
        return;
    }
    *cwd = target;
}

void pwd(FileNode* cwd, int lvl) {
    if (cwd->parent == NULL) {
        if (lvl == 0) {
            printf("/");
        }
        return;
    }
    pwd(cwd->parent, lvl + 1);
    printf("/%s", cwd->name);
}

void ls(FileNode* root, FileNode* cwd, char* path) {
    FileNode* target = getFileNodeByPath(root, cwd, path);
    if (root == NULL) {
        printf("Error: cannot access '%s': No such file or directory\n", path);
    }
    FileNode* curr = target->children;
    if (curr == NULL) {
        printf("(empty)\n");
    } else {
        do {
            if (curr->isDirectory) {
                printf("%s/\n", curr->name);
            } else {
                printf("%s\n", curr->name);
            }
            curr = curr->next;
        } while (curr != target->children);
    }
}

void df(int totalBlocks, Block* freeBlocksList) {
    int unusedBlocks = 0;
    Block* curr = freeBlocksList;
    do {
        unusedBlocks++;
        curr = curr->next;
    } while (curr != freeBlocksList);
    printf("Total Blocks: %d\n", totalBlocks);
    printf("Used Blocks: %d\n", totalBlocks - unusedBlocks);
    printf("Free Blocks: %d\n", unusedBlocks);
    printf("Disk Usage: %.2f%%\n", (float)(totalBlocks - unusedBlocks) / totalBlocks * 100);
}