# Compiler
CC = cc

# Files
SRCS = main.c board.c input.c
EXEC = a.out

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(SRCS)
	$(CC) -o $@ $^

# Clean build files
clean:
	rm -f $(EXEC)

# Phony targets
.PHONY: all clean

