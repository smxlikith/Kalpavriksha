# FCFS-Based OS Process Scheduling Simulator

This project implements a **First-Come-First-Serve (FCFS)** based **Operating System Process Scheduler** in C.
The simulator models how an operating system manages processes using **Process Control Blocks (PCB)**, **queues**, and a **system clock**, closely mimicking real OS scheduling behavior.

The scheduler supports **CPU burst execution**, **I/O blocking**, **parallel I/O handling**, and **process termination**, including **kill events** at specific clock ticks.

## Features

- **FCFS Scheduling**: Processes are executed strictly in the order they arrive in the ready queue.
- **Process Control Block (PCB)**: Stores all metadata related to a process (PID, name, burst time, I/O info, status, etc.).
- **Queue-Based State Management**:

  - Ready Queue
  - Waiting (I/O) Queue
  - Terminated Queue

- **System Clock Simulation**: Uses `sleep(1)` to simulate CPU cycles.
- **I/O Handling**:

  - Processes move to waiting queue on I/O request
  - I/O of all waiting processes executes in parallel

- **Kill Events**:

  - Processes can be terminated at a specific clock tick
  - Kill events are applied at the **start of the specified tick**

- **Execution Metrics**:

  - Turnaround Time
  - Waiting (Response) Time
  - CPU Burst Time
  - I/O Time
  - Process Status (OK / KILLED)

## Key Concepts Implemented

- **CPU Burst**
  Time spent actively executing on the CPU (computation only).

- **I/O Burst**
  Time spent waiting for I/O operations (disk, network, system calls).

- **Process States**

  - Ready
  - Running
  - Waiting (I/O)
  - Terminated

- **System Clock**
  Drives execution, I/O progression, scheduling decisions, and kill events.

## Input Specification

### Process Input Format

```
<process_name> <pid> <burst_time> <io_start_time> <io_duration>
```

### Kill Command Format

```
KILL <PID> <kill_time>
```

### Example Input

```
chrome 101 10 4 3
vscode 102 8 3 2
terminal 103 6 2 3
spotify 104 5 0 0
notepad 105 7 5 2
KILL 102 7
KILL 105 10
```

## Scheduling Behavior

1. **Process Initialization**

   - All processes arrive at time `0`
   - Stored in PCB structures
   - Initially placed in the Ready Queue

2. **Process Execution**

   - Scheduler selects the next process using FCFS
   - CPU burst is simulated one unit per tick using `sleep(1)`
   - Execution time is tracked per process

3. **I/O Handling**

   - When a process reaches its I/O start time:

     - It is moved to the Waiting Queue

   - I/O durations of all waiting processes are decremented every tick
   - Upon I/O completion, the process returns to the Ready Queue

4. **Termination**

   - A process terminates when:

     - CPU burst finishes → status `OK`
     - Kill event occurs → status `KILLED at <time>`

   - Terminated processes are moved to the Terminated Queue

## Output

After all processes terminate, the simulator displays:

- **PID**
- **Process Name**
- **Total CPU Burst Time**
- **Total I/O Time**
- **Status** (OK / KILLED at time)
- **Turnaround Time**
- **Waiting Time (Response Time)**

> **Note**: Since all processes arrive at time 0,
> Turnaround Time = Completion Time

## Compilation and Execution

### Compile the Program

```bash
gcc fcfsScheduler.c lib/processesInput.c lib/queue.c lib/scheduler.c -o out/fcfsScheduler
```

### Run the Program

```bash
./out/fcfs_scheduler
```
