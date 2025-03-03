#include <stdio.h>
#include <assert.h>
#include "vector.h"

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

void test_run(){
    test_add_real_vectors(); // все функции в отдлеьную
    test_add_empty_vectors();
    test_add_incompatible_vectors();

    test_scalar_multiply_real();
    test_scalar_multiply_empty_vectors();
    test_scalar_multiply_incompatible_vectors();

    test_empty_vectors();
    test_zero_elements_vector();

    printf("All tests passed.\n");

    return;
}

int main() {

    test_run();

    return 0;
}
