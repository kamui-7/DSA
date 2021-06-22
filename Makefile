CC = gcc 
CFLAGS = -pedantic -Wall -Wextra -march=native
DEBUG = -DDEBUG -ggdb3
RM = rm -f

BIN_PATH = build
SRC_PATH = src

CC_FLAGS = $(CFLAGS) $(DEBUG)

SRC = $(shell find src -name *.c -type f)
BIN = $(basename $(patsubst src%,build%,$(SRC)))

all: $(BIN)

$(BIN): %: $(SRC)
	$(CC) $(CC_FLAGS) -o $@ $<
