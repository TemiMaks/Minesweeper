# Podział na moduły
#### board.c - zarządza wszystkimi operacjami związanymi z planszą gry, zarówno tą widoczną dla gracza, jak i niewidoczną, zawierającą informacje o bombach i ich sąsiedztwie
###### Funkcje:
Tworzenie planszy (widocznej i niewidocznej dla gracza).
Rozmieszczanie bomb na planszy.
Zliczanie liczb wokół bomb i zapisywanie ich w odpowiednich polach.
Wyświetlanie aktualnego stanu planszy.
Zwolnienie pamięci po zakończeniu gry.

#### file.c - obsługuje operacje związane z ładowaniem gry z pliku, przetwarzaniem ruchów gracza oraz zarządzaniem pamięcią związaną z planszą gry
###### Funkcje:
Alokowanie i realokowanie pamięci dla planszy.
Odczytywanie danych z pliku i interpretowanie ruchów gracza.
Przetwarzanie ruchów gracza i aktualizacja planszy na podstawie danych z pliku.
Zwolnienie zasobów po zakończeniu gry (pamięć i plik).
Obsługuje błędy, takie jak niepoprawne ruchy gracza czy problemy z alokacją pamięci.

#### fileEntry.c - zarządza obsługą wejść związanych z oznaczaniem i odkrywaniem komórek na planszy gry na podstawie danych z pliku
###### Funkcje:
Obsługuje ruchy odkrywania komórek. Jeśli gracz odkryje bombę, gra kończy się przegraną. Jeśli odkryje pustą komórkę, odkrywa sąsiednie komórki. Sprawdza też, czy gracz wygrał.
Oznacza komórkę flagą, zmieniając jej status w grze. Jeśli komórka jest już odkryta, ruch jest ignorowany.
Obsługuje różne typy ruchów (odkrycie komórki 'r', oznaczenie flagą 'f') i sprawdza poprawność wprowadzenia, zwracając odpowiedni stan gry (wygrana, przegrana, błędny ruch).
Liczy i wyświetla liczbę odkrytych komórek oraz poprawnych kroków wykonanych do tej pory

#### input.c - obsługuje interakcję z użytkownikiem w grze, umożliwiając wykonywanie ruchów polegających na odkrywaniu komórek lub oznaczaniu ich flagami
###### Funkcje:
Zapewnia interaktywność gry poprzez wczytywanie danych od użytkownika.
Umożliwia wykonywanie różnych akcji, takich jak odkrywanie komórek i oznaczanie ich flagami.
Zawiera logikę umożliwiającą zakończenie gry w przypadku trafienia na bombę lub wygranej.
Obsługuje sytuacje błędów (np. niepoprawne współrzędne czy nieznany ruch).
Po każdym ruchu wyświetla zaktualizowaną planszę.

#### playerInfo.c - zajmuje się zarządzaniem informacjami o graczu, jego wynikach oraz przechowywaniem danych w pliku
###### Funkcje:
Zarządza unikalnymi identyfikatorami graczy (UID).
Oblicza i wyświetla wynik gracza w zależności od liczby odkrytych komórek.
Przechowuje dane o najlepszych graczach (do 5 graczy), umożliwiając zapis, odczyt oraz aktualizację wyników.
Obsługuje zapis do pliku oraz wczytywanie danych o graczach z pliku.

#### main.c - stanowi główną część programu, w którym odbywa się całe zarządzanie grą, ustawienie poziomu trudności, inicjalizacja planszy oraz obsługa pliku (jeśli użytkownik podał plik)
###### Funkcje:
Parsowanie argumentów za pomocą getopt.
Wczytywanie danych z pliku (jeśli podano) za pomocą loadFromFile.
Ustawianie poziomu trudności oraz parametrów planszy.
Inicjalizowanie planszy gry i planszy gracza.
Uruchamianie gry poprzez funkcję entry.
Obliczanie wyniku gracza za pomocą getScore.
Pobieranie danych gracza i zapisywanie ich do pliku w updateFile.
Wyświetlanie najlepszych graczy za pomocą printFile.
Zwalnianie pamięci po zakończeniu gry.

