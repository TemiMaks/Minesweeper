#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "playerInfo.h"
#include "input.h"
#include "board.h"

// Funkcja odkrywajaca pobliskie puste komorki
void showFreeCells(char **board, char **Player_board, int row, int col, int rows, int cols) {	//Zwraca liczbe odkrytych pol
	int i;
	int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}}; // Kierunki sprawdzanych komorek

	Player_board[row][col] = board[row][col];
	if (board[row][col] == '.') { // Jezeli komorka jest pusta to odkrywane sa kolejne
		for (i = 0; i < 8; i++) {
			int newRow = row + directions[i][0];
			int newCol = col + directions[i][1];
			if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && Player_board[newRow][newCol] == '#') {
				/* Sprawdzanie czy nastepna komorka jest w zakresie tablicy oraz czy jest nieodkryta 
				 * (zakladamy, ze nie moze byc to bomba poniewaz przed bomba zawsze znajdziemy komorke z 'numerem') */
				showFreeCells(board, Player_board, newRow, newCol, rows, cols);
			}
		}
	}
}

// Funkcja pokazująca komórkę
void showCell(bool *playState, char **board, char **Player_board, int row, int col, int rows, int cols, int bombNumber) {

    // Jeżeli trafiliśmy na bombę, kończymy grę
    if (board[row][col] == 'B') {
        printf("Koniec gry! BumBum\n");
        showCurrentBoard(board, rows, cols); // Końcowa plansza
        *playState = false;
        return; // Koniec gry
    }
    //Jesli nie jest to bomba to odkrywamy komorke
    else if (Player_board[row][col] == '#') {
	printf("Odkryto komorke [%d][%d].\n", row, col);
    showFreeCells(board, Player_board, row, col, rows, cols);
    if(didWin(Player_board, bombNumber,rows, cols) == 1){	//Skoro wygrana to koniec gry
      *playState = false;
    }
    }
    else if (Player_board[row][col] == 'f') {
	printf("Nie mozna odkryc komorki [%d][%d]; komorka jest oznaczona jako flaga.\n", row, col);
    }
    else {
	printf("Nie mozna odkryc komorki [%d][%d]; komorka juz odkryta.\n", row, col);
    }

    // Na koniec pokazujemy aktualna plansze
    showCurrentBoard(Player_board, rows, cols);
}
// Funkcja oblsugujaca 'r' z pliku
void showCellFromFile(bool *playState, char **board, char **Player_board, int row, int col, int rows, int cols, int bombNumber) {

    // Jeżeli trafiliśmy na bombę, kończymy grę
    if (board[row][col] == 'B') {
        printf("Koniec gry! BumBum\n");
        showCurrentBoard(board, rows, cols); // Końcowa plansza
        *playState = false;
        return; // Koniec gry
    }
    //Jesli nie jest to bomba to odkrywamy komorke
    else if (Player_board[row][col] == '#') {
	printf("Odkryto komorke [%d][%d].\n", row, col);
    showFreeCells(board, Player_board, row, col, rows, cols);
    if(didWin(Player_board, bombNumber,rows, cols) == 1){	//Skoro wygrana to koniec gry
      *playState = false;
    }
    }
    else if (Player_board[row][col] == 'f') {
	printf("Nie mozna odkryc komorki [%d][%d]; komorka jest oznaczona jako flaga.\n", row, col);
    }
    else {
	printf("Nie mozna odkryc komorki [%d][%d]; komorka juz odkryta.\n", row, col);
    }

    // Na koniec pokazujemy aktualna plansze
    showCurrentBoard(Player_board, rows, cols);
}

// Funkcja oznaczająca komórkę
void markCell(char **board, char **Player_board, int row, int col, int rows, int cols) {
	if (Player_board[row][col] == '#') {
        	printf("Oznaczyłes komorke [%d][%d] jako flage.\n", row, col);
		Player_board[row][col] = 'f';
	}
	else if (Player_board[row][col] == 'f') {
		printf("Usunales flage komorki [%d][%d].\n", row, col);
		Player_board[row][col] = '#';
	}
	else {
		printf("Nie mozna oznaczyc komorki [%d][%d] jako flagi; komorka juz odkryta.\n", row, col);
	}
        showCurrentBoard(Player_board, rows, cols);
}

