#include <assert.h>
#include "test.h"
#include "../board.h"
#include "../file.h"
#include "../fileEntry.h"
#include "../input.h"
#include "../playerInfo.h"


void testSetBoardParams() {
  int rows, cols, bombNumber;

  // Test dla poziomu 1
  setBoardParams(1, &rows, &cols, &bombNumber);
  assert(rows == 9 && cols == 9 && bombNumber == 10);

  // Test dla poziomu 2
  setBoardParams(2, &rows, &cols, &bombNumber);
  assert(rows == 16 && cols == 16 && bombNumber == 40);

  // Test dla poziomu 3
  setBoardParams(3, &rows, &cols, &bombNumber);
  assert(rows == 16 && cols == 30 && bombNumber == 99);

  printf("Testy funkcji setBoardParams zakończone pomyślnie.\n");
}

void testInitializeBoard() {
  int rows = 9, cols = 9, bombNumber = 10, startRow = 4, startCol = 4;

  // Inicjalizacja planszy
  char **board = initializeBoard(rows, cols, bombNumber, startRow, startCol);
  assert(board != NULL);

  // Sprawdzenie, czy rozmiar planszy jest prawidłowy
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      assert(board[i][j] == '.' || board[i][j] == 'B' || (board[i][j] >= '1' && board[i][j] <= '8'));
    }
  }

  printf("Testy funkcji initializeBoard zakończone pomyślnie.\n");
  freeBoard(board, rows);
}

void testPlayerBoard() {
  int rows = 9, cols = 9;

  // Inicjalizacja planszy widocznej dla gracza
  char **playerBoard = initializePlayerBoard(rows, cols);
  assert(playerBoard != NULL);

  // Sprawdzenie, czy wszystkie pola są nieodkryte
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      assert(playerBoard[i][j] == '#');
    }
  }

  printf("Testy funkcji initializePlayerBoard zakończone pomyślnie.\n");
  freeBoard(playerBoard, rows);
}

void test_combineDigits() {
  int entry = -1;
  assert(combineDigits(&entry, 3) == 3);  // Pierwsza cyfra
  assert(combineDigits(&entry, 4) == 34); // Łączenie cyfr
  assert(combineDigits(&entry, 5) == 345);
  printf("Testy funkcji combineDigits zakonczone pomyslnie\n");
}


int main() {

  // Test funkcji setBoardParams
  testSetBoardParams();

  // Test funkcji initializeBoard
  testInitializeBoard();

  // Test funkcji initializePlayerBoard
  testPlayerBoard();

  //Test funkcji combineDigits
  test_combineDigits();

  printf("Wszystkie testy zakończone pomyślnie!\n");
  return 0;
}