# Opis implementacji
# board.c- Opis funkcji

Plik `board.c` zawiera implementację funkcji odpowiedzialnych za zarządzanie planszą w grze w Saper. Poniżej znajdują się opisy kluczowych funkcji.

## Funkcje

### **1. `setBoardParams(int level, int *rows, int *cols, int *bombNumber)`**
Funkcja ustawia parametry planszy na podstawie wybranego poziomu trudności. Określa liczbę wierszy, kolumn oraz liczbę bomb, które mają zostać rozmieszczone na planszy.

- **Poziom 1**: 9x9, 10 bomb
- **Poziom 2**: 16x16, 40 bomb
- **Poziom 3**: 16x30, 99 bomb

### **2. `solveBoard(char **board, int rows, int cols)`**
Funkcja przetwarza planszę, zapisując liczby bomb w sąsiednich komórkach dla każdej komórki, która nie zawiera bomby. Sprawdza 8 sąsiednich komórek i dla każdej z nich, która zawiera bombę, zwiększa liczbę w komórce.
### **3`initializeBoard(int rows, int cols, int bombNumber)`**
Funkcja inicjalizuje planszę gry, tworząc planszę niewidoczną dla gracza. Rozmieszcza bomby losowo na planszy i wypełnia pozostałe komórki liczbami wskazującymi liczbę bomb w sąsiednich komórkach.
### **4`initializePlayerBoard(int rows, int cols)`**
Funkcja inicjalizuje planszę widoczną dla gracza. Tworzy planszę o wymiarach rows na cols, wypełniając ją symbolem # (nieodkryte pola).
### **5`showCurrentBoard(char **board, int rows, int cols)`**
Funkcja wyświetla aktualny stan planszy. Pokazuje numery kolumn i wierszy, a także status każdej komórki (nieodkryte pola, bomby, liczby w sąsiedztwie). Liczby są wyświetlane w różnych kolorach w zależności od ich wartości (np. zielony dla 1, czerwony dla 3).


# file.c

Plik `file.c` zawiera funkcje odpowiedzialne za manipulację danymi, zarządzanie pamięcią i przetwarzanie danych związanych z grą w Saper. Poniżej znajdują się opisy kluczowych funkcji.

## Funkcje
### **1.`recursiveCase(char *buff, int j, int *entry)`**
Rekurencyjnie przetwarza ciąg znaków buff i łączy cyfry w jedną liczbę. Zwraca aktualny indeks w ciągu, aby móc rozpocząć wczytanie od kolejnej liczby.
### **2. `processMove(char* moveType, char** board, char** playerBoard, int rows, int max_cols, int *bombNumber, int *entryRow, int *entryCol, FILE* file, int buffLine, int rows_mem)`**
Przetwarza ruch gracza na planszy. Sprawdza, czy ruch jest prawidłowy, czy gracz trafił na bombę, czy wygrał grę.
### **3.`loadFromFile(const char *filename, int *bombNumber)`**
Ładuje dane z pliku filename, w tym planszę gry i ruchy gracza. Alokuje pamięć dla planszy i przetwarza dane z pliku.

# fileEntry.c - Opis funkcji

Plik `fileEntry.c` zawiera funkcje odpowiedzialne za obsługę działań związanych z odkrywaniem i oznaczaniem komórek na planszy w grze w Saper. Poniżej znajdują się opisy kluczowych funkcji.

