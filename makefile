CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
TEST_DIR = tests


SRC = $(SRC_DIR)/main.c $(SRC_DIR)/vector.c $(SRC_DIR)/handlers.c $(SRC_DIR)/interface.c
OBJ = $(BIN_DIR)/main.o $(BIN_DIR)/vector.o $(BIN_DIR)/handlers.o $(BIN_DIR)/interface.o
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


rebuild: clean all


run: $(TARGET)
	./$(TARGET)

# ==========================
#           ТЕСТЫ
# ==========================

TEST_SRC = $(TEST_DIR)/add_test.c $(TEST_DIR)/multiply_test.c $(TEST_DIR)/more_tests.c
TEST_OBJ = $(BIN_DIR)/add_test.o $(BIN_DIR)/multiply_test.o $(BIN_DIR)/more_tests.o
TEST_EXE = $(BIN_DIR)/tests

$(TEST_EXE): $(TEST_OBJ) $(BIN_DIR)/vector.o
	$(CC) $(CFLAGS) -o $(TEST_EXE) $(TEST_OBJ) $(BIN_DIR)/vector.o

$(BIN_DIR)/%.o: $(TEST_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


test: $(TEST_EXE)
	./$(TEST_EXE)
