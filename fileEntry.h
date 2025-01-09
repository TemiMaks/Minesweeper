#ifndef FILEENTRY_H
#define FILEENTRY_H

#include "board.h"
#include "playerInfo.h"
#include "input.h"
#include <stdbool.h>

int entryFromFile(char **board, char **Player_board, int rows, int cols, int bombNumber, char moveType, int row, int col, int buffLine);
void getCorrectInputs(char **Player_board, int rows, int cols, int bombNumber);
void markCellFromFile(char **Player_board, int row, int col, int rows, int cols, int buffLine);
void showCellFromFile(int *playState, char **board, char **Player_board, int row, int col, int rows, int cols, int bombNumber, int buffLine);


#endif //FILEENTRY_H
