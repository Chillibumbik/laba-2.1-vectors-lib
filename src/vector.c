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
    if (v1->capacity != v2->capacity) return DIFFERENT_LENGHT_VECTORS;
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
    if (v1->capacity != v2->capacity) return DIFFERENT_LENGHT_VECTORS;
    if (v1->typeInfo->multiply == NULL) return OPERATION_NOT_DEFINED;
    
    memset(result, 0, v1->typeInfo->size);
    for(int i=0; i<v1->capacity; i++){
        void* arg1 = (char*)v1->data + i * v1->typeInfo->size;
        void* arg2 = (char*)v2->data + i * v2->typeInfo->size;
        void* temp_result = malloc(v1->typeInfo->size);
        if (temp_result == NULL) return MEMORY_ALLOCATION_FAILED; 
        v1->typeInfo->multiply(arg1, arg2, temp_result);  
        v1->typeInfo->add(result, temp_result, result);
        free(temp_result); 
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

VectorErrors rewrite_vector(TypeInfo* new_typeInfo, Vector *v, int new_capacity, void *new_data){
    if (v == NULL || new_data == NULL) return VECTOR_NOT_DEFINED;
    free(v->data);
    v->typeInfo = new_typeInfo;
    v->capacity = new_capacity;
    v->data =  malloc(new_typeInfo->size * v->capacity);
    if (v->data == NULL) return VECTOR_NOT_DEFINED;
    memcpy(v->data, new_data, new_capacity * new_typeInfo->size);
    return VECTOR_OPERATION_OK;
}