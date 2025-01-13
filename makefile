# Compiler
CC = cc

# Files
SRCS = main.c board.c input.c playerInfo.c file.c fileEntry.c
EXEC = a.out

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(SRCS)
	$(CC) -o $@ $^ -lm

# Build and run tests
test:
	$(CC) -o test/test_bin test/test.c $(SRCS) -lm
	cd test && ./test_bin

# Clean build files
clean:
	rm -f $(EXEC) test/test_bin

# Phony targets
.PHONY: all clean test

