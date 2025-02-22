#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// Структура комплексного числа
typedef struct {
    double re;
    double im;
} Complex;

// Структура FieldInfo для работы с типами данных
typedef struct {
    size_t element_size;
    void (*add_func)(void*, void*, void*);
    double (*scalar_multiply_func)(void*, void*);
} FieldInfo;

// Структура динамического вектора
typedef struct {
    void* data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Vector;

// Функции для работы с векторами
void init_vector(Vector* v, size_t capacity, size_t element_size);
void push_data_in_vector(Vector* v, void* element);
void free_vector(Vector* v);
void add__two_vectors(Vector v1, Vector v2, Vector* result, void (*addFunc)(void*, void*, void*));

void print_vector_real(Vector v);
void print_vector_complex(Vector v);

// Функции для работы с FieldInfo
FieldInfo* GetDoubleFieldInfo();
FieldInfo* GetComplexFieldInfo();

// Функции для работы с вещественными
void add_double(void* v1, void* v2, void* result);
double scalar_multiply_double(void* v1, void* v2);

// Функции для работы с комплексными
void add_complex(void* v1, void* v2, void* result);
double scalar_multiply_complex(void* v1, void* v2);

#endif 
