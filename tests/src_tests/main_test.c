#include <stdio.h>
#include "add_test.h"      
#include "multiply_test.h"  
#include "more_tests.h"     

int main() {

    test_add_real_vectors();
    test_add_empty_vectors();
    test_add_incompatible_vectors();

    test_scalar_multiply_real();
    test_scalar_multiply_empty_vectors();
    test_scalar_multiply_incompatible_vectors();

    test_empty_vectors();
    test_zero_elements_vector();

    printf("All tests passed.\n");
    return 0;
}
