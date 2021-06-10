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
#define ADDRESS_LEN 10

typedef struct Memory
{
    char *memory;
    int data[BYTE_LEN];
    int address[ADDRESS_LEN];
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
void numToBinary(int num, int *arr, int digits);

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
                getchar();
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
                system("cls");
                outputMemoryIC(memIC, 0);
                break;
            default:
                destoryMemory(memIC);
                return 0;
        }
        system("cls");
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
    system("cls");
    Sleep(1000);    // Reduce virual conflict.
    while (a->memory[i] != '\0')
    {
        system("cls");
        printf("Reading : ");
        for (int j = 0; j < i; j++)
            printf("%c", a->memory[j]);
        printf("\n");
        numToBinary(i, a->address, ADDRESS_LEN);
        numToBinary(a->memory[i], a->data, BYTE_LEN);
        outputMemoryIC(a, 1);
        i++;
    }
}

void writeMemory(Memory *a, char s[], int len)
{
    a->read = 0;
    a->write = 1;
    for (int i = 0; i < len; i++)
    {
        system("cls");
        printf("Writting : ");
        for (int j = 0; j < i; j++)
            printf("%c", s[j]);
        printf("\n");
        a->memory[i] = s[i];
        numToBinary(i, a->address, ADDRESS_LEN);
        numToBinary(s[i], a->data, BYTE_LEN);
        outputMemoryIC(a, 1);
    }
    a->memory[len] = '\0';
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
    {
        printf("******************************************************************************\n");
        printf("            |    |    |    |    |    |    |    |    |    |    0V             \n");
    }
    else
    {
        printf("            %1d    %1d", a->read, a->write);
        for (int i = BYTE_LEN - 1; i >= 0; i--)
            printf("    %1d", a->data[i]);
        printf("    0V             \n");
    }
    printf("       _____|____|____|____|____|____|____|____|____|____|____|_____         \n");
    printf("      |    RD    WR   d7   d6   d5   d4   d3   d2   d1   d0   GND   |        \n");
    printf("      |\\                                                            |        \n");
    printf("      |/                                                            |        \n");
    printf("      |____VCC___a9___a8___a7___a6___a5___a4___a3___a2___a1___a0____|        \n");
    printf("            |    |    |     |    |    |    |    |    |    |    |              \n");
    if (opearte == 0)
    {
        printf("           +5V   |    |     |    |    |    |    |    |    |    |              \n");
        printf("------------------------------------------------------------------------------\n");
        printf("   RD    :  Status of read signal.                                            \n");
        printf("   WR    :  Status of write signal.                                           \n");
        printf("  d(0-8) :  Status of data translate interfaces.                              \n");
        printf("  a(0-8) :  Status of address translate interfaces.                           \n");
        printf(" VCC/GND :  Status of power.                                                  \n");
        printf("******************************************************************************\n");
        Sleep(4000);
    }
    else
    {
        printf("           +5V");
        for (int i = ADDRESS_LEN - 1; i >= 0; i--)
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
    printf("* 2. Watch the process of writting this string.            *\n");
    printf("* 3. Watch the process of reading this string.             *\n");
    printf("* 4. Put a void memory IC.                                 *\n");
    printf("* 5. Quit this program.                                    *\n");
    printf("************************************************************\n");
    printf("Please input your choice :  ");
}

void numToBinary(int num, int *arr, int digits)
{
    for (int i = 0; i < digits; i++)
    {
        arr[i] = num & 1;
        num >>= 1;
    }
}
