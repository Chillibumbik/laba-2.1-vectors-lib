#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "vector.h"
#include "VectorErrors.h"
#include "double.h"
#include "Complex.h"
#include "integer.h"

#define EPS 1e-9

int perform_invalid_operation(Vector* v) {
    return OPERATION_NOT_DEFINED;
}

void test_double_operations() {
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6, 5.9, -6.1};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 4, &operation_result);
    Vector* v2 = createVector(GetDoubleTypeInfo(), a2, 4, &operation_result);
    Vector* v_res = createVector(GetDoubleTypeInfo(), malloc(4 * sizeof(double)), 4, &operation_result);
    
    if (errors_handler(operation_result)) return; 

    operation_result = add_vectors(v1, v2, v_res);
    if (errors_handler(operation_result)) return;
    
    double expected_sum[] = {9.7, 1.6, 9.4, -1.3};
    for (int i = 0; i < 4; i++) {
        if (fabs(((double*)v_res->data)[i] - expected_sum[i]) >= EPS) {
            printf("Error in addition at index %d\n", i);
        }
    }

    double scalar_result = 0.0;
    operation_result = multiply_vectors(v1, v2, &scalar_result);
    if (errors_handler(operation_result)) return;
    
    double expected_scalar = -4.91;
    if (fabs(scalar_result - expected_scalar) >= EPS) {
        printf("Error in scalar multiplication\n");
    }
    
    double module_result = 0.0;
    operation_result = find_module(v1, &module_result);
    if (errors_handler(operation_result)) return;
    
    if (fabs(sqrt(module_result) - sqrt(40.98)) >= EPS) {
        printf("Error in module calculation\n");
    }

    free_vector(v1);
    free_vector(v2);
    free_vector(v_res);
}

void test_memory_allocation_failure() {
    VectorErrors operation_result;
    Vector* v1 = createVector(GetDoubleTypeInfo(), NULL, 0, &operation_result);
    if (errors_handler(operation_result)) return;
}

void test_vector_not_defined() {
    VectorErrors operation_result;
    Vector* v1 = NULL;
    double scalar_result = 0.0;
    operation_result = multiply_vectors(v1, v1, &scalar_result);
    if (errors_handler(operation_result)) return;
}

void test_operation_not_defined() {
    VectorErrors operation_result;
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 4, &operation_result);
    if (errors_handler(operation_result)) return;
    
    free_vector(v1);
}

void test_incompatible_vectors() {
    double a1[] = {1.3, -2.0, 3.5};
    Complex a2[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 3, &operation_result);
    Vector* v2 = createVector(GetComplexTypeInfo(), a2, 3, &operation_result);
    Vector* v_res = createVector(GetComplexTypeInfo(), malloc(4 * sizeof(double)), 3, &operation_result);
    if (errors_handler(operation_result)) return;

    operation_result = add_vectors(v1, v2, v_res);
    if (errors_handler(operation_result)) return;
    
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res);
}

void test_different_length_vectors() {
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 4, &operation_result);
    Vector* v2 = createVector(GetDoubleTypeInfo(), a2, 2, &operation_result);
    Vector* v_res = createVector(GetDoubleTypeInfo(), malloc(4 * sizeof(double)), 4, &operation_result);
    if (errors_handler(operation_result)) return;

    operation_result = add_vectors(v1, v2, v_res);
    if (errors_handler(operation_result)) return;
    
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res);
}

void test_empty_vector() {
    VectorErrors operation_result;
    Vector* v = createVector(GetDoubleTypeInfo(), malloc(4 * sizeof(double)), 0, &operation_result);
    if (errors_handler(operation_result)) return;
    if (v == NULL || v->capacity != 0) {
        printf("Error in empty vector creation\n");
    }
    free_vector(v);
}

int main() {
    test_double_operations();
    test_memory_allocation_failure();
    test_vector_not_defined();
    test_operation_not_defined();
    test_incompatible_vectors();
    test_different_length_vectors();
    test_empty_vector();
    printf("All tests completed.\n");
    return 0;
}
