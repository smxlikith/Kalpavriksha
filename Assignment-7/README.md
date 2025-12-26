# ICC ODI Player Performance Analyzer

This project is an **ICC ODI Player Performance Analyzer** implemented in C.
It manages and analyzes international ODI cricket player statistics using **Searching**, **Sorting**, and **Linked List** concepts.
The system loads **200 predefined players from 10 teams** and allows users to explore and analyze player and team performance efficiently.

## Features

### **Player & Team Initialization**

- Automatically loads **200 players** and **10 teams** from `Players_data.h`.
- Builds Player and Team objects using independent structures defined in the program.

### **1. Display Players of a Specific Team**

- Shows:

  - All players of that team
  - Total number of players
  - Average batting strike rate (batters + all-rounders)

### **2. Sort & Display Teams by Batting Strike Rate**

- Teams are displayed in **descending order** of average batting strike rate.

### **3. Display Top K Players of a Team by Role**

- Display the **top K**:

  - Batsmen
  - Bowlers
  - All-rounders

- Ranked by **Performance Index** (calculated differently for each role).
- Guaranteed **O(K)** retrieval using proper pre-sorted structures or linked-list design.

### **4. Display Players Across All Teams by Role**

- Displays all players of a selected role across all teams.
- Sorted by performance index in descending order.
- Achieves **O(N log t)** complexity using an extra consolidated list and team-based sorting.

## Usage

### **1. Compile the Program**

```bash
gcc ODIPlayerPerformanceAnalyzer.c \
    lib/player.c \
    lib/team.c \
    lib/commands.c \
    lib/heapSort.c \
    -o ./out/ODIPlayerPerformanceAnalyzer
```

### **2. Run the Program**

```bash
./out/ODIPlayerPerformanceAnalyzer
```
