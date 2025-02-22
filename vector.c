#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

static FieldInfo* DOUBLE_FIELD_INFO = NULL;
static FieldInfo* COMPLEX_FIELD_INFO = NULL;

// Функции для работы с double
void add_double(void* v1, void* v2, void* result) {
    *(double*)result = *(double*)v1 + *(double*)v2;
}

double scalar_multiply_double(void* v1, void* v2) {
    return *(double*)v1 * *(double*)v2;
}

// Функции для работы с Complex
void add_complex(void* v1, void* v2, void* result) {
    Complex* cv1 = (Complex*)v1;
    Complex* cv2 = (Complex*)v2;
    Complex* cr = (Complex*)result;
    cr->re = cv1->re + cv2->re;
    cr->im = cv1->im + cv2->im;
}

double scalar_multiply_complex(void* v1, void* v2) {
    Complex* cv1 = (Complex*)v1;
    Complex* cv2 = (Complex*)v2;
    return cv1->re * cv2->re + cv1->im * cv2->im;
}

// Ленивая инициализация FieldInfo
FieldInfo* GetDoubleFieldInfo() {
    if (DOUBLE_FIELD_INFO == NULL) {
        DOUBLE_FIELD_INFO = (FieldInfo*)malloc(sizeof(FieldInfo));
        DOUBLE_FIELD_INFO->element_size = sizeof(double);
        DOUBLE_FIELD_INFO->add_func = add_double;
        DOUBLE_FIELD_INFO->scalar_multiply_func = scalar_multiply_double;
    }
    return DOUBLE_FIELD_INFO;
}

FieldInfo* GetComplexFieldInfo() {
    if (COMPLEX_FIELD_INFO == NULL) {
        COMPLEX_FIELD_INFO = (FieldInfo*)malloc(sizeof(FieldInfo));
        COMPLEX_FIELD_INFO->element_size = sizeof(Complex);
        COMPLEX_FIELD_INFO->add_func = add_complex;
        COMPLEX_FIELD_INFO->scalar_multiply_func = scalar_multiply_complex;
    }
    return COMPLEX_FIELD_INFO;
}

// Функции для работы с векторами
void init_vector(Vector* v, size_t capacity, size_t element_size) {
    v->data = malloc(capacity * element_size);
    v->size = 0;
    v->capacity = capacity;
    v->element_size = element_size;
}

void push_data_in_vector(Vector* v, void* element) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * v->element_size);
        if (v->data == NULL) {
            printf("Memory allocation error\n");
            return;
        }
    }
    memcpy((char*)v->data + v->size * v->element_size, element, v->element_size);
    v->size++;
}

void free_vector(Vector* v) {
    free(v->data);
}

void add__two_vectors(Vector v1, Vector v2, Vector* result, void (*addFunc)(void*, void*, void*)) {
    if (v1.size == 0 || v2.size == 0) {
        printf("Error: Cannot add empty vectors.\n");
        return;
    }
    if (v1.size != v2.size) {
        printf("Error: Vectors must have the same size for addition.\n");
        return;
    }

    init_vector(result, v1.size, v1.element_size);
    for (size_t i = 0; i < v1.size; i++) {
        void* res_element = malloc(v1.element_size);
        addFunc((char*)v1.data + i * v1.element_size,
                (char*)v2.data + i * v2.element_size,
                res_element);
        push_data_in_vector(result, res_element);
        free(res_element);
    }
}

void print_vector_real(Vector v) {
    printf("( ");
    for (size_t i = 0; i < v.size; i++) {
        printf("%.2lf ", ((double*)v.data)[i]);
    }
    printf(")\n");
}

void print_vector_complex(Vector v) {
    printf("( ");
    for (size_t i = 0; i < v.size; i++) {
        Complex* c = &((Complex*)v.data)[i];
        printf("%.2lf + %.2lfi ", c->re, c->im);
    }
    printf(")\n");
}
