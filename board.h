
#ifndef BOARD_H
#define BOARD_H

int getRandomNumber(int min, int max);
void setBoardParams(int level, int *rows, int *cols, int *bombNumber);
void placeBombs(char **board, int rows, int cols, int bombNumber);
void showBoard(char **board, int rows, int cols);
void initializeBoard(int level);

#endif //BOARD_H
