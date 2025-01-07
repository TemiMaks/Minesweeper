#include "file.h"
#include "board.h"
#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

unsigned connectNumbers(int x, int y) {
    int pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}

int recursiveCase(char *buff, int j, int *entry) {
    if (j >= strlen(buff) - 1) {
        //Koniec rekursji
        return -1;
    }

    if (isdigit(buff[j]) && isdigit(buff[j+1])) {
        {//Oba sa liczbami, a więc łączymy je
            *entry = connectNumbers(j, j+1);
        }
        return j+1;
    }

    // Recursive call for the next character
   return recursiveCase(buff, j + 1, entry);
}

char **AllocateMemory(int rows_mem, int cols_mem){
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
    return board;
}

void reallocateRowsMemory(char ***board, int rows, int cols, int *rows_mem, int *cols_mem){
// Realokowanie pamięci dla wierszy
        *rows_mem *= 2;
        *board = (char **)realloc(*board, *rows_mem * sizeof(char *));
        if (*board == NULL) {
        	printf("Blad realokacji pamieci dla wierszy!\n");
            freeBoard(*board,*rows_mem);
            free(board);
            return;
        }
 // Alokacja pamięci dla nowych kolumn
    	for (int j = rows; j < *rows_mem; j++) {
        	(*board)[j] = (char *)malloc(*cols_mem * sizeof(char));
        	if ((*board)[j] == NULL) {
        		printf("Blad alokacji dla wiersza %d!\n", j);
                freeBoard(*board, *rows_mem);
                free(board);
            	return;
        	}
    	}
}

void reallocateColsMemory(char **board, int *rows_mem, int rows, int *cols_mem){
  // Realokowanie pamięci dla kolumn w bieżącym wierszu
	*cols_mem *= 2;
    for (int j = 0; j <= rows; j++) {
    	board[j] = (char *)realloc(board[j], *cols_mem * sizeof(char));
        if (board[j] == NULL) {
        	printf("Blad realokacji pamieci dla kolumny %d!\n", j);
            freeBoard(board, *rows_mem);
            free(board);
            return;
         }
    }
}

char** loadFromFile(const char *filename, int *bombNumber) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("[!] Blad otwarcia pliku.\n");
        exit(1);
    }
    int entryRow, entryCol;
    // Alokacja pamięci dla planszy
    char **board = AllocateMemory(10, 10);
    int rows_mem = 10, cols_mem = 10;
    int correctInputs;

    int max_cols = -1;
    int rows = -1, cols = -1;

    char **playerBoard = NULL; // Deklaracja playerBoard, inicjalizujemy później

    char buff[1024]; // Do zapisu każdej linii
    while (fgets(buff, sizeof(buff), file)) {
        printf("Wiersz %d: ", rows + 1);
        printf("%s\n", buff);
        int start = 0, entryStart = 0;
        char moveType = '\0';
        cols = -1; // Resetowanie kolumn dla nowego wiersza
        // Obliczanie liczby kolumn i wierszy, wpisywanie znakow w poprawne miejsca do tabeli gry
        for (int i = 0; buff[i] != '\0'; i++) {
            if (buff[i] == '|') {
                start = 1;
                rows++;
                if (rows >= rows_mem) {
                    reallocateRowsMemory(&board, rows, cols, &rows_mem, &cols_mem);
                }
            }
            if (start == 1 && buff[i] != ' ' && buff[i] != '|' && buff[i] != 'r' && buff[i] != 'f') {
                cols++;
                max_cols = cols;
                if (cols >= cols_mem) {
                    reallocateColsMemory(board, &rows_mem, rows, &cols_mem);
                }
                board[rows][cols] = buff[i];
                if (buff[i] == 'B') {
                    (*bombNumber)++;
                }
            }
            if (buff[i] == 'r' || buff[i] == 'f') {
                entryStart = 1;
            }
            if (entryStart == 1) {
                moveType = buff[i];
                // Zbierz ktore pole odkryc / oznaczyc
                int last = recursiveCase(buff, i, &entryRow);
                last = recursiveCase(buff, last + 1, &entryCol);
                entryStart = 0;
            }
        }

        // Inicjalizacja playerBoard po ustaleniu max_cols (tylko raz)
        if (playerBoard == NULL) {
            playerBoard = initializePlayerBoard(rows + 1, max_cols + 1);
        }

        // Po wszystkim analiza inputu, tu trzeba wywolac analize tych wejsc entryCol, entryRow, moveType
        if (moveType != '\0'){
            //Funkcja entryFromFile zle dziala, kazdy input przyjmuje jako zly
            correctInputs = entryFromFile(board, playerBoard, rows, max_cols, *bombNumber, moveType, entryRow, entryCol);
            moveType = '\0';
        }
    }

    printf("Liczba poprawnych inputow %d", correctInputs);
    // Zamykanie pliku po zakończeniu
    fclose(file);

    return board;
}


