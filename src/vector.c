#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "VectorErrors.h"

Vector* createVector(TypeInfo* typeInfo, void *data, int capacity, VectorErrors* operationResult){
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
    if (v1->typeInfo != v2->typeInfo || v1->typeInfo != result->typeInfo) return INCOMPATIBLE_VECTOR_TYPES;
    if (v1->typeInfo->add == NULL) return OPERATION_NOT_DEFINED;

    for (int i = 0; i < v1->capacity; i++) {
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
    if (v1->typeInfo != v2->typeInfo) return INCOMPATIBLE_VECTOR_TYPES;
    if (v1->typeInfo->multiply == NULL) return OPERATION_NOT_DEFINED;


    for (int i = 0; i < v1->capacity; i++) {
        void* val1 = (char*)v1->data + i * v1->typeInfo->size;
        void* val2 = (char*)v2->data + i * v2->typeInfo->size;
        v1->typeInfo->multiply(val1, val2, result);  
    }

    return VECTOR_OPERATION_OK;
}



VectorErrors print_vector(const Vector* vector) {
    if (vector == NULL) return VECTOR_NOT_DEFINED;
    if (vector->typeInfo->print == NULL) return OPERATION_NOT_DEFINED;

    printf("Vector: (");
    for (int i = 0; i < vector->capacity; i++) {
        vector->typeInfo->print((char*)vector->data + i * vector->typeInfo->size);
        if (i < vector->capacity - 1) {
            printf(", ");
        }
    }
    printf(")");

    return VECTOR_OPERATION_OK;
}

VectorErrors find_module(const Vector* vector, void* result){
    if (vector == NULL || result == NULL) return VECTOR_NOT_DEFINED;
    if (vector->typeInfo->module == NULL) return OPERATION_NOT_DEFINED;
    
    for(int i=0; i < vector->capacity; i++){
        void* val = (char*)vector->data + i * vector->typeInfo->size;
        vector->typeInfo->module(val, result);
    }

    return VECTOR_OPERATION_OK;
}
