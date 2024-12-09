# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDE = -Iinclude
SRC = src/library.c src/main.c
OBJ = $(SRC:.c=.o)
TEST_SRC = test/test_main.c
TEST_OBJ = $(TEST_SRC:.c=.o)

# Targets
all: library

library: $(OBJ)
	$(CC) $(CFLAGS) -o library $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

test: library $(TEST_OBJ)
	$(CC) $(CFLAGS) -o test_runner $(TEST_OBJ) $(OBJ)
	./test_runner

clean:
	rm -f $(OBJ) $(TEST_OBJ) library test_runner

.PHONY: all test clean
