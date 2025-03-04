#include "double.h"

void doubleAdd(const void* arg1, const void* arg2, void* result) {
    *(double*)result = *(double*)arg1 + *(double*)arg2;
}

void doubleMultiply(const void* arg1, const void* arg2, void* result) {
    double* d1 = (double*)arg1;
    double* d2 = (double*)arg2;
    double* scalarResult = (double*)result;

    *scalarResult += (*d1) * (*d2);
}


void doublePrint(const void* data) {
    printf("%lf", *(const double*)data);
}

TypeInfo* GetDoubleTypeInfo() {
    if (DOUBLE_TYPE_INFO == NULL) {
        DOUBLE_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (!DOUBLE_TYPE_INFO) return NULL;
        DOUBLE_TYPE_INFO->size = sizeof(double);
        DOUBLE_TYPE_INFO->add = doubleAdd;
        DOUBLE_TYPE_INFO->multiply = doubleMultiply;
        DOUBLE_TYPE_INFO->print = doublePrint;
    }
    return DOUBLE_TYPE_INFO;
}
