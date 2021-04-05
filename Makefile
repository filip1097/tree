# Makefile

CC = gcc
RM = rm
CFLAGS = -g

SOURCE_DIR = body
OBJECT_DIR = build/obj
HEADERS_DIR = headers
BIN_DIR	= build/bin
BIN_NAME = tree

SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.c)
OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.c,$(OBJECT_DIR)/%.o,$(SOURCE_FILES))

default: $(BIN_DIR)/$(BIN_NAME)

$(BIN_DIR)/$(BIN_NAME): $(OBJECT_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$(BIN_NAME) $^

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(OBJECT_DIR)
	$(CC) -I $(HEADERS_DIR) -c $(CFLAGS) $< -o $@ 

test_tree: $(BIN_DIR)/$(BIN_NAME)
	$(BIN_DIR)/$(BIN_NAME) -d 2 ./

clean:
	$(RM) -rf build

