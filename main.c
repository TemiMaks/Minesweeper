#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"
#include "input.h"
#include "playerInfo.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    printf("Prosze podac poziom trudnosci 1-3: ");
    int level;

    // Sprawdzenie, czy podano liczbę
    while (scanf("%d", &level) != 1) {
        printf("Bledny argument, podaj poprawny: ");
        while (getchar() != '\n'); // Czyści bufor wejściowy
    }

    // Sprawdzenie zakresu liczby
    while (level < 1 || level > 3) {
        printf("Liczba poza zakresem, podaj poprawna (1-3): ");
        while (scanf("%d", &level) != 1) {
            printf("Bledny argument, podaj poprawny: ");
            while (getchar() != '\n'); // Czyści bufor wejściowy
        }
    }

    int rows = 0, cols = 0, bombNumber = 0;

    // Ustawienie parametrów planszy
    setBoardParams(level, &rows, &cols, &bombNumber);

    char **board = initializeBoard(level, rows, cols, bombNumber);
    char **Player_board = initializePlayerBoard(level, rows, cols);

    system("clear"); // Wyczyszczenie ekranu przed rozpoczeciem
    entry(board, Player_board, rows, cols, level, bombNumber);  //To zasadniczo trzyma cala gre- analizuje inputy i konczy jak trafi na bombe

    //Uzytkownik
    int score = getScore(Player_board, level, rows, cols);
    Info *Player = getPlayerInfo(score);
    printFile();

    //Zwolnienie pamieci
    freeBoard(board, rows);
    freeBoard(Player_board, rows);

    free(Player);

    return 0;
}
