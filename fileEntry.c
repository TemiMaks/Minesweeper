#include "fileEntry.h"
#include <stdio.h>
#include <stdbool.h>

// Funkcja oblsugujaca 'r' z pliku
void showCellFromFile(int *playState, char **board, char **Player_board, int chosenRow, int chosenCol, int rows, int cols, int bombNumber, int buffLine) {
    // Jeżeli trafiliśmy na bombę, kończymy grę
    if (board[chosenRow][chosenCol] == 'B') {
        printf("Koniec gry w ruchu %d! Tyle udalo sie odkryc!\n", buffLine);
        Player_board[chosenRow][chosenCol] = 'B';
        *playState = 3;    //Przegrana
        return; // Koniec gry
    } else if (Player_board[chosenRow][chosenCol] == '#') {	//Jesli nie jest to bomba to odkrywamy komorke
        showFreeCells(board, Player_board, chosenRow, chosenCol, rows, cols);
        if(didWin(Player_board, bombNumber,rows, cols) == 1) {
            *playState = 4;    //Skoro wygrana to koniec gry
        }
    } else if (Player_board[chosenRow][chosenCol] == 'f') {
        printf("Probujesz odkryc flage w ruchu %d, ignoruje.\n", buffLine);
        return;
    } else {
        printf("Probujesz odkryc znana komorke w ruchu %d, ignoruje.\n", buffLine);
        return;
    }
}

// Funkcja oznaczająca komórkę z pliku
void markCellFromFile(char **Player_board, int row, int col, int rows, int cols, int buffLine) {
    if (Player_board[row][col] == '#') {
        Player_board[row][col] = 'f';
    }
    else if (Player_board[row][col] == 'f') {
        Player_board[row][col] = '#';
    }
    else {
        printf("Probujesz oznaczyc odkryta komorke w ruchu %d, ignoruje\n", buffLine);
    }
}

//Jednorazowa (w odroznieniu od starego entry) obsluga wejscia- wielokrotnie wywolywania w file.c
int entryFromFile(char **board, char **Player_board, int rows, int cols, int bombNumber, char moveType, int chosenRow, int chosenCol, int buffLine) {
    int playState = 0;
    // Sprawdzenie poprawności argumentów
    if (chosenRow < 0 || chosenCol < 0 || chosenRow >= rows || chosenCol >= cols) {
        return 1;
    }
    // Ruchy
    if (moveType == 'r') {
        showCellFromFile(&playState, board, Player_board, chosenRow, chosenCol, rows, cols, bombNumber, buffLine);
        return playState;
    } else if (moveType == 'f') {
        markCellFromFile(Player_board, chosenRow, chosenCol, rows, cols, buffLine);
    } else {
        return 2;
        }
    return 0;
}


void getShownCells(char **Player_board, int rows, int cols, int bombNumber, int buffLine) {
    int correctInputs = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if((Player_board[i][j] >= '0' && Player_board[i][j] <= '8') || Player_board[i][j] == '.'){  // Bo to kod ASCII od 0-8 || .
                correctInputs++;
            }
        }
    }
    printf("Liczba odkrytych pol: %d\n", correctInputs);
    printf("Liczba poprawnych krokow: %d\n", buffLine);
}

