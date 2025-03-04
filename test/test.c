#include <stdio.h>
#include <assert.h>
#include "vector.h"
#include "Double.h"
#include "Integer.h"
#include "Complex.h"
#include <math.h>

// Значение epsilon для сравнения с погрешностью
#define EPSILON 1e-6

void testDoubleVector() {
    double data1[] = {1.1, 2.2, 3.3};
    double data2[] = {4.4, 5.5, 6.6};
    VectorErrors result;

    Vector* v1 = createVector(GetDoubleTypeInfo(), data1, 3, &result);
    Vector* v2 = createVector(GetDoubleTypeInfo(), data2, 3, &result);
    Vector* res = createVector(GetDoubleTypeInfo(), NULL, 3, &result);

    assert(result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && res != NULL);

    add_vectors(v1, v2, res);

    double expected[] = {5.5, 7.7, 9.9};
    for (int i = 0; i < 3; i++) {
        printf("Expected: %.2f, Got: %.2f\n", expected[i], ((double*)res->data)[i]);
        assert(fabs(((double*)res->data)[i] - expected[i]) < EPSILON);
    }

    free_vector(v1);
    free_vector(v2);
    free_vector(res);
}

void testIntegerVector() {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    VectorErrors result;

    Vector* v1 = createVector(GetIntTypeInfo(), data1, 3, &result);
    Vector* v2 = createVector(GetIntTypeInfo(), data2, 3, &result);
    Vector* res = createVector(GetIntTypeInfo(), NULL, 3, &result);

    assert(result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && res != NULL);

    add_vectors(v1, v2, res);
    int expected[] = {5, 7, 9};
    for (int i = 0; i < 3; i++) {
        assert(((int*)res->data)[i] == expected[i]);
    }

    free_vector(v1);
    free_vector(v2);
    free_vector(res);
}

void testComplexVector() {
    Complex data1[] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    Complex data2[] = {{6.0, 5.0}, {4.0, 3.0}, {2.0, 1.0}};
    VectorErrors result;

    Vector* v1 = createVector(GetComplexTypeInfo(), data1, 3, &result);
    Vector* v2 = createVector(GetComplexTypeInfo(), data2, 3, &result);
    Vector* res = createVector(GetComplexTypeInfo(), NULL, 3, &result);

    assert(result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && res != NULL);

    add_vectors(v1, v2, res);
    Complex expected[] = {{7.0, 7.0}, {7.0, 7.0}, {7.0, 7.0}};
    for (int i = 0; i < 3; i++) {
        assert(((Complex*)res->data)[i].real == expected[i].real);
        assert(((Complex*)res->data)[i].imag == expected[i].imag);
    }

    free_vector(v1);
    free_vector(v2);
    free_vector(res);
}

// Тест на создание пустого вектора
void testEmptyVector() {
    VectorErrors result;
    Vector* v = createVector(GetDoubleTypeInfo(), NULL, 0, &result);
    assert(result == VECTOR_OPERATION_OK);
    assert(v != NULL);
    assert(v->capacity == 0);
    free_vector(v);
}


// Тест на умножение векторов
void testMultiplyVectors() {
    double data1[] = {1.0, 2.0};
    double data2[] = {3.0, 4.0};
    double result = 0.0;

    VectorErrors resultCode;
    Vector* v1 = createVector(GetDoubleTypeInfo(), data1, 2, &resultCode);
    Vector* v2 = createVector(GetDoubleTypeInfo(), data2, 2, &resultCode);

    assert(v1 != NULL && v2 != NULL);

    multiply_vectors(v1, v2, &result);
    assert(fabs(result - 11.0) < EPSILON);  // Ожидаем результат 1.0*3.0 + 2.0*4.0 = 11.0

    free_vector(v1);
    free_vector(v2);
}

void testComplexMultiply() {
    Complex data1[] = {{1.0, 2.0}};
    Complex data2[] = {{3.0, 4.0}};
    double result = 0.0;

    VectorErrors resultCode;
    Vector* v1 = createVector(GetComplexTypeInfo(), data1, 1, &resultCode);
    Vector* v2 = createVector(GetComplexTypeInfo(), data2, 1, &resultCode);

    assert(v1 != NULL && v2 != NULL);

    multiply_vectors(v1, v2, &result);

    // Ожидаем результат: 1*3 + 2*4 = 11
    assert(fabs(result - 11.0) < EPSILON);

    free_vector(v1);
    free_vector(v2);
}

int main() {
    testDoubleVector();
    testIntegerVector();
    testComplexVector();
    testEmptyVector();
    testMultiplyVectors();
    testComplexMultiply();
    printf("All tests passed!\n");
    return 0;
}
