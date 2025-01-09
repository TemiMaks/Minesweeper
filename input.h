#ifndef INPUT_H
#define INPUT_H
#include <stdbool.h>

void markCell(char **board, char **Player_board, int row, int col, int rows, int cols);
void showCell(bool *playState, char **board, char **Player_board, int row, int col, int rows, int cols, int bombNumber);
void showFreeCells(char **board, char **Player_board, int row, int col, int rows, int cols);
void entry(char **board, char **Player_board, int rows, int cols, int bombNumber);
int entryFromFile(char **board, char **Player_board, int rows, int cols, int bombNumber, char moveType, int row, int col);
void getCorrectInputs(char **Player_board, int rows, int cols, int bombNumber);
void markCellFromFile(char **Player_board, int row, int col, int rows, int cols);
void showCellFromFile(bool *playState, char **board, char **Player_board, int row, int col, int rows, int cols, int bombNumber);

#endif //INPUT_H
