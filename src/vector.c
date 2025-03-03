#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "VectorErrors.h"

Vector* createVector(TypeInfo* typeInfo, void **data, size_t capacity, VectorErrors* operationResult){
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
    
    for(size_t i=0; i<vector->capacity; i++){
        memcpy(vector->data[i], data[i], typeInfo->size);
        }
    *operationResult = VECTOR_OPERATION_OK;
    return vector;
}


void free_vector(Vector* v) {
    free(v->data);

}

VectorErrors add_vectors(const Vector* v1, const Vector* v2, Vector* result) {
    if (v1 == NULL || v2 == NULL || result == NULL) return VECTOR_NOT_DEFINED;
    if (v1->typeInfo->add == NULL) return OPERATION_NOT_DEFINED;
    
    for(size_t i=0; i<v1->capacity; i++){
        v1->typeInfo->add(v1->data[i], v2->data[i], result->data[i]);
    }

    return VECTOR_OPERATION_OK;
}



VectorErrors multiply_vectors(const Vector* v1, const Vector* v2, void* result){
    if (v1 == NULL || v2 == NULL || result == NULL) return VECTOR_NOT_DEFINED;
    if (v1->typeInfo->multiply == NULL) return OPERATION_NOT_DEFINED;
    for(size_t i=0; i<v1->capacity; i++){
        v1->typeInfo->multiply(v1->data[i], v2->data[i], result);
    }   
    return VECTOR_OPERATION_OK;
}


VectorErrors print_vector(const Vector* vector) {
    if (vector == NULL) return VECTOR_NOT_DEFINED;
    if (vector->typeInfo->print == NULL) return OPERATION_NOT_DEFINED;
    printf("Vector: ("); 
    for(size_t i=0; i<vector->capacity; i++){
        if(i<(vector->capacity-1)){
            vector->typeInfo->print(vector->data[i]);
            printf(", "); 
        } else{
            vector->typeInfo->print(vector->data[i]);
            printf(")\n");
        }
    }
}