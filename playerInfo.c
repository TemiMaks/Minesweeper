#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playerInfo.h"
#include "board.h"

int getScore(char **Player_board, int level, int rows, int cols){
  int cellNumber = 0;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if((Player_board[i][j] >= 48 && Player_board[i][j] <= 56) || Player_board[i][j] == 46){  // Bo to kod ASCII od 0-8 || .
       cellNumber++;
      }
    }
  }
int score = cellNumber * level;
printf("Zdobyles %d punktow na %d poziomie\n", score, level);
return score;
}

int didWin(char **Player_board,int level, int bombNumber, int rows, int cols){
  //Warunki wygranej
    int knownCells = 0;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if((Player_board[i][j] >= 48 && Player_board[i][j] <= 56) || Player_board[i][j] == 46){  // Bo to kod ASCII od 0-8 || .
       knownCells++;
      }
    }
  }
 if(knownCells == rows * cols - bombNumber){
   printf("Wygrales!\n");
   return 1;
 } else {
   return 0;
 }

}

int isUIDUnique(int uid){
  FILE *file = fopen("playerInfo.txt", "r");
  if (file == NULL) {
    return 1;  // UID unikalne, bo plik nie istnieje
  }

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    int existingUID;
    if (sscanf(line, "UID gracza: %d", &existingUID) == 1) {  // Czyta z pliku linie
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
while (isUIDUnique(uid) == 0){ // Powtarzaj, aż UID będzie unikalne
  uid = getRandomNumber(1000000, 50000000);
}
  return uid;
}

int compareScores(const void *a, const void *b) {
  Info *playerA = (Info *)a;
  Info *playerB = (Info *)b;
  return playerB->score - playerA->score; // Sortowanie malejąco
}


void updateFile(Info *Player) {
    int max_players = 5;
    FILE *file = fopen("playerInfo.txt", "r+");

    if (file == NULL) {
        file = fopen("playerInfo.txt", "w");  // Tworzy plik, jeśli nie istnieje
        if (file == NULL) {
            printf("[!] Błąd otwarcia pliku!\n");
            return;
        }
    }

    Info players[max_players];
    int playerCount = 0;

    // Wczytanie danych z pliku
    while (fscanf(file, "Nazwa gracza: %s\nUID gracza: %d\nWynik gracza: %d\n----------------------------\n",
                  players[playerCount].name, &players[playerCount].UID, &players[playerCount].score) == 3) {
        playerCount++;
    }

    // Jeśli jest mniej niż 5 graczy, dodaj nowego gracza
    if (playerCount < max_players) {
        players[playerCount] = *Player;
        playerCount++;
        printf("Dane o graczach zaktualizowane.\n");
    } else {
        // Sprawdź, czy nowy gracz ma wystarczająco dobry wynik, by wejść do czołówki
        int minScoreIndex = 0;
        for (int i = 0; i < playerCount - 1; i++) {
            if (players[i].score < players[minScoreIndex].score) {
                minScoreIndex = i;
            }
        }

        if (Player->score > players[minScoreIndex].score) {
            // Zastępujemy najgorszego gracza
            players[minScoreIndex] = *Player;
            printf("Dane o graczach zaktualizowane.\n");
        } else {
          printf("Najniższy wynik %d przewyzsza twoj wynik %d.\n", players[minScoreIndex].score, Player->score);
        }
    }

    // Sortowanie graczy według wyników (malejąco)
    qsort(players, playerCount, sizeof(Info), compareScores);

    // Zapisanie danych do pliku
    freopen("playerInfo.txt", "w", file);  // Nadpisanie pliku

    // Zapisanie najlepszych graczy
    for (int i = 0; i < playerCount; i++) {
        fprintf(file, "Nazwa gracza: %s\n", players[i].name);
        fprintf(file, "UID gracza: %d\n", players[i].UID);
        fprintf(file, "Wynik gracza: %d\n", players[i].score);
        fprintf(file, "----------------------------\n");
    }

    fclose(file);
}

Info* getPlayerInfo(int score) {
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
    printf("\n[!] Błąd wczytywania nazwy!\n");
    free(Player);
    return NULL;
  }

  Player->UID = generateUniqueUID();
  Player->score = score;

  updateFile(Player);

  return Player;
}


void printFile() {
      FILE *file = fopen("playerInfo.txt", "r+");
      if (file == NULL) {
        printf("Dane o graczach nie zostana wyswietlone- plik nie istnieje!\n");
        return;
      }
 printf("\n");
 printf("Oto lista najlepszych 5 graczy");
 printf("\n");

 char buffer[1024]; // Do zapisu kazdej linii
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
  }