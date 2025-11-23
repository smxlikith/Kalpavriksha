#ifndef MEM_BLOCK_H
#define MEM_BLOCK_H

#define BLOCK_SIZE 512

#define MIN_BLOCKS 1
#define MAX_BLOCKS 5000

typedef struct Block Block;

struct Block {
    unsigned int currSize;
    unsigned int index;
    Block* prev;
    Block* next;
    char* data;
};

char** initVirtualDisk(int numberOfBlocks);
void freeVirtualDisk(char** virtualDisk, int numberOfBlocks);
Block* initMemoryBlocks(int numberOfBlocks, char** memoryBlocks);
Block* allocateBlocks(Block** freeBlocksList, unsigned int size);
void addBlocks(Block* newBlocks, Block* currBlocks);
void deallocateBlocks(Block** freeBlocksList, Block* blocks);
void freeBlocks(Block* blocks);
#endif