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

int main() {
    test_push_data_in_vector();
    test_add_vectors();
    printf("All tests passed!\n");
    return 0;
}
