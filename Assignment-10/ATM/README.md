# ATM — Part 2: Socket-Based ATM Transaction Simulation

This README describes the TCP client-server ATM (Part 2) for assignment 10. The system simulates Withdraw, Deposit and Display operations over TCP. The server is multi-threaded (pthreads) and uses a mutex to protect a shared account data file.

Project structure

```bash
.
├── account.txt
├── client.c
├── lib
│   └── common.h
├── out
│   ├── client
│   └── server
├── README.md
└── server.c
```

Overview:

- Server:
  - Listens for TCP clients.
  - For every connection, spawns a pthread to handle the client request(s).
  - Reads/writes balance from account.txt.
  - Uses a mutex to synchronize file access and prevent race conditions.
  - Responds with success or error messages to the client.
- Client:
  - Connects to the server.
  - Shows a simple menu:
    1. Withdraw
    2. Deposit
    3. Display Balance
    4. Exit
  - Sends requests to server and displays server replies.

Account file format

- account.txt contains the current balance as a single integer number (example): 1000

Build

- Create the out directory if not already present:
  mkdir -p out
- Compile server:
  gcc -pthread -o out/server server.c
- Compile client:
  gcc -o out/client client.c

Run

- Start server:
  ./out/server
- Start client(s):
  ./out/client
