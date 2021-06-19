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
#define COUNTER_MAX 255
#define SIZE_CNT 1
#define SUFFIX_NAME "rlec"
#define OPEN_SUCCESS 1
#define OPEN_FAILURE 0

typedef struct fileInfo
{
    char directory[MAX_DIR];
    char name[MAX_FILE_NAME];
    char suffix[MAX_FILE_SUFFIX];
    FILE *fp;
}fileInfo;
typedef int status;
typedef unsigned char buffElem;
typedef unsigned char countElem;

#endif

#if 1   // The declarations of functions.

void putMenu(void);
fileInfo *initFIleInfo(void);
void getFileLoc(char dir_Destination[], char * directory, char * fileName, const char * fileSuffix);
status getFileInfo(fileInfo * fileInfoPoint);
void destoryFileInfo(fileInfo * fileInfoPoint);
void compressFile(fileInfo * file);
void deCompressFile(fileInfo * file);

#endif

int main(void)
{
    int choice = 0;
    fileInfo *opeateFile = initFIleInfo();
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
                        printf("Reinput(1) or quit input(0) ?");
                        scanf("%d", &choice);
                        if (!choice)
                            break;
                    }
                }
                break;
            case 2:
                while (1)
                {
                    if (getFileInfo(opeateFile) && strcmp(opeateFile->suffix, SUFFIX_NAME) == 0)
                    {
                        deCompressFile(opeateFile);
                        break;
                    }
                    else
                    {
                        printf("[ERROR]: Directory or file name input error!\n");
                        printf("Reinput(1) or quit input(0) ?");
                        scanf("%d", &choice);
                        if (!choice)
                            break;
                    }
                }
            default:
                destoryFileInfo(opeateFile);
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

fileInfo *initFIleInfo(void)
{
    fileInfo *t = (fileInfo *)malloc(sizeof(fileInfo));
    memset(t->directory, '\0', sizeof t->directory);
    memset(t->name, '\0', sizeof t->name);
    memset(t->suffix, '\0', sizeof t->suffix);
    t->fp = NULL;
    return t;
}

status getFileInfo(fileInfo *fileInfoPoint)
{
    int dotLoc = -1;
    char directory[MAX_DIR + MAX_FILE_NAME + MAX_FILE_SUFFIX + 2];
    char dir[MAX_DIR], fileName[MAX_FILE_NAME + MAX_FILE_SUFFIX];
    printf("Please input the directory of goal file  : \n");
    scanf("%s", dir);
    strcpy(fileInfoPoint->directory, dir);
    printf("Please input the name of goal name  :\n");
    scanf("%s", fileName);
    for (int i = strlen(fileName) - 1; i >= 0; i--)
        if (fileName[i] == '.')
        {
            dotLoc = i;
            fileName[dotLoc] = '\0';
            break;
        }
    if (dotLoc == -1)
        strcpy(fileInfoPoint->name, fileName);
    else
    {
        strcpy(fileInfoPoint->name, fileName);
        fileName[dotLoc] = '.';
        strcpy(fileInfoPoint->suffix, fileName + dotLoc + 1);
    }
    
    getFileLoc(directory, dir, fileInfoPoint->name, fileInfoPoint->suffix);
    if ((fileInfoPoint->fp = fopen(directory, "rb")) == NULL)
        return OPEN_FAILURE;
    else
    {
        fclose(fileInfoPoint->fp);
        return OPEN_SUCCESS;
    }
}

void destoryFileInfo(fileInfo * fileInfoPoint)
{
    fileInfoPoint->fp = NULL;
    free(fileInfoPoint);
    fileInfoPoint = NULL;
}

void compressFile(fileInfo * file)
{
    char directory[MAX_DIR + MAX_FILE_NAME + MAX_FILE_SUFFIX + 2];
    getFileLoc(directory, file->directory, file->name, SUFFIX_NAME);
    FILE *read_fp = file->fp;
    FILE *write_fp = fopen(directory, "wb");
    buffElem predata, data;
    countElem counter = 1;
    fread(&predata, sizeof(buffElem), SIZE_CNT, read_fp);
    printf("%d %d\n", predata, counter);
    while ((fread(&data, sizeof(buffElem), SIZE_CNT, read_fp)) == SIZE_CNT)
    {
        if ((data ^ predata) == 0 && counter < COUNTER_MAX)
            counter++;
        else
        {
            printf("%d %d\n", predata, counter);
            fwrite(&predata, sizeof(buffElem), SIZE_CNT, write_fp);
            fwrite(&counter, sizeof(countElem), SIZE_CNT, write_fp);
            predata = data;
            counter = 1;
        }
    }
    printf("%d %d\n", predata, counter);
    fwrite(&predata, sizeof(buffElem), SIZE_CNT, write_fp);
    fwrite(&counter, sizeof(countElem), SIZE_CNT, write_fp);
    fclose(file->fp);
    fclose(write_fp);
}

void deCompressFile(fileInfo * file)
{}

void getFileLoc(char dir_Destination[], char * directory, char * fileName, const char * fileSuffix)
{
    memset(dir_Destination, '\0', MAX_DIR + MAX_FILE_NAME + MAX_FILE_SUFFIX + 2);
    strcpy(dir_Destination, directory);
    strcat(dir_Destination, "\\");
    strcat(dir_Destination, fileName);
    strcat(dir_Destination, ".");
    strcat(dir_Destination, fileSuffix);
}