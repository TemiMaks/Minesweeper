#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input.h"
#include "board.h"

// Funkcja pokazująca komórkę
//Oczywiscie z moimi umiejetnosciami r 1 1 pokazuje [2][2], bo jakzeby inaczej
void showCell(bool *playState, char **board, char **Player_board, int row, int col, int rows, int cols) {
    Player_board[row][col] = board[row][col];

    // Jeżeli trafiliśmy na bombę, kończymy grę
    if (Player_board[row][col] == 'B') {
        printf("Koniec gry! BumBum\n");
        showCurrentBoard(board, rows, cols); // Końcowa plansza
        *playState = false;
        return; // Koniec gry
    }
    //Jesli nie jest to bomba to liczymy ilosc bomb wokol komorki zeby ja wyswietlic
    else if (Player_board[row][col] == '-') {
        int bombCount = 0;

        // Ruch wokół
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                // W granicach planszy
                if (row + i >= 0 && row + i < rows && col + j >= 0 && col + j < cols) {
                    if (board[row + i][col + j] == 'B') {
                        bombCount++;
                    }
                }
            }
        }

        // Jeśli wokół komórki są jakieś bomby, wyświetlamy liczbę
        if (bombCount > 0) {
            Player_board[row][col] = '0' + bombCount;  // Zmieniamy pustą komórkę na liczbę bomb
        }
        else {
          //No i dorobic wyswietlanie pustych komorek wokol aktualnej
          //void showFreeCells(row, col);
        }
    }

    // Jeżeli komórka nie jest bombą ani pustą komórką, pokazujemy wynik
    showCurrentBoard(Player_board, rows, cols);
}

// Funkcja oznaczająca komórkę
void markCell(char **board, char **Player_board, int row, int col) {
        Player_board[row][col] = 'f';
        printf("Oznaczyłes komorke [%d][%d] jako flage.\n", row, col);
        showCurrentBoard(Player_board, row, col);
        //Tu mozna by bylo dodac cos na zasadzie, ze jak komorka jest juz odkryta to zabrac mozliwosc oznaczania flaga
}

// Funkcja do obsługi wejścia od użytkownika
void entry(bool *playState, char **board, char **Player_board, int rows, int cols) {
    char moveType = '\0';
    int row = 0;
    int col = 0;

    while (*playState) {  // Pętla działa, dopóki gra trwa
        printf("Twój ruch: ");

        // Wczytanie ruchu i współrzędnych
        int inputCount = scanf(" %c %d %d", &moveType, &row, &col); // Spacja przed %c pozwala na ignorowanie białych znaków

        // Sprawdzenie poprawności argumentów
        if (inputCount != 3 || row < 0 || col < 0 || row >= rows || col >= cols) {
            printf("Błąd danych! Wprowadź format: litera spacja liczba spacja liczba.\n");
            while (getchar() != '\n'); // Czyszczenie bufora wejściowego
            continue; // Powrót na początek pętli
        }

        // Ruchy
        if (moveType == 'r') {
            showCell(playState, board, Player_board, row, col, rows, cols);
        } else if (moveType == 'f') {
            markCell(board, Player_board, row, col);
        } else {
            printf("Nieznany ruch: '%c'.\n", moveType);
        }
    }

}
