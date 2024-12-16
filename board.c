#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"

// Funkcja do generowania losowej liczby miedzy min a max (wlacznie)
int getRandomNumber(int min, int max) {
  srand(time(NULL));  //Do main??
  return rand() % (max - min + 1) + min;
}

//Ustawienie ilosci kolumn i wierszy w zaleznosci od poziomu
//[!] Dodac wlasne parametry??-ISOD
void setBoardParams(int level, int *rows, int *cols, int *bombNumber) {
  if (level == 1) {
    *rows = 8;
    *cols = 8;
    *bombNumber = *rows * *cols * 0.15;
  } else if (level == 2) {
    *rows = 16;
    *cols = 16;
    *bombNumber = *rows * *cols * 0.2;
  } else if (level == 3) {
    *rows = 16;
    *cols = 32;
    *bombNumber = *rows * *cols * 0.2;
  } else {
    printf("Zly poziom\n");
  }
}

void placeBombs(char **board, int rows, int cols, int bombNumber) {
  int *bombs = (int*)malloc(bombNumber * sizeof(int));  // Przechowuje numery komórek na których będą bomby
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

void showBoard(char **board, int rows, int cols) {
  // Wyświetlenie planszy
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%c ", board[i][j]);
    }
    printf("\n");
 }
}



void initializeBoard(int level) {
  int rows = 0, cols = 0, bombNumber = 0;

  // Ustawienie parametrów planszy
  setBoardParams(level, &rows, &cols, &bombNumber);

  // Alokacja pamięci dla planszy
  char **board = (char **)malloc(rows * sizeof(char *));

  //Sprawdzenie poprawnosci przypisania pamieci
  if (board == NULL) {
    printf("Blad alokacji pamieci!\n");
    return;
  }
  for (int i = 0; i < rows; i++) {
    board[i] = (char *)malloc(cols * sizeof(char));
    if (board[i] == NULL) {
      printf("Blad alokacji dla rzedu %d!\n", i);
      return;
    }
  }

  // Inicjalizacja planszy, na razie tylko kropki
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      board[i][j] = '.';
    }
  }

  // Rozmieszczanie bomb
  placeBombs(board, rows, cols, bombNumber);

  //Wyswietlenie
  showBoard(board,rows,cols);

  // Zwolnienie pamięci
  for (int i = 0; i < rows; i++) {
    free(board[i]);
  }
  free(board);
}

