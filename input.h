#ifndef INPUT_H
#define INPUT_H
#include <stdbool.h>

void markCell(char **Player_board, int row, int col, int rows, int cols);
void showCell(bool *playState, char **board, char **Player_board, int row, int col, int rows, int cols, int bombNumber);
void showFreeCells(char **board, char **Player_board, int row, int col, int rows, int cols);
void entry(char **Player_board, int rows, int cols, int level, int bombNumber);

#endif //INPUT_H
