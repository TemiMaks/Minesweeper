#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

// Funkcja do generowania losowej liczby miedzy min a max (wlacznie)
int getRandomNumber(int min, int max) {
  return rand() % (max - min + 1) + min;
}

//Ustawienie ilosci kolumn i wierszy w zaleznosci od poziomu
//[!] Dodac wlasne parametry??-ISOD
void setBoardParams(int level, int *rows, int *cols, int *bombNumber) {
  if (level == 1) {
    *rows = 8;
    *cols = 8;
    *bombNumber = 10;
  } else if (level == 2) {
    *rows = 16;
    *cols = 16;
    *bombNumber = 40;
  } else if (level == 3) {
    *rows = 16;
    *cols = 32;
    *bombNumber = 99;
  } else {
    printf("Zly poziom\n");
  }
}

void placeBombs(char **board, int rows, int cols, int bombNumber) {
  int *bombs = (int*)malloc(bombNumber * sizeof(int));  // Przechowuje numery komorek na których będą bomby
  int bombsPlaced = 0;

  while (bombsPlaced < bombNumber) {
    int newBomb = getRandomNumber(0, rows * cols - 1); // Spośród komórek planszy

    // Sprawdzenie, czy ta liczba już została wylosowana
    bool isDuplicate = false;
    for (int i = 0; i < bombsPlaced; i++) {
      if (bombs[i] == newBomb) {
        isDuplicate = true;
        i = bombsPlaced;  // Wyjście z pętli
      }
    }

    // Jeśli liczba nie została wylosowana, dodajemy ją
    if (isDuplicate == false) {
      bombs[bombsPlaced] = newBomb;
      bombsPlaced++;
    }
  }

  // Rozmieszczanie bomb na planszy
  for (int i = 0; i < bombsPlaced; i++) {
    int index = bombs[i];
    //Konwersja tablicy jednowymairowej na dwuwymiarowa
    int row = index / cols;  // Numer wiersza
    int col = index % cols;  // Numer kolumny
    board[row][col] = 'B';  // Oznaczenie bomby
  }

  // Zwolnienie pamięci
  free(bombs);
}

// Zapisywanie liczb w polach graniczacych z bombami
void solveBoard(char **board, int rows, int cols) {
	int i, j, k;
	int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}}; // Kierunki sprawdzanych pol
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (board[i][j] != 'B') {
				char nearBombs = '0';
				for (k = 0; k < 8; k++) { // Sprawdza pola graniczace w 8 kierunkach
					if (i + directions[k][0] >= 0 && j + directions[k][1] >= 0 && i + directions[k][0] < rows && j + directions[k][1] < cols && board[i + directions[k][0]][j + directions[k][1]] == 'B') { // Sprawdzenie czy graniczace pola zawieraja sie w tablicy oraz czy sa bombami
						nearBombs += 1;
					}
				}
				if (nearBombs != '0') {
					board[i][j] = nearBombs;
				}
			}
		}
	}
}

void showCurrentBoard(char **board, int rows, int cols) {
    // Wyświetlenie aktualnej planszy
    for (int i = -1; i < rows; i++) {
        for (int j = -1; j < cols; j++) {
            if (i < 0) { // Nagłówki kolumn
                if (j < 0) {
                    printf("    ");
                } else {
                    printf("%d ", j);
                }
                if (j <= 9 && cols > 9)
                    printf(" ");
            } else { // Wiersze planszy
                if (j < 0) { // Nagłówki wierszy
                    if (i <= 9 && rows > 9)
                        printf("%d  | ", i); // Białe dla nagłówków wierszy
                    else
                        printf("%d | ", i);
                } else { // Pola gry
                    if (board[i][j] == '*') { // Jeśli to mina, wyświetl normalnie
                        printf("%c ", board[i][j]);
                    } else if (board[i][j] == '#') { // Nieodkryte pole, normalnie
                        printf("%c ", board[i][j]);
                    } else { // Liczba
                        // Kolorowanie liczb od 1 do 8
                        if (board[i][j] == '1') {
                            printf("\033[38;5;32m%c \033[0m", board[i][j]); // Zielony dla 1
                        } else if (board[i][j] == '2') {
                            printf("\033[38;5;34m%c \033[0m", board[i][j]); // Niebieski dla 2
                        } else if (board[i][j] == '3') {
                            printf("\033[38;5;196m%c \033[0m", board[i][j]); // Czerwony dla 3
                        } else if (board[i][j] == '4') {
                            printf("\033[38;5;208m%c \033[0m", board[i][j]); // Pomarańczowy dla 4
                        } else if (board[i][j] == '5') {
                            printf("\033[38;5;226m%c \033[0m", board[i][j]); // Żółty dla 5
                        } else if (board[i][j] == '6') {
                            printf("\033[38;5;82m%c \033[0m", board[i][j]); // Zielony dla 6
                        } else if (board[i][j] == '7') {
                            printf("\033[38;5;135m%c \033[0m", board[i][j]); // Różowy dla 7
                        } else if (board[i][j] == '8') {
                            printf("\033[38;5;93m%c \033[0m", board[i][j]); // Fioletowy dla 8
                        } else {
                            printf("%c ", board[i][j]); // Inne (np. '0') wyświetl normalnie
                        }
                    }
                }
            }
        }
        if (i < 0) {
            printf("\n   ");
            if (rows > 9)
                printf(" ");
            for (int j = 0; j < cols; j++) {
                printf("--");
                if (cols > 9)
                    printf("-");
            }
        }
        printf("\n");
    }
}


// Tablica widoczna dla gracza
char** initializePlayerBoard(int level, int rows, int cols) {
  // Alokacja pamięci dla planszy
  char **board = (char **)malloc(rows * sizeof(char *));

  //Sprawdzenie poprawnosci przypisania pamieci
  if (board == NULL) {
    printf("Blad alokacji pamieci!\n");
    return NULL;
  }
  for (int i = 0; i < rows; i++) {
    board[i] = (char *)malloc(cols * sizeof(char));
    if (board[i] == NULL) {
      printf("Blad alokacji dla rzedu %d!\n", i);
      return NULL;
    }
  }

  // Inicjalizacja planszy, jako nieodkryte komorki
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      board[i][j] = '#';
    }
  }

  return board;
}

/// Tablica niewidoczna dla gracza, zawierajaca polozenia bomb i liczby bomb na sasiadujacych komorkach
char** initializeBoard(int level, int rows, int cols, int bombNumber) {
  // Alokacja pamięci dla planszy
  char **board = (char **)malloc(rows * sizeof(char *));

  //Sprawdzenie poprawnosci przypisania pamieci
  if (board == NULL) {
    printf("Blad alokacji pamieci!\n");
    return NULL;
  }
  for (int i = 0; i < rows; i++) {
    board[i] = (char *)malloc(cols * sizeof(char));
    if (board[i] == NULL) {
      printf("Blad alokacji dla rzedu %d!\n", i);
      return NULL;
    }
  }

  // Inicjalizacja planszy, jako nieodkryte komorki
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      board[i][j] = '.';
    }
  }
  
  // Rozmieszczanie bomb
  placeBombs(board, rows, cols, bombNumber);

  // Zapisanie komorek z 'liczbami' bomb
  solveBoard(board, rows, cols);

  return board;
}

void freeBoard(char **board, int rows) {
  // Zwolnienie pamięci
  for (int i = 0; i < rows; i++) {
    free(board[i]);
  }
  free(board);
}

