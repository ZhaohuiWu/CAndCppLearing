/********************************************************************++
 *   Copyright (c) 2021     All rights reserved.
 * -------------------------------------------------------------------
 * Author   :   Mark Wu
 * Summary  :   A file compression program based on RLE algorithm.
--********************************************************************/

#if 1   // Preprocessing operation and data structure definition.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIR 1024
#define MAX_FILE_NAME 512
#define MAX_FILE_SUFFIX 16
#define SUFFIX_NAME "ys"
#define SUCCESS 1
#define FAILURE 0

typedef struct fileInfo
{
    char directory[MAX_DIR];
    char name[MAX_FILE_NAME];
    char suffix[MAX_FILE_SUFFIX];
    FILE *fp;
}fileInfo;
typedef status int;

#endif

#if 1   // The declarations of functions.

void putMenu(void);
fileInfo *initFile(void);
status getFileInfo(fileInfo * fileInfoPoint);
void destoryFile(fileInfo * fileInfoPoint);
void compressFile(fileInfo * file);
void decompressFile(fileInfo * file);

#endif

int main(void)
{
    int choice = 0;
    fileInfo opeateFile = initFile();
    while (1)
    {
        putMenu();
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                while (1)
                {
                    if (getFileInfo(opeateFile))
                    {
                        compressFile(opeateFile);
                        break;
                    }
                    else
                    {
                        printf("[ERROR]: Directory or file name input error!\n");
                        printf("Reinput(1) or quit input(0) ?")
                        scanf("%d", &choice);
                        if (!choice)
                            break;
                    }
                }
                break;
            case 2:
                while (1)
                {
                    if (getFileInfo(opeateFile) && strcmp(opeateFile.suffix, SUFFIX_NAME) == 0)
                    {
                        deCompressFile(opeateFile);
                        break;
                    }
                    else
                    {
                        printf("[ERROR]: Directory or file name input error!\n");
                        printf("Reinput(1) or quit input(0) ?")
                        scanf("%d", &choice);
                        if (!choice)
                            break;
                    }
                }
            default:
                destoryFile(opeateFile);
                return 0;
        }
    }
}

void putMenu(void)
{
    printf("***********************************\n");
    printf("-  1. Compress a file.            -\n");
    printf("-  2. Decompress a file.          -\n");
    printf("-  3. Quit this program.          -\n");
    printf("***********************************\n");
    printf("Please input your choice : ");
}

fileInfo *initFile(void)
{
    fileInfo *t = (fileInfo *)malloc(sizeof(fileInfo));
    memset(t->directory, '\0', sizeof t->directory);
    memset(t->name, '\0', sizeof t->name);
    memset(t->suffix, '\0', t->suffix);
    t->fp = NULL;
    return t;
}

status getFileInfo(fileInfo *fileInfoPoint)
{
    char dir[MAX_DIR], fileName[MAX_FILE_NAME + MAX_FILE_SUFFIX];
}

void destory(fileInfo * fileInfoPoint)
{
    fileInfoPoint.fp = NULL;
    free(fileInfoPoint);
    fileInfoPoint = NULL;
}