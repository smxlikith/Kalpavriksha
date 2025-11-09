#ifndef COMMANDS_H
#define COMMANDS_H
#include "fileSystem.h"

void createFile(FileNode* root, FileNode* cwd, char* path);
void writeFile(FileNode* root, FileNode* cwd, Block** freeBlocksList, char* path, char* data);
void readFile(FileNode* root, FileNode* cwd, char* path);
void deleteFile(FileNode* root, FileNode* cwd, Block** freeBlocksList, char* path);

void mkdir(FileNode* root, FileNode* cwd, char* path);
void rmdir(FileNode* root, FileNode* cwd, char* path);
void cd(FileNode* root, FileNode** cwd, char* path);
void pwd(FileNode* cwd, int lvl);
void ls(FileNode* root, FileNode* cwd, char* path);
void df(int totalBlocks, Block* freeBlocksList);
#endif