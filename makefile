CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
TEST_DIR = tests

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/vector.c
OBJ = $(BIN_DIR)/main.o $(BIN_DIR)/vector.o
TARGET = $(BIN_DIR)/program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir $(BIN_DIR) 2>nul || true

clean:
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

# ===========================
#           ТЕСТЫ
# ===========================

TEST_SRC = $(TEST_DIR)/tests.c
TEST_OBJ = $(BIN_DIR)/tests.o
TEST_EXE = $(BIN_DIR)/tests

$(TEST_EXE): $(TEST_OBJ) $(BIN_DIR)/vector.o
	$(CC) $(CFLAGS) -o $(TEST_EXE) $(TEST_OBJ) $(BIN_DIR)/vector.o

$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

test: $(TEST_EXE)
	./$(TEST_EXE)
