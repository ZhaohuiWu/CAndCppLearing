/********************************************************************++
 *   Copyright (c) 2021     All rights reserved.
 * -------------------------------------------------------------------
 * Author   :   Mark Wu
 * Summary  :   1KB memory IC storage simulation display based on 
 *              linear structure
--********************************************************************/

#if 1 // Preprocessing operation and data structure definition.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MEMORY_SIZE_MAX 1024

typedef struct Memory
{
    char *memory;
    int data[8];
    int address[8];
    bool read;
    bool write;
} Memory;

#endif

#if 1 // Declare the function used.

Memory *createMemory(void);
void destoryMemory(Memory *a);
void outputMemoryIC(Memory *a);
void putMenu(void);

#endif

int main(void)
{
    Memory *memIC = createMemory();
    char str[MEMORY_SIZE_MAX];

    destoryMemory(memIC);
    return 0;
}

// Instantiate a memory object.
Memory *createMemory(void)
{
    Memory a = {NULL, {0}, {0}, false, false};
    a.memory = (Memory *)malloc(sizeof(Memory) * MEMORY_SIZE_MAX);
    return (&a);
}

// Destory the memory occupied by imitation memory.
void destoryMemory(Memory *a)
{
    free(a->memory);
}