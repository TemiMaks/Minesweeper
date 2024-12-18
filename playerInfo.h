#ifndef PLAYERINFO_H
#define PLAYERINFO_H

typedef struct playerInfo{
    char name[25];
    int UID;
    int score;
} Info;


int getScore(char **Player_board, int level, int rows, int cols, int bombCount);
void updateFile(Info *Player);
int compareScores(const void *a, const void *b);
Info *getPlayerInfo(int score);
int generateUniqueUID();
int isUIDUnique(int uid);

#endif //PLAYERINFO_H
