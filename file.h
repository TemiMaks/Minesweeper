#ifndef FILE_H
#define FILE_H
#include <stdio.h>

void freeResources(char **board, char **playerBoard, int rows_mem, int rows, FILE *file);
int loadFromFile(const char *filename, int *bombNumber);
int combineDigits(int *entry, int digit);
int recursiveCase(char *buff, int j, int *entry);
char **AllocateMemory(int rows_mem, int cols_mem);
void reallocateRowsMemory(char ***board, int rows, int cols, int *rows_mem, int *cols_mem);
void reallocateColsMemory(char **board, int *rows_mem, int rows, int *cols_mem);
int processMove(char* moveType,char** board, char** playerBoard, int rows, int max_cols, int *bombNumber, int *entryRow, int *entryCol, FILE* file, int buffLine, int rows_mem);

#endif //FILE_H
