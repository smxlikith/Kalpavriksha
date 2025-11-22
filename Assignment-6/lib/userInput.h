#ifndef USER_INPUT_H
#define USER_INPUT_H
#define MAX_CHAR_LENGTH 512
#define MAX_ARGS 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileSystem.h"

void getUserInput(char* args[], FileNode* cwd);

#endif