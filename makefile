CC = gcc  #-Wall      
CFLAGS =  -Wextra -Wpedantic -std=c11 -Iinclude -Itests/include_tests

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

OBJ_DIR = bin
INCLUDE_DIR = include

SRC_FILES = $(SRC_DIR)/Complex.c $(SRC_DIR)/Double.c $(SRC_DIR)/Integer.c $(SRC_DIR)/handler.c $(SRC_DIR)/VectorErrors.c $(SRC_DIR)/main.c $(SRC_DIR)/vector.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


TEST_SRC_DIR = test
TEST_SRC_FILES = $(TEST_SRC_DIR)/test.c $(SRC_DIR)/vector.c $(SRC_DIR)/Complex.c $(SRC_DIR)/Double.c $(SRC_DIR)/Integer.c
TEST_OBJ_FILES = $(TEST_SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_TARGET = $(BIN_DIR)/test_program

TARGET = $(BIN_DIR)/program


all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR) 2>nul || true


test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJ_FILES)


clean:
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)


rebuild: clean all


run: $(TARGET)
	./$(TARGET)
