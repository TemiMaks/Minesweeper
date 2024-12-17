
#ifndef BOARD_H
#define BOARD_H

int getRandomNumber(int min, int max);
void setBoardParams(int level, int *rows, int *cols, int *bombNumber);
void placeBombs(char **board, int rows, int cols, int bombNumber);
void showCurrentBoard(char **board, int rows, int cols);
char** initializeBoard(int level, int rows, int cols);
void freeBoard(char **board, int rows);

#endif //BOARD_H
