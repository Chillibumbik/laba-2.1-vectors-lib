#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "vector.h"
#include "VectorErrors.h"
#include "double.h"
#include "Complex.h"
#include "integer.h"

#define EPS 1e-9

void test_double_operations() {
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6, 5.9, -6.1};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 4, &operation_result);
    Vector* v2 = createVector(GetDoubleTypeInfo(), a2, 4, &operation_result);
    Vector* v_res = createVector(GetDoubleTypeInfo(), malloc(4 * sizeof(double)), 4, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res != NULL);
    
    // Проверка сложения
    printf("Testing double addition\n");
    assert(add_vectors(v1, v2, v_res) == VECTOR_OPERATION_OK);
    double expected_sum[] = {9.7, 1.6, 9.4, -1.3};
    for (int i = 0; i < 4; i++) {
        assert(fabs(((double*)v_res->data)[i] - expected_sum[i]) < EPS);
    }
    
    // Проверка скалярного произведения
    printf("Testing double scalar multiplication\n");
    double scalar_result = 0.0;
    assert(multiply_vectors(v1, v2, &scalar_result) == VECTOR_OPERATION_OK);
    double expected_scalar = -4.91;
    assert(fabs(scalar_result - expected_scalar) < EPS);
    
    // Проверка модуля
    printf("Testing double module\n");
    double module_result = 0.0;
    assert(find_module(v1, &module_result) == VECTOR_OPERATION_OK);
    assert(fabs(sqrt(module_result) - sqrt(40.98)) < EPS);
    
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res);
}

void test_complex_operations() {
    Complex a1[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    Complex a2[] = {{1.0, -9.6}, {4.7, 6.8}, {-6.8, 3.1}};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetComplexTypeInfo(), a1, 3, &operation_result);
    Vector* v2 = createVector(GetComplexTypeInfo(), a2, 3, &operation_result);
    Vector* v_res = createVector(GetComplexTypeInfo(), malloc(4 * sizeof(double)), 3, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    
    printf("Testing complex addition\n");
    assert(add_vectors(v1, v2, v_res) == VECTOR_OPERATION_OK);
    
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res);
}

void test_vector_rewrite() {
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double new_coords[] = {5.0, -1.0, 2.0, 0.0};
    VectorErrors operation_result;
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 4, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    
    printf("Testing vector rewrite\n");
    assert(rewrite_vector(GetDoubleTypeInfo(), v1, 4, new_coords) == VECTOR_OPERATION_OK);
    
    free_vector(v1);
}

void test_empty_vector() {
    VectorErrors operation_result;
    Vector* v = createVector(GetDoubleTypeInfo(), malloc(4 * sizeof(double)), 0, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v != NULL);
    assert(v->capacity == 0);
    free_vector(v);
}

void test_incompatible_vectors() {
    double a1[] = {1.3, -2.0, 3.5};
    Complex a2[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    VectorErrors operation_result;
    
    Vector* v1 = createVector(GetDoubleTypeInfo(), a1, 3, &operation_result);
    Vector* v2 = createVector(GetComplexTypeInfo(), a2, 3, &operation_result);
    Vector* v_res = createVector(GetComplexTypeInfo(), malloc(4 * sizeof(double)), 3, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    
    printf("Testing incompatible vector addition\n");
    assert(add_vectors(v1, v2, v_res) == INCOMPATIBLE_VECTOR_TYPES);
    
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
    assert(operation_result == VECTOR_OPERATION_OK);
    
    printf("Testing different length vector addition\n");
    assert(add_vectors(v1, v2, v_res) == DIFFERENT_LENGHT_VECTORS);
    
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res);
}

int main() {
    test_double_operations();
    test_complex_operations();
    test_vector_rewrite();
    test_empty_vector();
    test_incompatible_vectors();
    test_different_length_vectors();
    printf("All tests passed successfully!\n");
    return 0;
}
