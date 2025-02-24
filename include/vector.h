#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// Перечисление для типов данных
typedef enum {
    REAL,
    COMPLEX
} DataType;

// Структура комплексного числа
typedef struct {
    double re;
    double im;
} Complex;

// Структура динамического вектора
typedef struct {
    void* data;
    DataType type_of_data;   // Используем DataType вместо строки
    size_t element_size;
    size_t size;
    size_t capacity;
} Vector;

// Функции для работы с векторами
void init_vector(Vector* v, size_t capacity, size_t element_size, DataType type_of_data);
void push_data_in_vector(Vector* v, void* element);
void free_vector(Vector* v);
void add_two_vectors(Vector v1, Vector v2, Vector* result);
void print_vector(Vector v);
void scalar_multiply(Vector v1, Vector v2, double* real_result, Complex* complex_result);

#endif
