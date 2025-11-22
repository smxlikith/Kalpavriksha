#ifndef FILE_SYSTEM_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memBlock.h"

#define FILE_SYSTEM_H
#define MAX_NAME_SIZE 50

typedef struct FileNode FileNode;

struct FileNode {
    char* name;
    bool isDirectory;
    FileNode* parent;
    FileNode* children;
    FileNode* prev;
    FileNode* next;
    Block* blocks;
};

typedef struct {
    char** virtualDisk;
    Block** freeBlocksList;
    FileNode* root;
    FileNode** cwd;
    int totalBlocks;
} VFSObj;

char** splitPath(char* path, char* delim, int* count);
char* getFileNameFromPath(char* path);
char* getParentPathFromPath(char* path);
FileNode* initFileSystem();
FileNode* createFileNode(FileNode* root, FileNode* cwd, bool isDirectory, char* path);
FileNode* getChildFileNode(FileNode* cwd, char* fileName);
FileNode* getFileNodeByPath(FileNode* root, FileNode* cwd, char* path);

bool canDelete(VFSObj* vfs, bool isDirectory, FileNode* file, char* path);
void displayFileNode(FileNode* file);

#endif