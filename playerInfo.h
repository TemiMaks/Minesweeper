#ifndef PLAYERINFO_H
#define PLAYERINFO_H

typedef struct playerInfo{
    char name[25];
    int UID;
    int score;
} Info;


int getScore(char **Player_board, int level, int rows, int cols);
Info* getPlayerInfo();

#endif //PLAYERINFO_H
