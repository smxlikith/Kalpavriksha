# LRU Cache Implementation using HashMap and Queue

This project is an **LRU (Least Recently Used) Cache Implementation** in C.
It manages frequently accessed data efficiently using **HashMap** and a **custom Queue (Doubly Linked List)**, enabling **O(1) operations** for both retrieval and insertion.

## Features

### **Cache Initialization**

- Initializes the cache with a **positive capacity**.
- Builds the cache using:

  - **HashMap**: Maps keys to queue nodes for fast lookup.
  - **Queue (Doubly Linked List)**: Maintains usage order:

    - **Front (Head)** → Most Recently Used (MRU)
    - **Rear (Tail)** → Least Recently Used (LRU)

### **1. Get Value by Key**

- Value if the key exists in the cache.
- `null` if the key is not found.

- Updates the node as **most recently used** if found.
- Operates in **O(1) time**.

### **2. Insert or Update Key-Value Pair**

- Updates value if key exists.
- Adds key-value pair if key is new.
- Evicts **least recently used (LRU)** key if cache exceeds capacity.
- operates in **O(1) time**.

### **3. Cache Constraints**

- Capacity: `1 ≤ capacity ≤ 1000`
- Keys: Integers
- Values: Strings
- All operations are **O(1)**.

## Usage

### **1. Compile the Program**

```bash
gcc LRUCache.c \
    lib/hashmap.c \
    lib/queue.c \
    lib/commands.c \
    lib/userInput.c \
    -o ./out/LRUCache
```

### **2. Run the Program**

```bash
./out/LRUCache
```

### **3. Input Commands**

```
createCache <size>
put <key> <data>
get <key>
```

### **4. Output**

- Prints the value retrieved for `get <key>`.
- Prints `null` if the key is not found.
