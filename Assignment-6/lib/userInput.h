#ifndef USER_INPUT_H
#define USER_INPUT_H
#define MAX_CHAR_LENGTH 512

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileSystem.h"

void clearInputBuffer();
char** getUserInput(int* size, FileNode* cwd);

#endif