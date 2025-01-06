#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "board.h"
#include "input.h"
#include "playerInfo.h"
#include "file.h"

int main(int argc, char **argv) {
    //Sprawdzam czy uzytkownik chce skorzystac z trybu wczytywania pliku
    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        // Sprawdzenie, czy plik ma rozszerzenie .txt
        const char *file = argv[2];
        size_t len = strlen(file);
        if (len > 4 && strcmp(file + len - 4, ".txt") == 0) {
            printf("Tryb czytania z pliku\n");
            char **fileBoard = loadFromFile(argv[2]);
        }



    }
printf("%d",argc);
printf("%s",argv[1]);
printf("%s",argv[2]);

    srand(time(NULL));
    printf("Prosze podac poziom trudnosci 1-3: ");
    int level;
    int rows = 0, cols = 0, bombNumber = 0;

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
