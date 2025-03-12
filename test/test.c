#include <stdio.h>
#include <assert.h>
#include<math.h>
#include "VectorErrors.h"
#include "Vector.h"


#define EPS 1e-9

void test_double_sum(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6, 5.9, -6.1};

    VectorErrors operation_result;

    Vector* v1 = createVector(Get_double_Type_info(), 4, a1, &operation_result);
    Vector* v2 = createVector(Get_double_Type_info(), 4, a2, &operation_result);
    Vector* v_res_sum = createVector(Get_double_Type_info(), 4, NULL, &operation_result);
    Vector* v_mult_numb_res = createVector(Get_double_Type_info(), 4, NULL, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("sum checking\n");
    add_vectors(v1, v2, v_res_sum);
    double need_sum[] = {9.7, 1.6, 9.4, -1.3};
    for (int i = 0; i < 4; i++) {
        printf("search value: %lf, received value: %lf\n", need_sum[i], ((double*)v_res_sum->data)[i]);
        assert(fabs(((double*)v_res_sum->data)[i] - need_sum[i]) < EPS);
    }
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res_sum);
}

void test_double_scalar_multiply(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6, 5.9, -6.1};

    VectorErrors operation_result;

    Vector* v1 = createVector(Get_double_Type_info(), 4, a1, &operation_result);
    Vector* v2 = createVector(Get_double_Type_info(), 4, a2, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL);
    printf("Scalar multiply checking\n");
    double multiply_res;
    multiply_vectors(v1, v2, &multiply_res);
    double need_multiply = -4.91;
    printf("Search value: %lf, received value: %lf\n", need_multiply, multiply_res);
    assert(fabs(need_multiply - multiply_res) < EPS);
    free_vector(v1);
    free_vector(v2);

}


void test_double_vector_overwrite(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};

    VectorErrors operation_result;

    Vector* v1 = createVector(Get_double_Type_info(), 4, a1, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL);
    printf("Checking of rewriting\n");
    double overwrite_coord[] = {1.0, -2.5, 4.33, 5.0};
    rewrite_vector(Get_double_Type_info(),v1,4, &overwrite_coord);
    for (int i = 0; i < 4; i++) {
        printf("Искомое значение: %lf, Полученное значение: %lf\n", overwrite_coord[i], ((double*)v1->data)[i]);
        assert(fabs(((double*)v1->data)[i] - overwrite_coord[i]) < EPS);
    }
    free_vector(v1);
}


void test_complex_sum(){
    Complex a1[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    Complex a2[] = {{1.0, -9.6}, {4.7, 6.8}, {-6.8, 3.1}};
    
    VectorErrors operation_result;

    Vector* v1 = createVector(Get_complex_Type_info(), 3, a1, &operation_result);
    Vector* v2 = createVector(Get_complex_Type_info(), 3, a2, &operation_result);
    Vector* v_res_sum = createVector(Get_complex_Type_info(), 3, NULL, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("sum checking\n");
    add_vectors(v1, v2, v_res_sum);
    print_vector(v_res_sum);
    Complex need_sum[] = {{3.0, -12.6}, {5.9, -1.7}, {-11.3, 1.2}};
    Complex* res_coord = (Complex*)v_res_sum->data;
    for (int i=0; i<3; i++) {
        printf("Searched value:");
        v1->typeInfo->print(&need_sum[i]);
        printf("Received value: ");
        v_res_sum->typeInfo->print((char*)v_res_sum->data + i * v_res_sum->typeInfo->size);
        printf("\n");
        assert(fabs(res_coord[i].real - need_sum[i].real) < EPS);
        assert(fabs(res_coord[i].imag - need_sum[i].imag) < EPS);
        }
        free_vector(v1);
        free_vector(v2);
        free_vector(v_res_sum);
}
    
void test_complex_scalar_multiply(){
    Complex a1[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    Complex a2[] = {{1.0, -9.6}, {4.7, 6.8}, {-6.8, 3.1}};

    VectorErrors operation_result;

    Vector* v1 = createVector(Get_complex_Type_info(), 3, a1, &operation_result);
    Vector* v2 = createVector(Get_complex_Type_info(), 3, a2, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL);

    printf("Scalar multiply checking\n");
    Complex multiply_res;
    multiply_vectors(v1, v2, &multiply_res);
    Complex need_multiply = {73.13, -55.02};
    printf("Searched value: %lf+%lfi, Received value: %lf+%lfi\n", need_multiply.real, need_multiply.imag,\
         multiply_res.real, multiply_res.imag);
    assert(fabs(multiply_res.real - need_multiply.real) < EPS);
    assert(fabs(multiply_res.imag - need_multiply.imag) < EPS);
    free_vector(v1);
    free_vector(v2);
}

void test_complex_vector_overwrite(){
    Complex a1[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};

    VectorErrors operation_result;
    Vector* v1 = createVector(Get_complex_Type_info(), 3, a1, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL);

    printf("проверка изменения координат вектора\n");
    Complex need_overwrite_coord[] = {{3.0, -12.6}, {5.9, -1.7}, {-11.3, 1.2}};
    vector_overwrite(Get_complex_Type_info(), v1, 3, &need_overwrite_coord);
    Complex* res_overwrite_coord = (Complex*) v1->data;
    for (int i=0; i<3; i++) {
        printf("Искомое значение:");
        v1->typeInfo->print(&need_overwrite_coord[i]);
        printf(" Полученное значение: ");
        v1->typeInfo->print((char*)v1->data + i * v1->typeInfo->size);
        printf("\n");
        assert(fabs(res_overwrite_coord[i].real - need_overwrite_coord[i].real) < EPS);
        assert(fabs(res_overwrite_coord[i].imag - need_overwrite_coord[i].imag) < EPS);
        }
    free_vector(v1);
    }



void test_empty_vector() {
    VectorErrors operation_result;
    Vector* v = add_vector(Get_double_Type_info(), 0, 0, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v != NULL);
    assert(v->capacity == 0);
    free_vector(v);
}

void test_error_different_lenght(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6};

    VectorErrors operation_result;

    Vector* v1 = createVector(Get_double_Type_info(), 4, a1, &operation_result);
    Vector* v2 = createVector(Get_double_Type_info(), 2, a2, &operation_result);
    Vector* v_res_sum = createVector(Get_double_Type_info(), 2, NULL, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("Error checking: different length of vectors\n");

    errors_handler(add_vectors(v1, v2, v_res_sum));
    assert(add_vectors(v1, v2, v_res_sum) == DIFFERENT_LENGHT_VECTORS);
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res_sum);

}

void test_error_different_types(){
    double a1[] = {1.3, -2.0, 3.5};
    Complex a2[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};

    VectorErrors operation_result;

    Vector* v1 = createVector(GetDoubleTypeInfo(), 4, a1, &operation_result);
    Vector* v2 = createVector(GetComplexTypeInfo(), 3, a2, &operation_result);
    Vector* v_res_sum = createVector(GetComplexTypeInfo(), 3, NULL, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("Error checking: different types of vectors\n");

    errors_handler(add_vectors(v1, v2, v_res_sum));
    assert(add_vectors(v1, v2, v_res_sum) == INCOMPATIBLE_VECTOR_TYPES);
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res_sum);

}
int main(){
    test_double_sum();
    test_double_scalar_multiply();
    test_double_multiply_by_a_number();
    test_double_vector_overwrite();
    test_complex_sum();
    test_complex_scalar_multiply();
    test_complex_vector_overwrite();
    test_empty_vector();
    test_error_different_lenght();
    test_error_different_types();
}