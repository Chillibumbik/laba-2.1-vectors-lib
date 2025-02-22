#include <stdio.h>
#include <assert.h>
#include "vector.h"

void test_push_data_in_vector() {
    Vector v;
    init_vector(&v, 2, sizeof(double));
    
    double a = 1.5, b = 2.5;
    push_data_in_vector(&v, &a);
    push_data_in_vector(&v, &b);

    assert(v.size == 2);
    assert(((double*)v.data)[0] == 1.5);
    assert(((double*)v.data)[1] == 2.5);
    
    printf("Test push_data_in_vector passed.\n");
    free_vector(&v);
}

void test_add_vectors() {
    Vector v1, v2, result;
    init_vector(&v1, 2, sizeof(double));
    init_vector(&v2, 2, sizeof(double));

    double a = 1.0, b = 2.0, c = 3.0, d = 4.0;
    push_data_in_vector(&v1, &a);
    push_data_in_vector(&v1, &b);
    push_data_in_vector(&v2, &c);
    push_data_in_vector(&v2, &d);

    add__two_vectors(v1, v2, &result, GetDoubleFieldInfo()->add_func);

    assert(((double*)result.data)[0] == 4.0);
    assert(((double*)result.data)[1] == 6.0);

    printf("Test add_vectors passed.\n");

    free_vector(&v1);
    free_vector(&v2);
    free_vector(&result);
}

void test_scalar_product() {
    Vector v1, v2;
    init_vector(&v1, 2, sizeof(double));
    init_vector(&v2, 2, sizeof(double));

    double a = 1.0, b = 2.0, c = 3.0, d = 4.0;
    push_data_in_vector(&v1, &a);
    push_data_in_vector(&v1, &b);
    push_data_in_vector(&v2, &c);
    push_data_in_vector(&v2, &d);

    double result = 0.0;
    for (size_t i = 0; i < v1.size; i++) {
        result += GetDoubleFieldInfo()->scalar_multiply_func(
            (char*)v1.data + i * v1.element_size,
            (char*)v2.data + i * v2.element_size
        );
    }

    assert(result == 11.0);

    printf("Test scalar_product passed.\n");

    free_vector(&v1);
    free_vector(&v2);
}

void test_complex_operations() {
    Vector v1, v2, result;
    init_vector(&v1, 2, sizeof(Complex));
    init_vector(&v2, 2, sizeof(Complex));

    Complex a = {1.0, 2.0}, b = {3.0, 4.0}, c = {5.0, 6.0}, d = {7.0, 8.0};
    push_data_in_vector(&v1, &a);
    push_data_in_vector(&v1, &b);
    push_data_in_vector(&v2, &c);
    push_data_in_vector(&v2, &d);

    add__two_vectors(v1, v2, &result, GetComplexFieldInfo()->add_func);

    Complex* res_data = (Complex*)result.data;
    assert(res_data[0].re == 6.0 && res_data[0].im == 8.0);
    assert(res_data[1].re == 10.0 && res_data[1].im == 12.0);

    printf("Test complex_addition passed.\n");

    double scalar_result = 0.0;
    for (size_t i = 0; i < v1.size; i++) {
        scalar_result += GetComplexFieldInfo()->scalar_multiply_func(
            (char*)v1.data + i * v1.element_size,
            (char*)v2.data + i * v2.element_size
        );
    }

    assert(scalar_result == 70.0);

    printf("Test complex_scalar_product passed.\n");

    free_vector(&v1);
    free_vector(&v2);
    free_vector(&result);
}

void test_invalid_operations() {
    Vector v1, v2, result;
    init_vector(&v1, 2, sizeof(double));
    init_vector(&v2, 3, sizeof(double)); // Размер не совпадает

    double a = 1.0, b = 2.0, c = 3.0, d = 4.0, e = 5.0;
    push_data_in_vector(&v1, &a);
    push_data_in_vector(&v1, &b);
    push_data_in_vector(&v2, &c);
    push_data_in_vector(&v2, &d);
    push_data_in_vector(&v2, &e);

    printf("Expecting an error message about vector size mismatch:\n\n");
    add__two_vectors(v1, v2, &result, GetDoubleFieldInfo()->add_func);

    free_vector(&v1);
    free_vector(&v2);
}

int main() {
    test_push_data_in_vector();
    test_add_vectors();
    test_scalar_product();
    test_complex_operations();
    test_invalid_operations();

    printf("\nAll tests passed!\n");
    return 0;
}
