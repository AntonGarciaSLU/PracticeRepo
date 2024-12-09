# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

# Binaries
MAIN_BINARY = $(BIN_DIR)/main
TEST_BINARY = $(BIN_DIR)/test_main

# Targets
all: $(MAIN_BINARY) $(TEST_BINARY)

# Build main binary
$(MAIN_BINARY): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Build test binary with -lcunit
$(TEST_BINARY): $(OBJ_FILES) $(TEST_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lcunit

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build directories
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
