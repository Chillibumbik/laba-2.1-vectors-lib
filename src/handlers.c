#include <stdio.h>
#include "vector.h"
#include "interface.h"

void print_complex(Complex c) {
    printf("%.2lf + %.2lfi", c.re, c.im);
}

void handle_double_vectors() {
    int input_size;
    size_t size;
    int valid_input = 0;

    while (!valid_input) {
        printf("Enter the size of the vectors: ");
        if (scanf("%d", &input_size) != 1 || input_size <= 0) {
            printf("Invalid input. Please enter a positive integer.\n");
            while (getchar() != '\n');
        } else {
            size = (size_t)input_size;
            valid_input = 1;
        }
    }

    Vector v1, v2;
    init_vector(&v1, size, sizeof(double), REAL);
    init_vector(&v2, size, sizeof(double), REAL);

    printf("Enter elements of the first vector:\n");
    for (size_t i = 0; i < size; i++) {
        double element;
        printf("Element %llu: ", i + 1);
        while (scanf("%lf", &element) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); 
            printf("Element %llu: ", i + 1);
        }
        push_data_in_vector(&v1, &element);
    }

    printf("Enter elements of the second vector:\n");
    for (size_t i = 0; i < size; i++) {
        double element;
        printf("Element %llu: ", i + 1);
        while (scanf("%lf", &element) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            printf("Element %llu: ", i + 1);
        }
        push_data_in_vector(&v2, &element);
    }

    printf("\n\nFirst vector: ");
    print_vector(v1);
    printf("Second vector: ");
    print_vector(v2);
    printf("\n");

    int choice;
    show_menu();
    while (scanf("%d", &choice) != 1 || (choice < 1 || choice > 3)) {
        printf("Invalid choice. Please enter a number between 1 and 3.\n");
        while (getchar() != '\n');
        show_menu();
    }

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
    int input_size;
    size_t size;
    int valid_input = 0;

    while (!valid_input) {
        printf("Enter the size of the vectors: ");
        
        if (scanf("%d", &input_size) != 1 || input_size <= 0) {
            printf("Invalid input. Please enter a positive integer.\n");
            while (getchar() != '\n');
        } else {
            size = (size_t)input_size; 
            valid_input = 1; 
        }
    }

    Vector v1, v2;
    init_vector(&v1, size, sizeof(Complex), COMPLEX);
    init_vector(&v2, size, sizeof(Complex), COMPLEX);

    printf("Enter elements of the first vector (real and imaginary parts):\n");
    for (size_t i = 0; i < size; i++) {
        Complex element;
        printf("Element %llu (real imaginary): ", i + 1);
        while (scanf("%lf %lf", &element.re, &element.im) != 2) {
            printf("Invalid input. Please enter two valid numbers.\n");
            while (getchar() != '\n');
            printf("Element %llu (real imaginary): ", i + 1);
        }
        push_data_in_vector(&v1, &element);
    }

    printf("Enter elements of the second vector (real and imaginary parts):\n");
    for (size_t i = 0; i < size; i++) {
        Complex element;
        printf("Element %llu (real imaginary): ", i + 1);
        while (scanf("%lf %lf", &element.re, &element.im) != 2) {
            printf("Invalid input. Please enter two valid numbers.\n");
            while (getchar() != '\n');
            printf("Element %llu (real imaginary): ", i + 1);
        }
        push_data_in_vector(&v2, &element);
    }

    printf("\n\nFirst vector: ");
    print_vector(v1);
    printf("Second vector: ");
    print_vector(v2);
    printf("\n");

    int choice;
    show_menu();
    while (scanf("%d", &choice) != 1 || (choice < 1 || choice > 3)) {
        printf("Invalid choice. Please enter a number between 1 and 3.\n");
        while (getchar() != '\n');
        show_menu();
    }

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
