#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playerInfo.h"
#include "board.h"

int getScore(char **Player_board, int level, int rows, int cols){
  int cellNumber = 0;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(Player_board[i][j] >=48 && Player_board[i][j] <= 56 ){  //Bo to kod ASCII
       cellNumber++;
      }
    }
  }
int score = cellNumber * level;
printf("Zdobyles %d punktow na poziomie %d\n", score, level);
return score;
}


Info* getPlayerInfo() {
  // Alokacja pamięci dla struktury gracza
  Info *Player = (Info *)malloc(sizeof(Info));
  if (Player == NULL) {
    printf("[!] Error alokacji pamieci dla Info\n");
    return NULL;
  }

  // Wczytanie nazwy gracza
  printf("Podaj swoja nazwe: ");
  if (fgets(Player->name, sizeof(Player->name), stdin) == NULL) {
    printf("[!] Błąd wczytywania nazwy!\n");
    free(Player);
    return NULL;
  }

  // Usunięcie znaku nowej linii po fgets
  Player->name[strcspn(Player->name, "\n")] = '\0';

  // Losowanie UID
  Player->UID = getRandomNumber(1000000, 50000000);

  return Player; // Zeby zwolnic w main
}
