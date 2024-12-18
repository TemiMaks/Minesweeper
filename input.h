#ifndef INPUT_H
#define INPUT_H

void markCell(char **board, char **Player_board, int row, int col, int rows, int cols);
void showCell(bool *playState, char **board, char **Player_board, int row, int col, int rows, int cols);
void entry(char **board, char **Player_board, int rows, int cols, int level, int bombNumber);


#endif //INPUT_H
