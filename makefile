# Compiler
CC = cc

# Files
SRCS = main.c board.c input.c playerInfo.c
EXEC = a.out

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(SRCS)
	$(CC) -o $@ $^ -lm

# Clean build files
clean:
	rm -f $(EXEC)

# Phony targets
.PHONY: all clean

