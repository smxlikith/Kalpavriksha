#include "commands.h"

#include "queue.h"

void createFile(VFSObj* vfs, char* path) {
    if (createFileNode(vfs->root, *(vfs->cwd), false, path) != NULL) {
        printf("File Successfully created\n");
    }
}

void writeFile(VFSObj* vfs, char* path, char* data) {
    FileNode* file = getFileNodeByPath(vfs->root, *vfs->cwd, path);
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
        file->blocks = allocateBlocks(vfs->freeBlocksList, n);
    }
    Block* block = file->blocks;

    Block* curr = block;
    int required = n;
    do {
        required -= (BLOCK_SIZE - curr->currSize);
        curr = curr->next;
    } while (curr != block);

    if (required > 0) {
        Block* newBlocks = allocateBlocks(vfs->freeBlocksList, required);
        if (newBlocks == NULL) {
            printf("No memory available to allocate.\n");
            return;
        }
        addBlocks(newBlocks, block);
    }

    for (int i = 0; i < n; i += BLOCK_SIZE) {
        size_t copySize = strlen(data + i) > BLOCK_SIZE ? BLOCK_SIZE : strlen(data + i);
        strncpy(block->data + block->currSize, data + i, copySize);
        block->currSize += copySize;
        block = block->next;
    }
    printf("Data written successfully(size = %d bytes).\n", n);
}

void readFile(VFSObj* vfs, char* path) {
    FileNode* file = getFileNodeByPath(vfs->root, *vfs->cwd, path);

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

void deleteFile(VFSObj* vfs, char* path) {
    FileNode* target = getFileNodeByPath(vfs->root, *vfs->cwd, path);
    if (!canDelete(vfs, false, target, path)) {
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
    deallocateBlocks(vfs->freeBlocksList, target->blocks);
    free(target);
    printf("File deleted successfully.\n");
}

void mkdir(VFSObj* vfs, char* path) {
    if (createFileNode(vfs->root, *vfs->cwd, true, path) != NULL) {
        printf("File Successfully created\n");
    }
}

void rmdir(VFSObj* vfs, char* path) {
    FileNode* target = getFileNodeByPath(vfs->root, *vfs->cwd, path);
    if (!canDelete(vfs, true, target, path)) {
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

void cd(VFSObj* vfs, char* path) {
    FileNode* target = getFileNodeByPath(vfs->root, *vfs->cwd, path);
    if (target == NULL) {
        printf("Error: no such file or directory: %s\n", path);
        return;
    }

    if (!target->isDirectory) {
        printf("cd: not a directory: %s\n", path);
        return;
    }
    *vfs->cwd = target;
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

void ls(VFSObj* vfs, char* path) {
    FileNode* target = getFileNodeByPath(vfs->root, *vfs->cwd, path);
    if (target == NULL) {
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

void df(VFSObj* vfs) {
    int unusedBlocks = 0;
    Block* freeBlocksList = *vfs->freeBlocksList;
    int totalBlocks = vfs->totalBlocks;

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

void exitVFS(VFSObj* vfs) {
    if (vfs->root == NULL) {
        return;
    }

    printf("Memory released. Exiting program...\n");
    Queue* q = initQueue(vfs->totalBlocks);
    if (!q) {
        printf("Failed to create queue!\n");
        return;
    }

    enqueueQueue(q, vfs->root);

    while (q->currSize > 0) {
        FileNode* current = dequeueQueue(q);

        if (current->isDirectory && current->children != NULL) {
            FileNode* child = current->children;
            do {
                enqueueQueue(q, child);
                child = child->next;
            } while (child != current->children);
        }
        free(current->name);
        free(current);
    }

    freeQueue(q);
    freeBlocks(*vfs->freeBlocksList);
    freeVirtualDisk(vfs->virtualDisk, vfs->totalBlocks);
    exit(0);
}