#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "board.h"
#include "input.h"
#include "playerInfo.h"
#include "file.h"

int main(int argc, char **argv) {
    int opt;
    char *file = NULL;
    int bombNumber = 0;

    // Parsowanie argumentów za pomoca getopt
    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                file = optarg; // Pobranie nazwy pliku
                break;
            case '?':
                fprintf(stderr, "Nieznana opcja: -%c\n", optopt);
                return 1;
        }
    }

    // Sprawdzenie trybu pliku
    if (file) {
        // Sprawdzenie, czy plik ma rozszerzenie .txt
        size_t len = strlen(file);
        if (len > 4 && strcmp(file + len - 4, ".txt") == 0) {
            system("clear");
            printf("Tryb czytania z pliku: %s\n", file);
            int fileExit = loadFromFile(file, &bombNumber);
            return fileExit;
        } else {
            fprintf(stderr, "Plik musi miec rozszerzenie .txt\n");
            return 3;
        }
    }

    // Tryb standardowy (bez pliku)
    srand(time(NULL));
    printf("Prosze podac poziom trudnosci (1-4):\n"
           "1 - latwy (9x9, 10 bomb);\n"
           "2 - sredni (16x16, 40 bomb);\n"
           "3 - trudny (16x30, 99 bomb);\n"
           "4 - niestandardowy (dowolne wymiary i liczba bomb);");
    int level;
    int rows = 0, cols = 0;

    // Sprawdzenie, czy podano liczbe
    while (scanf("%d", &level) != 1) {
        printf("Bledny argument, podaj poprawny: ");
        while (getchar() != '\n'); // Czyści bufor wejściowy
    }

    // Sprawdzenie zakresu liczby
    while (level < 1 || level > 4) {
        printf("Liczba poza zakresem, podaj poprawna (1-4): ");
        while (scanf("%d", &level) != 1) {
            printf("Bledny argument, podaj poprawny: ");
            while (getchar() != '\n'); // Czyści bufor wejściowy
        }
    }

    // Ustawienie parametrów planszy
    setBoardParams(level, &rows, &cols, &bombNumber);
    char **Player_board = initializePlayerBoard(rows, cols);

    system("clear"); // Wyczyszczenie ekranu przed rozpoczeciem
    entry(Player_board, rows, cols, level, bombNumber);  //To zasadniczo trzyma cala gre- analizuje inputy i konczy jak trafi na bombe

    // Użytkownik
    int score = getScore(Player_board, level, rows, cols);
    Info *Player = getPlayerInfo(score);
    printFile();

    //Zwolnienie pamieci
    freeBoard(Player_board, rows);
    free(Player);

    return 0;
}
