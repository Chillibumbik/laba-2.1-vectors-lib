#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include "TypeInfo.h"
#include "Integer.h"
#include "Double.h"
#include "Complex.h"
#include "VectorErrors.h"

typedef struct {
    void **data;
    TypeInfo* typeInfo;   
    int capacity;
} Vector;


Vector* createVector(TypeInfo* typeInfo, void *data, int capacity, VectorErrors* operationResult);
void free_vector(Vector* v);
VectorErrors add_vectors(const Vector* v1, const Vector* v2, Vector* result);
VectorErrors multiply_vectors(const Vector* v1, const Vector* v2, void* result);
VectorErrors print_vector(const Vector* v);


#endif
