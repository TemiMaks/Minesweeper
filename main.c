#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"
#include "input.h"



int main() {
    int level=2;
    srand(time(NULL));

    int rows = 0, cols = 0, bombNumber = 0;

    // Ustawienie parametrów planszy
    setBoardParams(level, &rows, &cols, &bombNumber);

    char **board = initializeBoard(level, rows, cols);
    char **Player_board = initializeBoard(level, rows, cols);

    // Rozmieszczanie bomb
    placeBombs(board, rows, cols, bombNumber);

    //Logika gry
    bool playState = true;
    while (playState == true) {
        //Wyswietlanie aktualnej planszy
        showCurrentBoard(Player_board, rows, cols);
        entry(&playState, board, Player_board, rows, cols);  //To zasadniczo trzyma cala gre- analizuje inputy i konczy jak trafi na bombe
    }
    //Wyswietlenie planszy koncowej
    printf("Plansza koncowa\n");
    showCurrentBoard(board,rows,cols);

    //Zwolnienie pamieci
    freeBoard(board, rows);
    freeBoard(Player_board, rows);


    return 0;
}