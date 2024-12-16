#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"


int main() {
    int level=1;
    srand(time(NULL));

    int rows = 0, cols = 0, bombNumber = 0;

    // Ustawienie parametrów planszy
    setBoardParams(level, &rows, &cols, &bombNumber);

    char **board = initializeBoard(level, rows, cols);

    // Rozmieszczanie bomb
    placeBombs(board, rows, cols, bombNumber);

    //Wyswietlenie planszy
    printf("Plansza koncowa\n");
    showBoard(board,rows,cols);

    //Zwolnienie pamieci
    freeBoard(board, rows);


    return 0;
}