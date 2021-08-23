CC = gcc 
CC_FLAGS = -pedantic -Wall -Wextra -march=native
DEBUG = -DDEBUG -g
RM = rm -rf

OUT_DIR = build
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
TEST_OUT_DIR = build/bin
TARGET_LIB = libdsa.a

SRC = $(shell find $(SRC_DIR) -name *.c -type f)
OBJ = $(shell echo "$(SRC:.c=.o)" | sed -e "s/$(SRC_DIR)\//$(OUT_DIR)\//g")

TEST_SRC = $(shell find $(TEST_DIR) -name *.c -type f)
TEST_OBJ = $(shell echo "$(TEST_SRC:.c=)" | sed -e "s/$(TEST_DIR)\//$(subst /,\/,${TEST_OUT_DIR})\//g")

CFLAGS = $(CC_FLAGS) $(DEBUG) -I$(INC_DIR)
TEST_LDFLAGS = -lcmocka

.PHONY: clean, run, check

check: $(OUT_DIR)/$(TARGET_LIB) $(TEST_OBJ) 

$(OUT_DIR)/$(TARGET_LIB): $(OBJ)
	ar rcs $@ $(OBJ)

$(OBJ): $(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)/
	$(CC) $(CFLAGS) -c $< -o $@ 

$(TEST_OBJ): $(TEST_OUT_DIR)/%: $(TEST_DIR)/%.c  | $(TEST_OUT_DIR)/
	$(CC) $(CFLAGS) $(TEST_LDFLAGS) $< -o $@ $(OUT_DIR)/$(TARGET_LIB)

run: $(OUT_DIR)/$(TARGET_LIB) $(TEST_OBJ) 
	for tb in $^ ; do \
		eval $$tb; \
		echo; \
	done

clean:
	$(RM) $(OUT_DIR)

$(OUT_DIR)/:
	mkdir -p $@

$(TEST_OUT_DIR)/:
	mkdir -p $@

