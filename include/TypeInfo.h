#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef void (*BinaryOperator)(const void* arg1, const void* arg2, void* result);
typedef void (*NonBinaryOperator)(const void* arg1, void* result);

typedef struct {
    size_t size;
    BinaryOperator add;
    BinaryOperator multiply;
    NonBinaryOperator module;
    void (*print)(const void*);
} TypeInfo;

#endif 