## Funkcje
### **1.`showCellFromFile(int *playState, char **board, char **Player_board, int chosenRow, int chosenCol, int rows, int cols, int bombNumber, int buffLine)`**
Obsługuje ruch odkrywania komórki (`r`). Jeśli gracz trafił na bombę, kończy grę. Jeśli komórka jest pusta, odkrywa sąsiednie komórki. Jeśli gracz wygrał, kończy grę.
### **2`markCellFromFile(char **Player_board, int row, int col, int rows, int cols, int buffLine)`**
Oznacza komórkę flagą (f) lub zdejmuję flagę, jeśli komórka była już oznaczona.
### **3`entryFromFile(char **board, char **Player_board, int rows, int cols, int bombNumber, char moveType, int chosenRow, int chosenCol, int buffLine)`**
Obsługuje pojedynczy ruch na podstawie danych z pliku. Funkcja rozróżnia różne typy ruchów: odkrywanie komórki (r), oznaczanie komórki flagą (f), lub niepoprawne dane.
### **4`getShownCells(char **Player_board, int rows, int cols, int bombNumber, int buffLine)`**
Liczy i wyświetla liczbę odkrytych komórek oraz liczbę poprawnych kroków wykonanych przez gracza.

# input.c - Opis funkcji

Plik `input.c` zawiera funkcje związane z obsługą interakcji gracza z grą w Saper. Umożliwia odkrywanie komórek, oznaczanie ich flagą, a także kontroluje poprawność wprowadzonych danych.

## Funkcje
### **1.`void showFreeCells(char **board, char **Player_board, int row, int col, int rows, int cols)`**
Funkcja odkrywająca pobliskie puste komórki, rekurencyjnie odkrywając kolejne komórki w przypadku, gdy komórka jest pusta (`'.'`).
### **2`void showCell(bool *playState, char **board, char **Player_board, int row, int col, int rows, int cols, int bombNumber)`**
Funkcja odpowiedzialna za odkrycie komórki i sprawdzenie, czy nie trafiło się na bombę. W przypadku wygranej, gra kończy się.
### **3`void markCell(char **board, char **Player_board, int row, int col, int rows, int cols)`**
Funkcja umożliwiająca oznaczenie komórki flagą lub jej usunięcie. Jeśli komórka została już odkryta, oznaczenie nie jest możliwe.
### **4`void entry(char **board, char **Player_board, int rows, int cols, int bombNumber)`**
Funkcja obsługująca wejście od użytkownika. Pozwala na wykonywanie ruchów w grze: odkrywanie komórek (r) oraz oznaczanie ich flagą (f). Umożliwia również sprawdzenie poprawności wprowadzonych danych oraz wyświetlanie planszy po każdym ruchu.

# playerinfo.c - Opis funkcji

Plik `playerinfo.c` zarządza informacjami o graczach, w tym obliczaniem punktów, sprawdzaniem warunków wygranej, generowaniem unikalnych identyfikatorów UID i aktualizowaniem wyników w pliku.

## Funkcje
### **1`int getScore(char **Player_board, int level, int rows, int cols)`**
Oblicza wynik gracza na podstawie odkrytych komórek (komórki oznaczone od 0 do 8 lub puste). Wynik obliczany jest jako liczba odkrytych komórek pomnożona przez poziom trudności.
### **2`int didWin(char **Player_board, int bombNumber, int rows, int cols)`**
Sprawdza, czy gracz wygrał, czyli odkrył wszystkie komórki oprócz bomb. Jeśli tak, funkcja zwraca 1, w przeciwnym przypadku 0.
### **3.`void updateFile(Info *Player)`**
Aktualizuje plik playerInfo.txt, dodając nowego gracza lub zastępując najgorszego gracza, jeśli jego wynik jest mniejszy niż nowego. Po dodaniu lub aktualizacji danych, plik jest sortowany według wyników.
### **4`Info* getPlayerInfo(int score)`**
Funkcja do wczytania danych gracza, takich jak jego nazwa i wynik. Generuje unikalny UID dla gracza oraz zapisuje dane do pliku.
### Struktura Info
Struktura Info przechowuje dane o graczu: jego nazwę, unikalny identyfikator UID oraz wynik.

# Podział pracy w zespole
MM- 
JJ- 