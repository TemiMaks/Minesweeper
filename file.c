#include "file.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>

char** loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    printf("filename: %s\n", filename);
    if (file == NULL) {
        printf("[!] Blad otwarcia pliku.\n");
        exit(1);
    }

    // Alokacja pamięci dla planszy
    int rows_mem = 10, cols_mem = 10;
    char **board = (char **)malloc(rows_mem * sizeof(char *));

    // Sprawdzenie poprawności przypisania pamięci
    if (board == NULL) {
        printf("Blad alokacji pamieci!\n");
        return NULL;
    }

    for (int i = 0; i < rows_mem; i++) {
        board[i] = (char *)malloc(cols_mem * sizeof(char));    // Domyślnie 10x10 plansza
        if (board[i] == NULL) {
            printf("Blad alokacji dla rzedu %d!\n", i);
            return NULL;
        }
    }

    int rows = -1, cols = -1;
    char buff[1024]; // Do zapisu każdej linii
    while (fgets(buff, sizeof(buff), file)) {
      printf("%s\n", buff);
        int start = 0;
        cols = -1;  // Resetowanie kolumn dla nowego wiersza

        for (int i = 0; buff[i] != '\0'; i++) {
            if (buff[i] == '|') {
                start = 1;
                rows++;

                if (rows >= rows_mem) {
                    // Realokowanie pamięci dla wierszy
                    rows_mem *= 2;
                    board = (char **)realloc(board, rows_mem * sizeof(char *));
                    if (board == NULL) {
                        printf("Blad realokacji pamieci dla wierszy!\n");
                        return NULL;
                    }

                    // Alokacja pamięci dla nowych kolumn
                    for (int j = rows; j < rows_mem; j++) {
                        board[j] = (char *)malloc(cols_mem * sizeof(char));
                        if (board[j] == NULL) {
                            printf("Blad alokacji dla wiersza %d!\n", j);
                            return NULL;
                        }
                    }
                }
            }

            if (start == 1 && buff[i] != ' ' && buff[i] != '|') {
                cols++;

                if (cols >= cols_mem) {
                    // Realokowanie pamięci dla kolumn w bieżącym wierszu
                    cols_mem *= 2;
                    for (int j = 0; j <= rows; j++) {
                        board[j] = (char *)realloc(board[j], cols_mem * sizeof(char));
                        if (board[j] == NULL) {
                            printf("Blad realokacji pamieci dla kolumny!\n");
                            return NULL;
                        }
                    }
                }

                board[rows][cols] = buff[i];
             printf("Wiersz: %d\t Kolumna: %d\t Char: %c\n", rows, cols, buff[i]);

            }
        }
    }

    showCurrentBoard(board, rows, cols);

    // Zamykanie pliku po zakończeniu
    fclose(file);

    return board;
}
