
CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c11


SRC = main.c vector.c

OBJ = $(SRC:.c=.o)

TARGET = program


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@if exist $(TARGET) del $(TARGET)
	@if exist main.o del main.o
	@if exist vector.o del vector.o


run: $(TARGET)
	./$(TARGET)


rebuild: clean all
