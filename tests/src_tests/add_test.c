#include <assert.h>
#include <stdio.h>
#include "vector.h"
#include "add_test.h"  


void test_add_real_vectors() { // ВСЕ ТЕСТЫ В ОДИН ФАЙЛ
    Vector v1, v2, result;
    double data1[] = {1.0, 2.0, 3.0};
    double data2[] = {4.0, 5.0, 6.0};
    init_vector(&v1, 3, sizeof(double), REAL);
    init_vector(&v2, 3, sizeof(double), REAL);

    for (size_t i = 0; i < 3; i++) {
        push_data_in_vector(&v1, &data1[i]);
        push_data_in_vector(&v2, &data2[i]);
    }

    add_two_vectors(v1, v2, &result);
    assert(((double*)result.data)[0] == 5.0);
    assert(((double*)result.data)[1] == 7.0);
    assert(((double*)result.data)[2] == 9.0);

    free_vector(&v1);
    free_vector(&v2);
    free_vector(&result);
    printf("Test passed: test_add_real_vectors\n"); // все принты в отдлеьный интерфейс файл
}

void test_add_empty_vectors() {
    Vector v1, v2, result;
    init_vector(&v1, 0, sizeof(double), REAL);
    init_vector(&v2, 0, sizeof(double), REAL);

    add_two_vectors(v1, v2, &result);
    
    assert(result.size == 0);

    free_vector(&v1);
    free_vector(&v2);
    free_vector(&result);
    printf("Test passed: test_add_empty_vectors\n");
}


void test_add_incompatible_vectors() {
    Vector v1, v2, result;

    double data1[] = {1.0, 2.0, 3.0};
    Complex data2[] = {{4.0, 5.0}, {6.0, 7.0}, {8.0, 9.0}};
    init_vector(&v1, 3, sizeof(double), REAL);
    init_vector(&v2, 3, sizeof(Complex), COMPLEX);

    for (size_t i = 0; i < 3; i++) {
        push_data_in_vector(&v1, &data1[i]);
        push_data_in_vector(&v2, &data2[i]);
    }

    add_two_vectors(v1, v2, &result);

    free_vector(&v1);
    free_vector(&v2);
    free_vector(&result);
    printf("Test passed: test_add_incompatible_vectors\n");
}
