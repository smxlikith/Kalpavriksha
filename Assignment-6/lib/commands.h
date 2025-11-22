#ifndef COMMANDS_H
#define COMMANDS_H
#include "fileSystem.h"

void createFile(VFSObj* vfs, char* path);
void writeFile(VFSObj* vfs, char* path, char* data);
void readFile(VFSObj* vfs, char* path);
void deleteFile(VFSObj* vfs, char* path);

void mkdir(VFSObj* vfs, char* path);
void rmdir(VFSObj* vfs, char* path);
void cd(VFSObj* vfs, char* path);
void pwd(FileNode* cwd, int lvl);
void ls(VFSObj* vfs, char* path);
void df(VFSObj* vfs);
void exitVFS(VFSObj* vfs);

#endif