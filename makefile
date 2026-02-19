# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
LIBS = -pthread

# Folders and files
SRC_DIR = src
INC_DIR = include
SRC = $(SRC_DIR)/logger.c $(SRC_DIR)/main.c
OBJ = $(SRC:.c=.o)
TARGET = logger_test

# Default rule
all: $(TARGET)

# Linking the final binary
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Compiling source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleanup rule
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET) *.txt
