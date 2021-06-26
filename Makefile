CC = gcc 
CC_FLAGS = -pedantic -Wall -Wextra -march=native
DEBUG = -DDEBUG -g
RM = rm -f

OUT_DIR = build
SRC_DIR = src
INC_DIR = include
TARGET_LIB = libdsa.a

SRC = $(shell find $(SRC_DIR) -name *.c -type f)
OBJ = $(subst $(SRC_DIR),$(OUT_DIR),$(SRC:.c=.o))

CFLAGS = $(CC_FLAGS) $(DEBUG)

$(OUT_DIR)/$(TARGET_LIB): $(OBJ)
	ar -rcs $@ $<

$(OBJ): $(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)/
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(OUT_DIR)/:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)
