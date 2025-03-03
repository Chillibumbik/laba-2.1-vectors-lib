CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude -Itests/include_tests

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Папки для исходных и объектных файлов
OBJ_DIR = bin
INCLUDE_DIR = include

# Исходные файлы
SRC_FILES = $(SRC_DIR)/Complex.c $(SRC_DIR)/Double.c $(SRC_DIR)/Integer.c $(SRC_DIR)/handler.c $(SRC_DIR)/interface.c $(SRC_DIR)/main.c $(SRC_DIR)/vector.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/program

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR) 2>nul || true

clean:
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)
