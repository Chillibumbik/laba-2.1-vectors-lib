#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void show_menu() {
    printf("\nSelect an operation:\n");
    printf("1 - Vector Addition\n");
    printf("2 - Scalar Product\n");
    printf("3 - Exit\n");
    printf("Your choice: ");
}

void show_type_menu() {
    printf("\nSelect data type:\n");
    printf("1 - Real Numbers (double)\n");
    printf("2 - Complex Numbers (Complex)\n");
    printf("Your choice: ");
}

void safe_scanf_double(double* value) {
    while (scanf("%lf", value) != 1) {
        printf("Invalid input. Please enter a valid number: ");
        while (getchar() != '\n'); 
    }
}

void safe_scanf_int(int* value) {
    while (scanf("%d", value) != 1 || *value <= 0) {
        printf("Invalid input. Please enter a positive integer: ");
        while (getchar() != '\n'); 
    }
}

void safe_scanf_complex(Complex* value) {
    while (scanf("%lf %lf", &value->re, &value->im) != 2) {
        printf("Invalid input. Please enter two numbers separated by space (real imaginary): ");
        while (getchar() != '\n'); 
    }
}

void handle_double_vectors() {
    unsigned long temp_size;
    printf("\nEnter vector size: ");
    scanf("%lu", &temp_size);
    size_t vector_size = (size_t)temp_size;

    Vector v1, v2, result;
    init_vector(&v1, vector_size, sizeof(double));
    init_vector(&v2, vector_size, sizeof(double));

    printf("Enter elements of the first vector (double):\n");
    for (size_t i = 0; i < vector_size; i++) {
        double value;
        printf("Element %lu: ", (unsigned long)(i + 1));
        safe_scanf_double(&value);
        push_data_in_vector(&v1, &value);
    }

    printf("Enter elements of the second vector (double):\n");
    for (size_t i = 0; i < vector_size; i++) {
        double value;
        printf("Element %lu: ", (unsigned long)(i + 1));
        safe_scanf_double(&value);
        push_data_in_vector(&v2, &value);
    }

    int operation;
    while (1) {
        show_menu();
        safe_scanf_int(&operation);
        
        if (operation == 1) {
            printf("\nYour vectors:\n");
            print_vector_real(v1);
            print_vector_real(v2);

            add__two_vectors(v1, v2, &result, GetDoubleFieldInfo()->add_func);
            printf("Vector sum (double): ");
            print_vector_real(result);
            free_vector(&result);
        } else if (operation == 2) {
            printf("\nYour vectors:\n");
            print_vector_real(v1);
            print_vector_real(v2);

            double scalar_result = 0.0;
            for (size_t i = 0; i < v1.size; i++) {
                scalar_result += GetDoubleFieldInfo()->scalar_multiply_func(
                    (char*)v1.data + i * v1.element_size,
                    (char*)v2.data + i * v2.element_size
                );
            }
            printf("Scalar product (double): %.2lf\n", scalar_result);
        } else if (operation == 3) {
            break;
        } else {
            printf("Error: Invalid input. Please try again.\n");
        }
    }

    free_vector(&v1);
    free_vector(&v2);
}

void handle_complex_vectors() {
    unsigned long temp_size;
    printf("\nEnter vector size: ");
    scanf("%lu", &temp_size);
    size_t vector_size = (size_t)temp_size;

    Vector v1, v2, result;
    init_vector(&v1, vector_size, sizeof(Complex));
    init_vector(&v2, vector_size, sizeof(Complex));

    printf("Enter elements of the first vector (Complex) (format: re im):\n");
    for (size_t i = 0; i < vector_size; i++) {
        Complex value;
        while (getchar() != '\n');  
        printf("Element %lu: ", (unsigned long)(i + 1));
        safe_scanf_complex(&value);
        push_data_in_vector(&v1, &value);
    }

    printf("\nEnter elements of the second vector (Complex) (format: re im):\n");
    for (size_t i = 0; i < vector_size; i++) {
        Complex value;
        while (getchar() != '\n');  
        printf("Element %lu: ", (unsigned long)(i + 1));
        safe_scanf_complex(&value);
        push_data_in_vector(&v2, &value);
    }

    int operation;
    while (1) {
        show_menu();
        safe_scanf_int(&operation);
        
        if (operation == 1) {
            printf("\nYour vectors:\n");
            print_vector_complex(v1);
            print_vector_complex(v2);

            add__two_vectors(v1, v2, &result, GetComplexFieldInfo()->add_func);
            printf("Vector sum (Complex): ");
            print_vector_complex(result);
            free_vector(&result);
        } else if (operation == 2) {
            printf("\nYour vectors:\n");
            print_vector_complex(v1);
            print_vector_complex(v2);

            double scalar_result = 0.0;
            for (size_t i = 0; i < v1.size; i++) {
                scalar_result += GetComplexFieldInfo()->scalar_multiply_func(
                    (char*)v1.data + i * v1.element_size,
                    (char*)v2.data + i * v2.element_size
                );
            }
            printf("Scalar product (Complex): %.2lf\n", scalar_result);
        } else if (operation == 3) {
            break;
        } else {
            printf("Error: Invalid input. Please try again.\n");
        }
    }

    free_vector(&v1);
    free_vector(&v2);
}

int main() {
    int choice;
    
    while (1) {
        show_type_menu();
        safe_scanf_int(&choice);

        if (choice == 1) {
            handle_double_vectors();
        } else if (choice == 2) {
            handle_complex_vectors();
        } else {
            printf("Error: Invalid input. Please try again.\n");
        }
    }

    return 0;
}
