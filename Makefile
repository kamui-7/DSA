CC = gcc 
CC_FLAGS = -pedantic -Wall -Wextra -march=native
DEBUG = -DDEBUG -g
RM = rm -f

OUT_DIR = build
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
TARGET_LIB = libdsa.a
TARGET_TEST = test

SRC = $(shell find $(SRC_DIR) -name *.c -type f)
OBJ = $(shell echo "$(SRC:.c=.o)" | sed -e "s/$(SRC_DIR)\//$(OUT_DIR)\//g")

TEST_SRC = $(shell find $(TEST_DIR) -name *.c -type f)
TEST_OBJ = $(shell echo "$(TEST_SRC:.c=.o)" | sed -e "s/$(TEST_DIR)\//$(OUT_DIR)\//g")

CFLAGS = $(CC_FLAGS) $(DEBUG) -I$(INC_DIR)
TEST_LDFLAGS = -L$(OUT_DIR) -l:$(TARGET_LIB) -lcmocka

all: check

$(OUT_DIR)/$(TARGET_LIB): $(OBJ)
	ar rcs $@ $(OBJ)

$(OBJ): $(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)/
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OUT_DIR)/:
	mkdir -p $@

.PHONY: check, clean
check: $(OUT_DIR)/$(TARGET_LIB) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_LDFLAGS) $(word 2,$^) -o $(OUT_DIR)/$(TARGET_TEST)

$(TEST_OBJ): $(OUT_DIR)/%.o: $(TEST_DIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OUT_DIR)
