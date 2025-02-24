#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void init_vector(Vector* v, size_t capacity, size_t element_size, DataType type_of_data) {
    v->data = malloc(capacity * element_size);
    v->capacity = capacity;
    v->element_size = element_size;
    v->type_of_data = type_of_data;
    v->size = 0;
}

void push_data_in_vector(Vector* v, void* element) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * v->element_size);
        if (v->data == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
    }
    memcpy((char*)v->data + v->size * v->element_size, element, v->element_size);
    v->size++;
}

void free_vector(Vector* v) {
    free(v->data);
}

void add_two_vectors(Vector v1, Vector v2, Vector* result) {
    if (v1.size == 0 || v2.size == 0) {
        printf("Error: cannot add empty vectors.\n");
        return;
    }

    init_vector(result, v1.size, v1.element_size, v1.type_of_data);

    if (v1.type_of_data == REAL && v2.type_of_data == REAL) {
        for (size_t i = 0; i < v1.size; i++) {
            double* res_elem = (double*)malloc(v1.element_size);
            if (res_elem == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }

            *res_elem = *(double*)((char*)v1.data + i * v1.element_size) + *(double*)((char*)v2.data + i * v2.element_size);
            push_data_in_vector(result, res_elem);
            free(res_elem);
        }
    } else if (v1.type_of_data == COMPLEX && v2.type_of_data == COMPLEX) {
        for (size_t i = 0; i < v1.size; i++) {
            Complex* res_elem = (Complex*)malloc(v1.element_size);
            if (res_elem == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }

            Complex* cv1 = (Complex*)((char*)v1.data + i * v1.element_size);
            Complex* cv2 = (Complex*)((char*)v2.data + i * v2.element_size);
            res_elem->im = cv1->im + cv2->im;
            res_elem->re = cv1->re + cv2->re;

            push_data_in_vector(result, res_elem);
            free(res_elem);
        }
    }
}

void scalar_multiply(Vector v1, Vector v2, double* real_result, Complex* complex_result) {
    if (v1.type_of_data == REAL && v2.type_of_data == REAL) {
        *real_result = 0.0;
        for (size_t i = 0; i < v1.size; i++) {
            *real_result += *(double*)((char*)v1.data + i * v1.element_size) * *(double*)((char*)v2.data + i * v2.element_size);
        }
    } else if (v1.type_of_data == COMPLEX && v2.type_of_data == COMPLEX) {
        double real_part = 0.0;
        double imag_part = 0.0;

        for (size_t i = 0; i < v1.size; i++) {
            Complex* cv1 = (Complex*)((char*)v1.data + i * v1.element_size);
            Complex* cv2 = (Complex*)((char*)v2.data + i * v2.element_size);

            real_part += cv1->re * cv2->re - cv1->im * cv2->im;
            imag_part += cv1->re * cv2->im + cv1->im * cv2->re;
        }

        complex_result->re = real_part;
        complex_result->im = imag_part;
    }
}

void print_vector(Vector v) {
    printf("( ");
    if (v.type_of_data == REAL) {
        for (size_t i = 0; i < v.size; i++) {
            printf("%.2lf ", ((double*)v.data)[i]);
        }
    } else if (v.type_of_data == COMPLEX) {
        for (size_t i = 0; i < v.size; i++) {
            Complex* c = &((Complex*)v.data)[i];
            printf("%.2lf + %.2lfi ", c->re, c->im);
        }
    }
    printf(")\n");
}
