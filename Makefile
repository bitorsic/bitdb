# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC = main.c

# Object files (replace .c with .o in SRC)
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = bitdb

# Default target
all: $(TARGET)

# Rule to build the executable from object files
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Rule to build each .o file from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove the executable and object files
clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean
