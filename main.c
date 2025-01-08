#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"
#include "input.h"
#include "playerInfo.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    int level = (argc > 1 && atoi(argv[1]) >= 1 && atoi(argv[1]) <= 4) ? atoi(argv[1]) : 2;

    int rows = 0, cols = 0, bombNumber = 0;

    // Ustawienie parametrów planszy
    setBoardParams(level, &rows, &cols, &bombNumber);

    char **Player_board = initializePlayerBoard(rows, cols);

    system("clear"); // Wyczyszczenie ekranu przed rozpoczeciem
    entry(Player_board, rows, cols, level, bombNumber);  //To zasadniczo trzyma cala gre- analizuje inputy i konczy jak trafi na bombe

    //Uzytkownik
    int score = getScore(Player_board, level, rows, cols);
    Info *Player = getPlayerInfo(score);

    //Zwolnienie pamieci
    freeBoard(Player_board, rows);

    free(Player);

    return 0;
}
