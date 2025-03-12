#include "VectorErrors.h"

int errors_handler(VectorErrors operation_result) {
    if (operation_result != VECTOR_OPERATION_OK) {
        switch (operation_result) {
            case MEMORY_ALLOCATION_FAILED:
                fprintf(stderr, "ERROR: memory allocation failed.\n");
                return 1;
            case VECTOR_NOT_DEFINED:
                fprintf(stderr, "ERROR: vector is not defined.\n");
                return 1;
            case OPERATION_NOT_DEFINED:
                fprintf(stderr, "ERROR: operation is not defined.\n");
                return 1;
            case INCOMPATIBLE_VECTOR_TYPES:
                fprintf(stderr, "ERROR: incompatible vector types.\n");
                return 1; 
            case DIFFERENT_LENGHT_VECTORS:
                fprintf(stderr, "ERROR: different lenght of vectors.\n");
                return 1;
            default:
                fprintf(stderr, "ERROR: unknown error.\n");
                return 1;
        }
    }
    return 0;
}