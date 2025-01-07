#ifndef PLAYERINFO_H
#define PLAYERINFO_H

typedef struct playerInfo{
    char name[25];
    int UID;
    int score;
} Info;

int getScore(char **Player_board, int level, int rows, int cols);
void updateFile(Info *Player);
int compareScores(const void *a, const void *b);
Info *getPlayerInfo(int score);
int generateUniqueUID();
int isUIDUnique(int uid);
int didWin(char **Player_board, int bombNumber, int rows, int cols);
void printFile();

#endif //PLAYERINFO_H
