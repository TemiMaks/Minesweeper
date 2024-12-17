#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playerInfo.h"
#include "board.h"

int getScore(char **Player_board, int level, int rows, int cols){
  int cellNumber = 0;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(Player_board[i][j] >=48 && Player_board[i][j] <= 56 ){  // Bo to kod ASCII od 0-8
       cellNumber++;
      }
    }
  }
  int score = cellNumber * level;
  printf("Zdobyles %d punktow na poziomie %d\n", score, level);
  return score;
}

int isUIDUnique(int uid){
  FILE *file = fopen("playerInfo.txt", "r");
  if (file == NULL) {
    return 1;  // UID unikalne, bo plik nie istnieje
  }

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    int existingUID;
    if (sscanf(line, "UID gracza: %d", &existingUID) == 1) {
      if (existingUID == uid) {
        fclose(file);
        return 0;  // UID już istnieje
      }
    }
  }

  fclose(file);
  return 1;  // UID jest unikalne
}

int generateUniqueUID() {
  int uid = getRandomNumber(1000000, 50000000);;
while (!isUIDUnique(uid)){ // Powtarzaj, aż UID będzie unikalne
  uid = getRandomNumber(1000000, 50000000);
}
  return uid;
}

int compareScores(const void *a, const void *b) {
  Info *playerA = (Info *)a;
  Info *playerB = (Info *)b;
  return playerB->score - playerA->score; // Sortowanie malejąco
}

void updateFile(Info *Player){
  int max_players = 5;
  FILE *file = fopen("playerInfo.txt", "r+"); // Tryb odczyt i zapis, taki kompromis
  if (file == NULL) {
    printf("[!] Błąd otwarcia pliku!\n");
    return;
  }

  Info players[max_players];
  int playerCount = 0;

  // Wczytanie danych z pliku
  while (fscanf(file, "Nazwa gracza: %s\nUID gracza: %d\nWynik gracza: %d\n----------------------------\n",
          players[playerCount].name, &players[playerCount].UID, &players[playerCount].score) == 3) {
    playerCount++;
  }

  fclose(file);

  // Dodanie nowego gracza do tablicy
  if (playerCount < max_players) {
    players[playerCount] = *Player;
    playerCount++;
  } else {
    // Jeśli mamy już 5 graczy, zastępujemy najgorszego
    players[max_players - 1] = *Player;
  }

  // Sortowanie graczy według wyników (malejąco)
  qsort(players, playerCount, sizeof(Info), compareScores);

  // Zapisanie danych do pliku
  FILE *fileW = fopen("playerInfo.txt", "w"); // Nadpisanie pliku

  // Zapisanie najlepszych 5 graczy
  for (int i = 0; i < max_players; i++) {
    fprintf(fileW, "Nazwa gracza: %s\n", players[i].name);
    fprintf(fileW, "UID gracza: %d\n", players[i].UID);
    fprintf(fileW, "Wynik gracza: %d\n", players[i].score);
    fprintf(fileW, "----------------------------\n");
  }

  fclose(fileW);
  printf("Dane o graczach zaktualizowane.\n");
}

Info* getPlayerInfo() {
  Info *Player = (Info *)malloc(sizeof(Info));
  if (Player == NULL) {
    printf("[!] Error alokacji pamieci dla Info\n");
    return NULL;
  }

  // Czyszczenie bufora przed wczytaniem nazwy
  while (getchar() != '\n' && getchar() != EOF);

  // Wczytanie nazwy gracza
  printf("Podaj swoja nazwe: ");
  if (fgets(Player->name, sizeof(Player->name), stdin) == NULL) {
    printf("[!] Błąd wczytywania nazwy!\n");
    free(Player);
    return NULL;
  }

  Player->name[strcspn(Player->name, "\n")] = '\0';  // Usuwanie znaku nowej linii

  Player->UID = generateUniqueUID();

  updateFile(Player);

  return Player;
}
