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
    const char* last = strrchr(path, '/');
    const char* fileStart = last ? last + 1 : path;
    char* fileName = strdup(fileStart);
    if (fileName == NULL) {
        printf("Unable to allocate memory for file name\n");
        return NULL;
    }
    return fileName;
}

char* getParentPathFromPath(char* path) {
    const char* last = strrchr(path, '/');
    if (last == NULL) {
        char* empty = strdup("");
        if (empty == NULL) {
            return NULL;
        }
        return empty;
    }
    int n = last - path;
    char* parentPath = malloc(n + 1);
    if (parentPath == NULL) {
        fprintf(stderr, "Unable to allocate memory for parent path\n");
        return NULL;
    }
    memcpy(parentPath, path, n);
    parentPath[n] = '\0';
    return parentPath;
}

bool canDelete(VFSObj* vfs, bool isDirectory, FileNode* file, char* path) {
    if (file == NULL) {
        printf("Error: no such file: %s\n", path);
        return false;
    }

    if (isDirectory && !file->isDirectory) {
        printf("Error: cannot write to '%s', it is a directory\n", path);
        return false;
    }

    if (!isDirectory && file->isDirectory) {
        printf("Error: failed to remove '%s': Not a file\n", path);
        return false;
    }

    if (isDirectory && file == vfs->root) {
        printf("Error: cannot remove root '/'\n", path);
        return false;
    }

    if (isDirectory && file->children != NULL) {
        printf("Error: failed to remove '%s': Directory not empty\n", path);
        return false;
    }

    return true;
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
        free(parentPath);
    }

    file = malloc(sizeof(FileNode));
    if (file == NULL) {
        free(fileName);
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
            continue;
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

void displayFileNode(FileNode* file) {
    printf("name: %s\nisDir: %d\nchildren:%p\ncontent:%s\n\n", file->name, file->isDirectory, file->children, file->blocks);
}
