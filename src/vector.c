#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "VectorErrors.h"

Vector* createVector(TypeInfo* typeInfo, void *data, size_t capacity, VectorErrors* operationResult){
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    if (vector == NULL) {
        *operationResult = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    vector->typeInfo = typeInfo;
    vector->capacity = capacity;
    vector->data = malloc(typeInfo->size * vector->capacity);
    if (vector->data == NULL) {
        *operationResult = MEMORY_ALLOCATION_FAILED;
        free(vector);
        return NULL;
    }
    
    if (data != NULL) {
        memcpy(vector->data, data, typeInfo->size * vector->capacity);
    }

    *operationResult = VECTOR_OPERATION_OK;
    return vector;
}

void free_vector(Vector* v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

VectorErrors add_vectors(const Vector* v1, const Vector* v2, Vector* result) {
    if (v1 == NULL || v2 == NULL || result == NULL) return VECTOR_NOT_DEFINED;
    if (v1->typeInfo->add == NULL) return OPERATION_NOT_DEFINED;

    for (size_t i = 0; i < v1->capacity; i++) {
        v1->typeInfo->add(
            (char*)v1->data + i * v1->typeInfo->size,
            (char*)v2->data + i * v1->typeInfo->size,
            (char*)result->data + i * v1->typeInfo->size
        );
    }

    return VECTOR_OPERATION_OK;
}

VectorErrors multiply_vectors(const Vector* v1, const Vector* v2, void* result) {
    if (v1 == NULL || v2 == NULL || result == NULL) return VECTOR_NOT_DEFINED;
    if (v1->typeInfo->multiply == NULL) return OPERATION_NOT_DEFINED;

    // Для комплексных чисел результат скалярного произведения - комплексное число
    if (v1->typeInfo->size == sizeof(Complex)) {
        Complex* scalarResult = (Complex*)result;
        scalarResult->real = 0;  // Инициализируем как 0
        scalarResult->imag = 0;

        for (size_t i = 0; i < v1->capacity; i++) {
            Complex* c1 = (Complex*)((char*)v1->data + i * v1->typeInfo->size);
            Complex* c2 = (Complex*)((char*)v2->data + i * v2->typeInfo->size);
            v1->typeInfo->multiply(c1, c2, scalarResult);  // Используем multiply для комплексных чисел
        }
    }
    else {  // Для других типов (например, double, int)
        double* scalarResult = (double*)result;
        *scalarResult = 0;
        for (size_t i = 0; i < v1->capacity; i++) {
            if (v1->typeInfo->size == sizeof(double)) {
                double* val1 = (double*)((char*)v1->data + i * v1->typeInfo->size);
                double* val2 = (double*)((char*)v2->data + i * v2->typeInfo->size);
                *scalarResult += (*val1) * (*val2);
            }
            else if (v1->typeInfo->size == sizeof(int)) {
                int* val1 = (int*)((char*)v1->data + i * v1->typeInfo->size);
                int* val2 = (int*)((char*)v2->data + i * v2->typeInfo->size);
                *scalarResult += (*val1) * (*val2);
            }
        }
    }

    return VECTOR_OPERATION_OK;
}


VectorErrors print_vector(const Vector* vector) {
    if (vector == NULL) return VECTOR_NOT_DEFINED;
    if (vector->typeInfo->print == NULL) return OPERATION_NOT_DEFINED;

    printf("Vector: (");
    for (size_t i = 0; i < vector->capacity; i++) {
        vector->typeInfo->print((char*)vector->data + i * vector->typeInfo->size);
        if (i < vector->capacity - 1) {
            printf(", ");
        }
    }
    printf(")");

    return VECTOR_OPERATION_OK;
}