// Funkcja oznaczająca komórkę z pliku
void markCellFromFile(char **board, char **Player_board, int row, int col, int rows, int cols) {
	if (Player_board[row][col] == '#') {
		Player_board[row][col] = 'f';
	}
	else if (Player_board[row][col] == 'f') {
		Player_board[row][col] = '#';
	}
	else {
	}
}

// Funkcja do obsługi wejścia od użytkownika
void entry(char **board, char **Player_board, int rows, int cols, int bombNumber) {
    char moveType = '\0';
    int row = 0;
    int col = 0;
    bool playState = true; 
    bool firstMove = true;   

    printf("Saper. Aby odkryc komorke: r [wiersz] [kolumna]; aby oznaczyc komorke jako flage: f [wiersz] [kolumna].\n");
    showCurrentBoard(Player_board, rows, cols);
    
    while (playState == true) {  // Pętla działa, dopóki gra trwa
        printf("Twój ruch: ");
	
        // Wczytanie ruchu i współrzędnych
        int inputCount = scanf(" %c %d %d", &moveType, &row, &col); // Spacja przed %c to ignorowanie bialych znakow

        // Sprawdzenie poprawności argumentów
        if (inputCount != 3 || row < 0 || col < 0 || row >= rows || col >= cols) {
            printf("Nieprawidlowy ruch. Aby odkryc komorke: r [wiersz] [kolumna]; aby oznaczyc komorke jako flage: f [wiersz] [kolumna].\n");
            while (getchar() != '\n'); // Czyszczenie bufora wejściowego
            continue; // Powrót na while
        }

	system("clear"); // Czysci ekran przed pokazaniem planszy po wykonanym ruchu
	
        // Ruchy
        if (moveType == 'r') {
	    if (firstMove) {
	    	while (board[row][col] != '.') {
            //Mysle ze tu dobrym pomyslem jest zwalnianie pamieci niepasujacej tablicy
            freeBoard(board, rows);
		    board = initializeBoard(rows, cols, bombNumber);
		}
	    	firstMove = false;
	    }
            showCell(&playState, board, Player_board, row, col, rows, cols, bombNumber);
        } else if (moveType == 'f') {
            markCell(board, Player_board, row, col, rows, cols);
        } else {
            printf("Nieznany ruch: '%c'. Aby odkryc komorke: r [wiersz] [kolumna]; aby oznaczyc komorke jako flage: f [wiersz] [kolumna].\n", moveType);
	    showCurrentBoard(Player_board, rows, cols);
        }
    }

}

//Nowe entry do oblsugi pliku
int entryFromFile(char **board, char **Player_board, int rows, int cols, int bombNumber, char moveType, int row, int col) {
    bool playState = true;

    while (playState == true) {  // Pętla działa, dopóki gra trwa
        // Sprawdzenie poprawności argumentów
        if (row < 0 || col < 0 || row >= rows || col >= cols) {
            printf("Nieprawidlowy ruch. Przerywam czytanie");
            return 1;
        }
        // Ruchy
        if (moveType == 'r') {
        	showCellFromFile(&playState, board, Player_board, row, col, rows, cols, bombNumber);
        } else if (moveType == 'f') {
            markCellFromFile(board, Player_board, row, col, rows, cols);
        } else {
            printf("Nieznany ruch: '%c'. Przerywam czytanie\n", moveType);
            playState = false;
	    	return 1;
        }
    }
	return 0;
}

int getCorrectInputs(char **Player_board, int rows, int cols, int bombNumber){
int correctInputs = 0;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if((Player_board[i][j] >= 48 && Player_board[i][j] <= 56) || Player_board[i][j] == 46){  // Bo to kod ASCII od 0-8 || .
       correctInputs++;
      }
    }
  }
return correctInputs;
}




