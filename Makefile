CC = gcc 
CC_FLAGS = -pedantic -Wall -Wextra -march=native
DEBUG = -DDEBUG -g
RM = rm -f

BIN_PATH = build
SRC_PATH = src

CFLAGS = $(CC_FLAGS) $(DEBUG)

SRC = $(shell find src -name *.c -type f)
BIN = $(basename $(patsubst $(SRC_PATH)%,$(BIN_PATH)%,$(SRC)))

all: $(BIN)

$(BIN): $(BIN_PATH)/%: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -o $@ $<
