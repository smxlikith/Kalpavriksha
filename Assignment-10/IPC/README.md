# Part 1 — Interprocess Communication (IPC) Programs

Short summary: this project implements four IPC mechanisms in C (file, message queue, pipe, shared memory). Each mechanism has two programs (p1 and p2); p1 reads/displays the integer array before sorting, p2 sorts the data and provides it back to p1. A small helper library (lib/ipcUtils.c/h) is shared by the programs.

## Project structure

```bash
.
├── lib
│   ├── ipcUtils.c
│   └── ipcUtils.h
├── file
│   ├── data.txt
│   ├── out
│   │   ├── p1
│   │   └── p2
│   ├── p1.c
│   └── p2.c
├── messageQueue
│   ├── mqfile
│   ├── out
│   │   ├── p1
│   │   └── p2
│   ├── p1.c
│   └── p2.c
├── pipe
│   ├── out
│   │   ├── p1
│   │   └── p2
│   ├── p1.c
│   └── p2.c
├── sharedMemory
│   ├── out
│   │   ├── p1
│   │   └── p2
│   ├── p1.c
│   └── p2.c
└── README.md
```

## Build & run (file-based IPC)

To see the file-based IPC in action:

1. Change into the file directory:
   cd file

2. Build the two programs (helper is in ../lib):
   gcc -Wall -Wextra -std=gnu11 -I../lib ../lib/ipcUtils.c p1.c -o out/p1
   gcc -Wall -Wextra -std=gnu11 -I../lib ../lib/ipcUtils.c p2.c -o out/p2

3. Run the programs (in separate terminals or background p1):
   ./out/p1 # prints "Before sort", waits for sorted result
   ./out/p2 # reads, sorts, writes result back

Quick tips

- Redirect output for automated runs:
  ./out/p1 > out/p1.log 2>&1 &
  ./out/p2 > out/p2.log 2>&1
- Ensure input (e.g., file/data.txt) exists if p1 reads it.
- Clean up binaries when done:
  rm out/p1 out/p2

If you want concise build/run lines for messageQueue, pipe, or sharedMemory next, tell me which one.
