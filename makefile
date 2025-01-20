# Kompilator
CC = cc

# Pliki
SRCS = board.c input.c playerInfo.c file.c fileEntry.c
EXEC = saper

all: $(EXEC)

# Kompilacja programu
$(EXEC): $(SRCS)
	$(CC) -o $@ main.c $^ -lm

# Kompilacja w trybie do debugowania
debug:
	$(CC) -g -o $(EXEC)_debug main.c $(SRCS) -lm
	gdb ./$(EXEC)_debug

# Kompilacja w trybie testowania
test:
	$(CC) -o test/test_bin test/test.c $(SRCS) -lm
	cd test && ./test_bin

# Czyszczenie
clean:
	rm -f $(EXEC) $(EXEC)_debug test/test_bin

.PHONY: all clean test

