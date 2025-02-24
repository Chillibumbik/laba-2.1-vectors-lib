#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>


typedef enum {
    REAL,
    COMPLEX
} DataType;


typedef struct {
    double re;
    double im;
} Complex;

typedef struct {
    void* data;
    DataType type_of_data;   
    size_t element_size;
    size_t size;
    size_t capacity;
} Vector;


void init_vector(Vector* v, size_t capacity, size_t element_size, DataType type_of_data);
void push_data_in_vector(Vector* v, void* element);
void free_vector(Vector* v);

void add_two_vectors(Vector v1, Vector v2, Vector* result);

void print_vector(Vector v);

double scalar_multiply_real(Vector v1, Vector v2);
Complex scalar_multiply_complex(Vector v1, Vector v2);
#endif
