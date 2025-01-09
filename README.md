# SAPER

## OPIS
Gra saper polega na odkrywaniu pól na planszy w taki sposób, aby nie natrafić na minę. 
Na każdym odkrytym polu wyświetlana jest liczba wskazująca, 
ile min znajduje się w sąsiednich polach (od 0 do 8). 
Gra umożliwia również flagowanie pól, aby zabezpieczyć je 
przed przypadkowym odkryciem.

Gra posiada trzy poziomy trudności, możliwość wczytywania planszy z pliku 
oraz zapisywania wyników najlepszych graczy.

## FUNKCJE GRY
### Poziomy trudności:

Łatwy: plansza 9x9 i 10 min.  
Średni: plansza 16x16 i 40 min.  
Trudny: plansza 16x30 i 99 min.  
Własny poziom: możliwość definiowania rozmiaru planszy i liczby min. 

### Polecenia gracza:

f x y – Ustaw flagę na polu (x, y).  
Kolejne wywołanie z tymi samymi współrzędnymi usuwa flagę.  
r x y – Odsłoń pole (x, y).   
Pole może być odkryte lub oznaczone flagą.

### Wynik gracza:

Wynik jest obliczany jako liczba odsłoniętych pól pomnożona przez mnożnik trudności 
(1 - łatwy, 2 - średni, 3 - trudny).

### Zarządzanie wynikami:

Gra zapisuje wyniki wszystkich graczy w pliku tekstowym i 
wyświetla 5 najlepszych wyników.

### Generowanie planszy:

Gra generuje losowe rozmieszczenie min, zapewniając, że pierwszy wybór nie trafia na minę.  
Plansza generuje się ponownie, aż będzie ona spełniała ten warunek

### Tryb pracy z plikiem:

Gra może wczytywać planszę i ruchy z pliku, zwracając liczbę poprawnych kroków, 
liczbę punktów oraz status gry (0 - niepowodzenie, 1 - wygrana).
#### Przykładowy format pliku został przesłany na repozytorium- game.txt

## URUCHAMIANIE
### Instalacja poprzez repozytorium gitHub:
#### 1. Pobierz repozytorium:
###### git clone https://github.com/TemiMaks/Minesweeper
#### 2. Zbuduj aplikacje
###### make
#### 3. Uruchom program. Wpisz w terminalu:
###### ./saper -f file.txt
##### Program wczyta planszę i ruchy z pliku, a następnie wypisze podsumowanie
###### Lub też ./saper
#### A następnie będzie prosił o wpisywanie kolejnych ruchów zgodnie z wyświetlonym formatem
### Przykładowe komendy
#### f 5 6 - oflagowanie komórki na przecięciu 5 wiersza i 6 kolumny czy też odflagowanie jej
#### r 5 7 - odsłonięcie komórki na przecięciu 5 wiersza i 7 kolumny, niemożliwe dla już odsłoniętej czy też oflagowanej komórki 

## Wymagania i Zależności
#### Makefile do budowania aplikacji i uruchamiania testów
#### Kompilator C, np. gcc


## Testowanie
#### Aby uruchomić testy jednostkowe, użyj polecenia:
###### make test
#### Program wyświetla ilość testów, które przeszedł program, jak i ich listę
