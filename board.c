#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "board.h"

// Funkcja do generowania losowej liczby miedzy min a max (wlacznie)
int getRandomNumber(int min, int max) {
  return rand() % (max - min + 1) + min;
}

//Ustawienie ilosci kolumn i wierszy w zaleznosci od poziomu lub ustawienie wlasnych parametrow
void setBoardParams(int level, int *rows, int *cols, int *bombNumber) {
  if (level == 1) {
    *rows = 9;
    *cols = 9;
    *bombNumber = 10;
  } else if (level == 2) {
    *rows = 16;
    *cols = 16;
    *bombNumber = 40;
  } else if (level == 3) {
    *rows = 16;
    *cols = 30;
    *bombNumber = 99;
  } else if (level == 4) { 
    while (true) {
      printf("Podaj liczbe wierszy: ");
      scanf("%d", rows);
      if (*rows > 1) {
	      break;
      } else {
	printf("Nieprawidlowa wartosc.\n");
      }
    }
    while (true) {
      printf("Podaj liczbe kolumn: ");
      scanf("%d", cols);
      if (*cols > 1) {
	break;
      } else {
	printf("Nieprawidlowa wartosc.\n");
      }
    }
    while (true) {
      printf("Podaj liczbe bomb: ");
      scanf("%d", bombNumber);
      if (*bombNumber > 0 && *bombNumber < (*rows) * (*cols)) { /* Sprawdzenie czy ilosc bomb pozwala
								 * na wygenerowanie planszy (nie moze byc 
								 * wiecej bomb niz wszystkich pol na planszy)
								 */ 
	break;
      } else {
      	printf("Nieprawidlowa wartosc.\n");
      }
    }
  } else {
    printf("Zly poziom.\n");
  }
}

// Rozmieszczenie bomb na planszy zapewniajac, ze pierwsze odkryte pole ma byc puste
void placeBombs(char **board, int rows, int cols, int bombNumber, int startRow, int startCol) { 
  int bombsPlaced = 0;

  while (bombsPlaced < bombNumber) {
    int newBombRow = getRandomNumber(0, rows - 1); // Losowe wybranie komorki, w ktorej umieszczamy bombe
    int newBombCol = getRandomNumber(0, cols - 1);

    // Sprawdzenie, czy ta komorka jest juz bomba oraz czy nie graniczy z polem startowym
    if (board[newBombRow][newBombCol] != 'B' && (newBombRow < startRow - 1 || newBombRow > startRow + 1 || newBombCol < startCol - 1 || newBombCol > startCol + 1)) {
      board[newBombRow][newBombCol] = 'B';
      bombsPlaced++;
    }
  }
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
    int exp_row = (int)log10(rows) + 1;
    int exp_col = (int)log10(cols) + 1;
    for (int i = -1; i < rows; i++) {
        for (int j = -1; j < cols; j++) {
            if (i < 0) { // Nagłówki kolumn
                if (j < 0) {
		    for (int k = 0; k < exp_row + 3; k++)
                        printf(" ");
                } else {
                    printf("%d", j);
		    for (int k = 0; k < exp_col - (j > 0 ? (int)log10(j) : (int)log10(j+1)); k++)
			printf(" ");
                }
            } else { // Wiersze planszy
                if (j < 0) { // Nagłówki wierszy
                    printf("%d", i);
		    for (int k = 0; k < exp_row - (i > 0 ? (int)log10(i) : (int)log10(i+1)); k++)
			printf(" ");
                    printf("| ");
                } else { // Pola gry
                    if (board[i][j] == '*') { // Jeśli to mina, wyświetl normalnie
                        printf("%c", board[i][j]);
                    } else if (board[i][j] == '#') { // Nieodkryte pole, normalnie
                        printf("%c", board[i][j]);
                    } else { // Liczba
                        // Kolorowanie liczb od 1 do 8
                        if (board[i][j] == '1') {
                            printf("\033[38;2;1;0;255m%c\033[0m", board[i][j]); // Niebieski dla 1
                        } else if (board[i][j] == '2') {
                            printf("\033[38;2;1;127;1m%c\033[0m", board[i][j]); // Zielony dla 2
                        } else if (board[i][j] == '3') {
                            printf("\033[38;2;255;0;0m%c\033[0m", board[i][j]); // Czerwony dla 3
                        } else if (board[i][j] == '4') {
                            printf("\033[38;2;1;0;128m%c\033[0m", board[i][j]); // Granatowy dla 4
                        } else if (board[i][j] == '5') {
                            printf("\033[38;2;129;1;2m%c\033[0m", board[i][j]); // Ciemnoczerwony dla 5
                        } else if (board[i][j] == '6') {
                            printf("\033[38;2;0;128;129m%c\033[0m", board[i][j]); // Jasnoniebieski dla 6
                        } else if (board[i][j] == '7') {
                            printf("\033[38;2;0;0;0135m%c\033[0m", board[i][j]); // Czarny dla 7
                        } else if (board[i][j] == '8') {
                            printf("\033[38;2;128;128;128m%c\033[0m", board[i][j]); // Szary dla 8
                        } else {
                            printf("%c", board[i][j]); // Inne znaki wyświetl normalnie
                        }
                    }
		    for (int k = 0; k < exp_col; k++)
		        printf(" ");
                }
            }
	}
	if (i < 0) {
            printf("\n");
            for (int j = 0; j < exp_row + 2; j++)
                printf(" ");
            for (int j = 0; j < cols * (exp_col + 1); j++) {
                printf("-");
            }
        }
        printf("\n");
    }
}

// Tablica widoczna dla gracza
char** initializePlayerBoard(int rows, int cols) {
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
char** initializeBoard(int rows, int cols, int bombNumber, int startRow, int startCol) {
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
  placeBombs(board, rows, cols, bombNumber, startRow, startCol);

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

