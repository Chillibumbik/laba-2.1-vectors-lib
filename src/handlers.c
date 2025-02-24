#include <stdio.h>
#include "vector.h"
#include "interface.h"

void print_complex(Complex c) {
    printf("%.2lf + %.2lfi", c.re, c.im);
}

void handle_double_vectors() {
    size_t size;
    printf("Enter the size of the vectors: ");
    scanf("%llu", &size);  

    Vector v1, v2;
    init_vector(&v1, size, sizeof(double), REAL);
    init_vector(&v2, size, sizeof(double), REAL);

    printf("Enter elements of the first vector:\n");
    for (size_t i = 0; i < size; i++) {
        double element;
        printf("Element %llu: ", i + 1);  
        scanf("%lf", &element);
        push_data_in_vector(&v1, &element);
    }

    printf("Enter elements of the second vector:\n");
    for (size_t i = 0; i < size; i++) {
        double element;
        printf("Element %llu: ", i + 1);  
        scanf("%lf", &element);
        push_data_in_vector(&v2, &element);
    }

    printf("\n\nFirst vector: ");
    print_vector(v1);
    printf("Second vector: ");
    print_vector(v2);
    printf("\n");

    int choice;
    show_menu();
    scanf("%d", &choice);

    if (choice == 1) {
        Vector result;
        add_two_vectors(v1, v2, &result);
        printf("\nResult of addition:\n");
        print_vector(result);
        free_vector(&result);
    } else if (choice == 2) {
        double result = scalar_multiply_real(v1, v2);  
        printf("\nScalar product: %.2lf\n", result);  
    } else if (choice == 3) {
        printf("Exiting program.\n");
        free_vector(&v1);
        free_vector(&v2);
        return;
    }

    free_vector(&v1);
    free_vector(&v2);
    printf("\n");
}

void handle_complex_vectors() {
    size_t size;
    printf("Enter the size of the vectors: ");
    scanf("%llu", &size);

    Vector v1, v2;
    init_vector(&v1, size, sizeof(Complex), COMPLEX);
    init_vector(&v2, size, sizeof(Complex), COMPLEX);

    printf("Enter elements of the first vector (real and imaginary parts):\n");
    for (size_t i = 0; i < size; i++) {
        Complex element;
        printf("Element %llu (real imaginary): ", i + 1);  
        scanf("%lf %lf", &element.re, &element.im);
        push_data_in_vector(&v1, &element);
    }

    printf("Enter elements of the second vector (real and imaginary parts):\n");
    for (size_t i = 0; i < size; i++) {
        Complex element;
        printf("Element %llu (real imaginary): ", i + 1); 
        scanf("%lf %lf", &element.re, &element.im);
        push_data_in_vector(&v2, &element);
    }

    printf("\n\nFirst vector: ");
    print_vector(v1);
    printf("Second vector: ");
    print_vector(v2);
    printf("\n");

    int choice;
    show_menu();
    scanf("%d", &choice);

    if (choice == 1) {
        Vector result;
        add_two_vectors(v1, v2, &result);
        printf("\nResult of addition:\n");
        print_vector(result);
        free_vector(&result);
    } else if (choice == 2) {
        Complex result = scalar_multiply_complex(v1, v2);  
        printf("\nScalar product: ");
        print_complex(result);
        printf("\n");
    } else if (choice == 3) {
        printf("Exiting program.\n");
        free_vector(&v1);
        free_vector(&v2);
        return;
    }

    free_vector(&v1);
    free_vector(&v2);
    printf("\n");
}
