# Virtual File System (VFS)

This project implements a **Virtual File System (VFS)** that simulates an in-memory file storage environment using **circular** and **doubly linked lists**. The system allows users to create, read, write, and manage files and directories, mimicking the structure and behavior of an actual file system.

## Features

- **Circular and Doubly Linked Lists**: Core data structures used to simulate file and directory management.
- **Free Block Management**: Manages free disk blocks using a doubly linked list, simulating allocation and deallocation.
- **File and Directory Operations**: Supports common file system operations like creating files, writing/reading content, deleting files, and managing directories.
- **Current Working Directory (CWD)**: Tracks the user's current location in the file system.

### Operations Supported:

- **mkdir** – Creates a new directory under the current directory.
- **create** – Creates a new file under the current directory.
- **write** – Allocates blocks for a file, writes content to disk, and updates file pointers.
- **read** – Reads file content by traversing block pointers.
- **delete** – Deletes a file, removes it from the directory, and returns its blocks to the free block list.
- **rmdir** – Removes an empty directory.
- **ls** – Lists files and directories in the current directory.
- **cd** – Changes the current working directory.
- **pwd** – Displays the current directory path.
- **df** – Displays disk usage (total, used, and free blocks).
- **exit** – Frees memory, clears linked lists, and exits the program.

## Compilation and Execution

### 1. Compile the Program

```bash
gcc -g lib/commands.c lib/fileSystem.c lib/memBlock.c lib/userInput.c virtualFileSystem.c -o out/vfs
```

### 2. Run the Program

```bash
./out/vfs 1024
```

## Implementation Details

- The VFS simulates a file system environment entirely in memory using linked lists.
- **Circular Linked Lists** manage directories and their contents.
- **Doubly Linked Lists** are used for managing free disk blocks.
- Supports dynamic memory management, ensuring efficient storage handling.
