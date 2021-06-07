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
#include <windows.h>

#define MEMORY_SIZE_MAX 1024
#define BYTE_LEN 8

typedef struct Memory
{
    char *memory;
    int data[BYTE_LEN];
    int address[BYTE_LEN];
    bool read;
    bool write;
} Memory;

#endif

#if 1 // Declare the function used.

Memory *createMemory(void);
void destoryMemory(Memory *a);
void outputMemoryIC(Memory *a, int opearte);
void putMenu(void);
void readMemory(Memory *a);
void writeMemory(Memory *a, char s[], int len);
void numToBinary(int num, int * arr);

#endif

int main(void)
{
    Memory *memIC = createMemory();
    char str[MEMORY_SIZE_MAX];

    while (1)
    {
        int choice = 1;
        putMenu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            gets(str);
            strcpy(memIC->memory, str);
            break;
        case 2:
            readMemory(memIC);
            break;
        case 3:
            writeMemory(memIC, str, strlen(str));
            break;
        case 4:
            // memset(memIC->data, -1, sizeof memIC->data);
            // memset(memIC->address, -1, sizeof memIC->address);
            outputMemoryIC(memIC, 0);
            break;
        default:
            destoryMemory(memIC);
            return 0;
        }
    } // while end
}

// Instantiate a memory object.
Memory *createMemory(void)
{
    Memory *a = (Memory *)malloc(sizeof(Memory));
    a->memory = (char *)malloc(sizeof(char) * MEMORY_SIZE_MAX);
    return a;
}

void readMemory(Memory *a)
{
    a->read = 1;
    a->write = 0;
    int i = 0;
    while (a->memory[i] != '\n')
    {
        printf("Reading : ");
        for (int j = 0; j < i; j++)
            printf("%c", a->memory[j]);
        printf("\n");
        numToBinary(i, a->address);
        numToBinary(a->memory[i], a->data);
        outputMemoryIC(a, 1);
        system("cls");
    }
}

void writeMemory(Memory *a, char s[], int len)
{
    a->read = 0;
    a->write = 1;
    for (int i = 0; i < len; i++)
    {
        printf("Writting : ");
        for (int j = 0; j < i; j++)
            printf("%c", s[j]);
        printf("\n");

        a->memory[i] = s[i];
        numToBinary(i, a->address);
        numToBinary(s[i], a->data);
        outputMemoryIC(a, 1);
        system("cls");
    }
    a->memory[len] = '\n';
}


// Destory the memory occupied by imitation memory.
void destoryMemory(Memory *a)
{
    free(a->memory);
    a->memory = NULL;
    free(a);
    a = NULL;
}

// Output status of memory IC.
// Opearte  : One stands status of now, zero stands void.
void outputMemoryIC(Memory *a, int opearte)
{
    if (opearte == 0)
        printf("            |    |    |    |    |    |    |    |    |              \n");
    else
    {
        printf("            %d", a->read);
        for (int i = BYTE_LEN; i >= 0; i--)
            printf("    %1d", a->data[i]);
        printf("              \n");
    }
    printf("      ______|____|____|____|____|____|____|____|____|______        \n");
    printf("      |    RD    d7   d6   d5   d4   d3   d2   d1   d0    |        \n");
    printf("      |\\                                                  |        \n");
    printf("      |/                                                  |        \n");
    printf("      |____WR____a7___a6___a5___a4___a3___a2___a1___a0____|        \n");
    printf("            |    |    |    |    |    |    |    |    |              \n");
    if (opearte == 0)
    {
        printf("            |    |    |    |    |    |    |    |    |              \n");
        Sleep(2000);
    }
    else
    {
        printf("            %d", a->write);
        for (int i = BYTE_LEN; i >= 0; i--)
            printf("    %1d", a->address[i]);
        printf("              \n");
    }
    Sleep(1000);
}

// Process of Menu format printing.
void putMenu(void)
{
    printf("************************************************************\n");
    printf("*         Welcome to 1KB memory display program!           *\n");
    printf("*----------------------------------------------------------*\n");
    printf("* 1. Input a string, which length between 0 and 1024.      *\n");
    printf("* 2. Watch the process of storing this string.             *\n");
    printf("* 3. Watch the process of reading this string.             *\n");
    printf("* 4. Put a void memory IC.                                 *\n");
    printf("* 5. Quit this program.                                    *\n");
    printf("************************************************************\n");
    printf("Please input your choice :  ");
}

void numToBinary(int num, int * arr)
{
    for (int i = 0; i < 8; i++)
    {
        arr[i] = num & 1;
        num >>= 1;
    }
}