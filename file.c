#include "file.h"
#include "board.h"
#include "fileEntry.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int combineDigits(int *entry, int digit) {
    // Jeśli entry jest -1, to oznacza, że to pierwsza cyfra
    if (*entry == -1) {
        *entry = digit; // Zainicjujemy entry pierwszą cyfrą
    } else {
        // Łączenie cyfr, np. 13 i 3 -> 133
        *entry = (*entry) * 10 + digit;
    }
    return *entry;
}

int recursiveCase(char *buff, int j, int *entry) {
    // Jeśli osiągnięto koniec ciągu, zwróć aktualny indeks
    if (j >= strlen(buff)) {
        return j;
    }

    // Jeśli obecny znak jest cyfrą
    if (isdigit(buff[j])) {
        if (*entry == -1) {
            *entry = buff[j] - '0'; // Inicjalizuj wartość liczby
        } else {
            *entry = combineDigits(entry, buff[j] - '0'); // Łącz cyfry
        }

        // Jeśli następny znak jest cyfrą, kontynuuj
        if (j + 1 < strlen(buff) && isdigit(buff[j + 1])) {
            return recursiveCase(buff, j + 1, entry);
        } else {
            // Jeśli następny znak nie jest cyfrą, zakończ i zwróć indeks
            return j;
        }
    }

    // Rekursja dla następnego znaku, jeśli obecny znak nie jest cyfrą
    return recursiveCase(buff, j + 1, entry);
}

char **AllocateMemory(int rows_mem, int cols_mem) {
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

void reallocateRowsMemory(char ***board, int rows, int cols, int *rows_mem, int *cols_mem) {
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

void reallocateColsMemory(char **board, int *rows_mem, int rows, int *cols_mem) {
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

void processMove(char* moveType,char** board, char** playerBoard, int rows, int max_cols, int *bombNumber, int *entryRow, int *entryCol, FILE* file, int buffLine, int rows_mem) {
     if (*moveType != '\0'){
        int returnEntry = entryFromFile(board, playerBoard, rows + 1, max_cols, *bombNumber, *moveType, *entryRow, *entryCol, buffLine);
        if (returnEntry == 1) {
            printf("Nieprawidlowy ruch. Przerywam czytanie");
            getCorrectInputs(playerBoard, rows + 1, max_cols, *bombNumber);
            freeBoard(board, rows_mem);
            free(board);
            free(playerBoard);
            fclose(file);
        } else if (returnEntry == 2) {
            printf("Nieznany ruch: '%c'. Przerywam czytanie\n", *moveType);
            getCorrectInputs(playerBoard,rows + 1, max_cols, *bombNumber);
            freeBoard(board, rows_mem);
            free(board);
            free(playerBoard);
            fclose(file);
        } else if (returnEntry == 3) {
            getCorrectInputs(playerBoard, rows + 1, max_cols, *bombNumber);
            freeBoard(board, rows_mem);
            free(board);
            free(playerBoard);
            fclose(file);
        } else if (returnEntry == 4 ) {
            getCorrectInputs(playerBoard, rows + 1, max_cols, *bombNumber);
            freeBoard(board, rows_mem);
            free(board);
            free(playerBoard);
            fclose(file);
        }
        *moveType = '\0';
        *entryCol = -1, *entryRow = -1;
    }
}

void loadFromFile(const char *filename, int *bombNumber) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("[!] Blad otwarcia pliku.\n");
        exit(1);
    }
    int entryRow = -1, entryCol = -1;  // Inicjalizacja wartości
    // Alokacja pamięci dla planszy
    char **board = AllocateMemory(10, 10);
    int rows_mem = 10, cols_mem = 10;
    char **playerBoard = NULL;
    int max_cols = -1;
    int rows = -1, cols = -1;
    int buffLine = 0;

    char buff[1024]; // Do zapisu każdej linii
    while (fgets(buff, sizeof(buff), file)) {
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
                if (playerBoard == NULL) {
                    playerBoard = initializePlayerBoard(rows + 1, max_cols);
                }
            }
            if (entryStart == 1) {
                buffLine++;
                moveType = buff[i];
                // Zbierz ktore pole odkryc / oznaczyc
                int last = recursiveCase(buff, i, &entryRow);
                last = recursiveCase(buff, last + 1, &entryCol);
                // Po wszystkim analiza inputu, tu trzeba wywolac analize tych wejsc entryCol, entryRow, moveType
                processMove(&moveType, board, playerBoard, rows, max_cols, bombNumber, &entryRow, &entryCol, file, buffLine, rows_mem);
                entryStart = 0;
                }
            }
    }

    //Tu jesli nie przegra, nie wygra, po prostu za malo inputow do czegokolwiek
    getCorrectInputs(playerBoard, rows + 1, max_cols, *bombNumber);
    freeBoard(board, rows_mem);
    free(board);
    free(playerBoard);

    // Zamykanie pliku po zakończeniu
    fclose(file);
}
//Blednie liczona jest ilosc rzedow