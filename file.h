#ifndef FILE_H
#define FILE_H

void loadFromFile(const char *filename, int *bombNumber);
int combineDigits(int *entry, int digit);
int recursiveCase(char *buff, int j, int *entry);
char **AllocateMemory(int rows_mem, int cols_mem);
void reallocateRowsMemory(char ***board, int rows, int cols, int *rows_mem, int *cols_mem);
void reallocateColsMemory(char **board, int *rows_mem, int rows, int *cols_mem);

#endif //FILE_H
