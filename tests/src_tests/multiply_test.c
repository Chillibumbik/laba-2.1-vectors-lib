#include <assert.h>
#include <stdio.h>
#include "vector.h"
#include "multiply_test.h"  


void test_scalar_multiply_real() {
    Vector v1, v2;
    init_vector(&v1, 3, sizeof(double), REAL);
    init_vector(&v2, 3, sizeof(double), REAL);

    double data1[] = {1.0, 2.0, 3.0};
    double data2[] = {4.0, 5.0, 6.0};

    for (size_t i = 0; i < 3; i++) {
        push_data_in_vector(&v1, &data1[i]);
        push_data_in_vector(&v2, &data2[i]);
    }

    double result = scalar_multiply_real(v1, v2);
    assert(result == 32.0);

    free_vector(&v1);
    free_vector(&v2);
    printf("Test passed: test_scalar_multiply_real\n");
}

void test_scalar_multiply_empty_vectors() {
    Vector v1, v2;
    init_vector(&v1, 0, sizeof(double), REAL);
    init_vector(&v2, 0, sizeof(double), REAL);

    double result = scalar_multiply_real(v1, v2);
    assert(result == 0.0);

    free_vector(&v1);
    free_vector(&v2);
    printf("Test passed: test_scalar_multiply_empty_vectors\n");
}

void test_scalar_multiply_incompatible_vectors() {
    Vector v1, v2;
    init_vector(&v1, 3, sizeof(double), REAL);
    init_vector(&v2, 3, sizeof(Complex), COMPLEX);

    double data1[] = {1.0, 2.0, 3.0};
    Complex data2[] = {{4.0, 5.0}, {6.0, 7.0}, {8.0, 9.0}};

    for (size_t i = 0; i < 3; i++) {
        push_data_in_vector(&v1, &data1[i]);
        push_data_in_vector(&v2, &data2[i]);
    }

    Complex result = scalar_multiply_complex(v1, v2);

    free_vector(&v1);
    free_vector(&v2);
    printf("Test passed: test_scalar_multiply_incompatible_vectors\n");
}
