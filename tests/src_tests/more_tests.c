#include <assert.h>
#include <stdio.h>
#include "vector.h"
#include "more_tests.h"  

void test_empty_vectors() {
    Vector v1, v2, result;
    init_vector(&v1, 0, sizeof(double), REAL);
    init_vector(&v2, 0, sizeof(double), REAL);

    add_two_vectors(v1, v2, &result);
    assert(result.size == 0);

    free_vector(&v1);
    free_vector(&v2);
    free_vector(&result);
    printf("Test passed: test_empty_vectors\n");
}

void test_zero_elements_vector() {
    Vector v1, v2, result;
    init_vector(&v1, 3, sizeof(double), REAL);
    init_vector(&v2, 3, sizeof(double), REAL);

    double data[] = {0.0, 0.0, 0.0};
    for (size_t i = 0; i < 3; i++) {
        push_data_in_vector(&v1, &data[i]);
        push_data_in_vector(&v2, &data[i]);
    }

    add_two_vectors(v1, v2, &result);
    assert(((double*)result.data)[0] == 0.0);

    free_vector(&v1);
    free_vector(&v2);
    free_vector(&result);
    printf("Test passed: test_zero_elements_vector\n");
}
