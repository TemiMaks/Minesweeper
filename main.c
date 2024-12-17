#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"
#include "input.h"
#include "playerInfo.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    int level = (argc > 1 && atoi(argv[1]) >= 1 && atoi(argv[1]) <= 3) ? atoi(argv[1]) : 2;

    int rows = 0, cols = 0, bombNumber = 0;

    // Ustawienie parametrów planszy
    setBoardParams(level, &rows, &cols, &bombNumber);

    char **board = initializeBoard(level, rows, cols);
    char **Player_board = initializePlayerBoard(level, rows, cols);

    // Rozmieszczanie bomb
    placeBombs(board, rows, cols, bombNumber);

    // Zapisanie komorek z 'liczbami' bomb
    solveBoard(board, rows, cols);

    system("clear"); // Wyczyszczenie ekranu przed rozpoczeciem
    entry(board, Player_board, rows, cols);  //To zasadniczo trzyma cala gre- analizuje inputy i konczy jak trafi na bombe

    //Uzytkownik
    int score = getScore(Player_board, level, rows, cols);
    getPlayerInfo(score);

    //Uzytkownik
    getScore(Player_board, level, rows, cols);
    Info *Player = getPlayerInfo();

    //Zwolnienie pamieci
    freeBoard(board, rows);
    freeBoard(Player_board, rows);

    free(Player);

    return 0;
}
