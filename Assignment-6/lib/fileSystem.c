#include "fileSystem.h"

char** splitPath(char* path, char* delim, int* count) {
    int n = 0;
    char** parts = NULL;
    char* pathCopy = strdup(path);
    char* token = strtok(pathCopy, delim);
    while (token != NULL) {
        parts = realloc(parts, sizeof(char*) * (n + 1));
        parts[n] = strdup(token);
        n++;
        token = strtok(NULL, delim);
    }
    *count = n;
    free(pathCopy);
    return parts;
}

char* getFileNameFromPath(char* path) {
    char* last = strrchr(path, '/');

    if (last == NULL) {
        return path;
    }

    char* fileStart = (last) ? last + 1 : path;
    int n = strlen(fileStart) + 1;

    char* fileName = malloc(n);

    if (fileName == NULL) {
        printf("Unable to allocate\n");
        return NULL;
    }
    strcpy(fileName, fileStart);
    fileName[n] = '\0';
    return fileName;
}

char* getParentPathFromPath(char* path) {
    char* last = strrchr(path, '/');

    if (last == NULL) {
        return "\0";
    }

    int n = last - path;
    char* parentPath = malloc(n + 1);

    if (parentPath == NULL) {
        printf("Unable to allocate\n");
        return NULL;
    }

    strncpy(parentPath, path, n);
    parentPath[n] = '\0';

    return parentPath;
}

FileNode* createFileNode(FileNode* root, FileNode* cwd, bool isDirectory, char* path) {
    FileNode *file, *parent;
    int n = strlen(path);
    char* fileName = getFileNameFromPath(path);
    char* parentPath = getParentPathFromPath(path);

    if (root != NULL) {
        FileNode* target = getFileNodeByPath(root, cwd, path);
        if (target != NULL) {
            printf("Error: cannot create file '%s': File exists\n", path);
            return NULL;
        }

        if (fileName == NULL || parentPath == NULL) {
            printf("Error: Invalid file path '%s'. Could not extract file or parent directory.\n", path);
            return NULL;
        }

        if (strlen(fileName) > MAX_NAME_SIZE) {
            printf("Error: FILE_NAME \"%s\" exceeds max allowed size(%d)\n", fileName, MAX_NAME_SIZE);
            return NULL;
        }

        if (strlen(parentPath) == 0) {
            parent = cwd;
        } else {
            parent = getFileNodeByPath(root, cwd, parentPath);
        }

        if (parent == NULL) {
            printf("Error: Cannot create file '%s': No such directory '%s'\n", path, parentPath);
            return NULL;
        }
    }

    file = malloc(sizeof(FileNode));
    if (file == NULL) {
        printf("Error: cannot create file. Unable to allocate memory at the moment. Try again...\n");
        return NULL;
    }

    file->name = fileName;
    file->isDirectory = isDirectory;
    file->parent = parent;
    file->children = NULL;
    file->prev = NULL;
    file->next = NULL;
    file->blocks = NULL;

    if (root == NULL) {
        file->name = strdup(path);
        file->parent = NULL;
        return file;
    }

    if (parent->children == NULL) {
        parent->children = file;
        file->next = file;
        file->prev = file;
    } else {
        FileNode* child = parent->children;
        file->next = child;
        file->prev = child->prev;
        child->prev->next = file;
        child->prev = file;
    }

    return file;
}

FileNode* initFileSystem() {
    return createFileNode(NULL, NULL, true, "/");
}

FileNode* getChildFileNode(FileNode* cwd, char* fileName) {
    FileNode* curr = cwd->children;
    if (curr == NULL) return NULL;
    do {
        if (strcmp(curr->name, fileName) == 0) {
            return curr;
        }
        curr = curr->next;
    } while (curr != cwd->children);
    return NULL;
}

FileNode* getFileNodeByPath(FileNode* root, FileNode* cwd, char* path) {
    int n = 0;
    char** components = splitPath(path, "/", &n);
    FileNode* curr = path[0] == '/' ? root : cwd;
    for (int i = 0; i < n; i++) {
        if (strcmp(".", components[i]) == 0) {
        } else if (strcmp("..", components[i]) == 0) {
            if (curr->parent != NULL) {
                curr = curr->parent;
            }
        } else {
            FileNode* child = getChildFileNode(curr, components[i]);
            if (child == NULL) {
                return NULL;
            }
            curr = child;
        }
    }
    return curr;
}
