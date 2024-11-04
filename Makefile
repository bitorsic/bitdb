# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source file
SRC = main.c

# Executable name
TARGET = bitdb

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean target to remove the executable
clean:
	rm -f $(TARGET)

.PHONY: all clean
